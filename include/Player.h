#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject {
public:
    Player();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void handleInput();
    virtual void load(const LoaderParams* pParams);
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif //PLAYER_H
