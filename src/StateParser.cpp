#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char *stateFile, std::string stateID) {
    tinyxml2::XMLDocument xmlDoc;

    if (!xmlDoc.LoadFile(stateFile)) {
        std::cerr << xmlDoc.ErrorStr() << std::endl;
        return false;
    }

    tinyxml2::XMLElement* pRoot = xmlDoc.RootElement();
    tinyxml2::XMLElement* pStateRoot = 0;
    for(tinyxml2::XMLElement* e = pRoot ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
        if (e -> Value() == stateID) {
            pStateRoot = e;
        }
    }

    tinyxml2::XMLElement* pTextureRoot = 0;
    for(tinyxml2::XMLElement* e = pStateRoot ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
        if (e -> Value() == std::string("TEXTURES")) {
            pTextureRoot = e;
        }
    }
    parseTextures(pTextureRoot, pTextureIDs);

    tinyxml2::XMLElement* pObjectRoot = 0;
    for(tinyxml2::XMLElement* e = pStateRoot ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
        if (e -> Value() == std::string("OBJECTS")) {
            pObjectRoot = e;
        }
    }
    parseObjects(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement *pStateRoot, std::vector<std::string> *pTextureIDs) {
    for(tinyxml2::XMLElement* e = pStateRoot ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
        std::string filenameAttribute = e ->Attribute("filename");
        std::string idAttribute = e ->Attribute("ID");
        pTextureIDs ->push_back(idAttribute);

        TextureManager::Instance() -> load(filenameAttribute, idAttribute, Game::Instance() -> getRenderer());
    }
}


void StateParser::parseObjects(tinyxml2::XMLElement *pStateRoot, std::vector<GameObject *> *pObjects) {
    for(tinyxml2::XMLElement* e = pStateRoot ->FirstChildElement(); e != NULL; e = e ->NextSiblingElement()) {
       int x, y, width, height, numFrames, callbackID;
       std::string textureID;

       e ->QueryIntAttribute("x", &x);
       e ->QueryIntAttribute("y", &y);
       e ->QueryIntAttribute("width", &width);
       e ->QueryIntAttribute("height", &height);
       e ->QueryIntAttribute("numFrames", &numFrames);
       e ->QueryIntAttribute("callbackID", &callbackID);

       textureID = e ->Attribute("textureID");

       GameObject* pGameObject = GameObjectFactory::Instance() ->create(e ->Attribute("type"));
       pGameObject ->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID));
       pObjects ->push_back(pGameObject);
    }
}