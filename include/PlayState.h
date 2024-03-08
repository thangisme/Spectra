#ifndef PLATFORMER_PLAYSTATE_H
#define PLATFORMER_PLAYSTATE_H

#include <vector>
#include "GameState.h"
#include "GameObject.h"

class SDLGameObject;

class PlayState : public GameState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    bool checkCollision(SDLGameObject* a, SDLGameObject* b);

    virtual std::string getStateID() const { return s_playID; }
private:
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};

#endif //PLATFORMER_PLAYSTATE_H
