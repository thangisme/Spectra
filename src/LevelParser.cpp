#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "Level.h"
#include "helper.h"
#include "ObjectLayer.h"
#include <iostream>
#include <string>

Level *LevelParser::parseLevel(const char *levelFile) {
    tinyxml2::XMLDocument levelDoc;
    levelDoc.LoadFile(levelFile);

    if (levelDoc.ErrorID()) {
        std::cout << "Failed to load tilemap" << std::endl;
        return NULL;
    }

    pLevel = new Level();

    tinyxml2::XMLElement *pRoot = levelDoc.RootElement();

    pRoot->QueryIntAttribute("tilewidth", &m_tileSize);
    pRoot->QueryIntAttribute("width", &m_width);
    pRoot->QueryIntAttribute("height", &m_height);

    tinyxml2::XMLElement *pProperties = pRoot->FirstChildElement();
    for (tinyxml2::XMLElement *e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("property")) {
            parseTextures(e);
        }
    }

    for (tinyxml2::XMLElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    for (tinyxml2::XMLElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
            if (e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, pLevel->getLayers());
            } else if (e->FirstChildElement()->Value() == std::string("data") || (e ->FirstChildElement() ->NextSiblingElement() != 0 && e->FirstChildElement() ->NextSiblingElement() -> Value() == std::string("data"))) {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel -> getCollisionLayers());
                pLevel -> getCollisionLayers();
            }
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement *pTilesetRoot, std::vector<Tileset> *pTilesets) {
    TextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"),
                                     pTilesetRoot->Attribute("name"), Game::Instance()->getRenderer());
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->QueryIntAttribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->QueryIntAttribute("height", &tileset.height);
    pTilesetRoot->QueryIntAttribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->QueryIntAttribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->QueryIntAttribute("tileheight", &tileset.tileHeight);
    if (pTilesetRoot->QueryIntAttribute("spacing", &tileset.spacing) == tinyxml2::XML_NO_ATTRIBUTE) tileset.spacing = 0;
    if (pTilesetRoot->QueryIntAttribute("margin", &tileset.margin) == tinyxml2::XML_NO_ATTRIBUTE) tileset.margin = 0;
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers) {
    TileLayer *pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    std::vector<std::vector<int>> data;

    bool collidable = false;

    std::string decodedIDs;
    tinyxml2::XMLElement *pDataNode;

    for (tinyxml2::XMLElement *e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            pDataNode = e;
        }
        if (e -> Value() == std::string("properties")) {
            for (tinyxml2::XMLElement* property = e ->FirstChildElement(); property != NULL; property = property ->NextSiblingElement()) {
                if (property -> Value() == std::string("property")) {
                    if (property ->Attribute("name") == std::string("collidable")) {
                        collidable = true;
                    }
                }
            }
        }
    }

    for (tinyxml2::XMLNode *e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
        tinyxml2::XMLText *text = e->ToText();
        std::string t = strip(text->Value());
        decodedIDs = base64_decode(t);
    }

    // Zlib compression library
    uLongf sizeofids = m_width * m_height * sizeof(int);
    std::vector<int> ids(m_width * m_height);
    uncompress((Bytef *) &ids[0], &sizeofids, (const Bytef *) decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);

    for (int j = 0; j < m_height; j++) {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++) {
        for (int cols = 0; cols < m_width; cols++) {
            data[rows][cols] = ids[rows * m_width + cols];
        }
    }

    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(m_width);

    if (collidable) {
        pCollisionLayers -> push_back(pTileLayer);
    }

    pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(tinyxml2::XMLElement *pTextureRoot) {
    TextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"),
                                     Game::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(tinyxml2::XMLElement *pObjectElement, std::vector<Layer *> *pLayers) {
    ObjectLayer *pObjectLayer = new ObjectLayer();

    for (tinyxml2::XMLElement *e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("object")) {
            int x, y, width, height, numFrames, callbackID = 0, animSpeed = 1, scaleFactor = 1;
            std::string textureID;

            e->QueryIntAttribute("x", &x);
            e->QueryIntAttribute("y", &y);
            e->QueryIntAttribute("width", &width);
            e->QueryIntAttribute("height", &height);

            GameObject *pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));

            for (tinyxml2::XMLElement *properties = e->FirstChildElement();
                 properties != NULL; properties = properties -> NextSiblingElement()) {
                if (properties->Value() == std::string("properties")) {
                    for (tinyxml2::XMLElement *property = properties->FirstChildElement();
                         property != NULL; property = property->NextSiblingElement()) {
                        if (property->Value() == std::string("property")) {
                            if (property->Attribute("name") == std::string("numFrames")) {
                                property->QueryIntAttribute("value", &numFrames);
                            } else if (property->Attribute("name", "textureID")) {
                                textureID = property->Attribute("value");
                                std::cout << textureID << std::endl;
                            } else if (property->Attribute("name", "callbackID")) {
                                property->QueryIntAttribute("value", &callbackID);
                            } else if (property->Attribute("name", "animSpeed")) {
                                property->QueryIntAttribute("value", &animSpeed);
                            } else if (property->Attribute("name","scaleFactor")) {
                                property->QueryIntAttribute("value", &scaleFactor);
                            }
                        }
                    }
                }
            }

            pGameObject ->load(new LoaderParams(x,y, width, height, textureID, numFrames, callbackID, animSpeed, scaleFactor));
            if (pGameObject->type() == "Player") {
                pLevel ->setPlayer(dynamic_cast<Player*> (pGameObject));
            }
            pObjectLayer -> getGameObjects() ->push_back(pGameObject);
        }
    }
    pLayers ->push_back(pObjectLayer);
}