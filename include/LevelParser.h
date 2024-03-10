#ifndef PLATFORMER_LEVELPARSER_H
#define PLATFORMER_LEVELPARSER_H

#include "tinyxml2.h"
#include "base64.h"
#include "zlib.h"
#include <vector>

class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser {
public:
    Level* parseLevel(const char* levelFile);
private:
    void parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    void parseTileLayer(tinyxml2::XMLElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets);

    int m_tileSize;
    int m_width;
    int m_height;
};

#endif //PLATFORMER_LEVELPARSER_H
