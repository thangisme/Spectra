#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "Level.h"
#include <iostream>

Level* LevelParser::parseLevel(const char *levelFile) {
    tinyxml2::XMLDocument levelDoc;
    levelDoc.LoadFile(levelFile);

    if (levelDoc.ErrorID()) {
        std::cout << "Failed to load tilemap" << std::endl;
        return NULL;
    }

    Level* pLevel = new Level();

    tinyxml2::XMLElement* pRoot = levelDoc.RootElement();

    pRoot ->QueryIntAttribute("tilewidth", &m_tileSize);
    pRoot ->QueryIntAttribute("width", &m_width);
    pRoot ->QueryIntAttribute("height", &m_height);

    for(tinyxml2::XMLElement* e = pRoot ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
        if (e -> Value() == std::string("tileset")) {
            parseTilesets(e, pLevel -> getTilesets());
        }
    }

    for (tinyxml2::XMLElement* e = pRoot ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
        if (e -> Value() == std::string("layer")) {
            parseTileLayer(e, pLevel -> getLayers(), pLevel -> getTilesets());
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement *pTilesetRoot, std::vector<Tileset> *pTilesets) {
    TextureManager::Instance() ->load(pTilesetRoot ->FirstChildElement() ->Attribute("source"), pTilesetRoot ->Attribute("name"), Game::Instance() -> getRenderer());
    Tileset tileset;
    pTilesetRoot ->FirstChildElement() ->QueryIntAttribute("width", &tileset.width);
    pTilesetRoot ->FirstChildElement() ->QueryIntAttribute("height", &tileset.height);
    pTilesetRoot ->QueryIntAttribute("firstgid", &tileset.firstGridID);
    pTilesetRoot ->QueryIntAttribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot ->QueryIntAttribute("tileheight", &tileset.tileHeight);
    if (pTilesetRoot ->QueryIntAttribute("spacing", &tileset.spacing) == tinyxml2::XML_NO_ATTRIBUTE) tileset.spacing = 0;
    if (pTilesetRoot ->QueryIntAttribute("margin", &tileset.margin) == tinyxml2::XML_NO_ATTRIBUTE) tileset.margin = 0;
    tileset.name = pTilesetRoot ->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets ->push_back(tileset);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement *pTileElement, std::vector<Layer *> *pLayers,
                                 const std::vector<Tileset> *pTilesets) {
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    tinyxml2::XMLElement* pDataNode;

    for (tinyxml2::XMLElement* e = pTileElement ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
        if (e -> Value() == std::string("data")) {
            pDataNode = e;
        }
    }

    for (tinyxml2::XMLNode* e = pDataNode -> FirstChild(); e != NULL; e = e ->NextSibling()) {
        tinyxml2::XMLText* text = e ->ToText();
        std::string t = text -> Value();
        decodedIDs = base64_decode(t);
    }

    // Zlib compression library
    uLongf sizeofids = m_width * m_height * sizeof(int);
    std::vector<int> ids(m_width * m_height);
    uncompress((Bytef*)&ids[0], &sizeofids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);

    for (int j = 0; j < m_height; j++) {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++) {
        for (int cols = 0; cols < m_width; cols++) {
            data[rows][cols] = ids[rows * m_width + cols];
        }
    }

    pTileLayer ->setTileIDs(data);

    pLayers ->push_back(pTileLayer);
}