#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <string>
#include <vector>
#include "Layer.h"
#include "LevelParser.h"
#include "Player.h"

struct Tileset {
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level {
public:
    ~Level(){}

    void update();
    void render();

    std::vector<Tileset>* getTilesets() { return &m_tilesets; }
    std::vector<Layer*>* getLayers() { return &m_layers; }

    Player* getPlayer() { return m_pPlayer; }
    void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
private:
    friend class LevelParser;
    Level();
    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;

    Player* m_pPlayer;
};

#endif //PLATFORMER_LEVEL_H
