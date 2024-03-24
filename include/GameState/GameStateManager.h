#ifndef PLATFORMER_GAMESTATEMANAGER_H
#define PLATFORMER_GAMESTATEMANAGER_H

#include <vector>
#include "GameState/GameState.h"

class GameStateManager {
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    void update();
    void render();
private:
    std::vector<GameState*> m_gameStates;
};

#endif //PLATFORMER_GAMESTATEMANAGER_H
