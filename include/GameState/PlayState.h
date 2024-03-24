#ifndef PLATFORMER_PLAYSTATE_H
#define PLATFORMER_PLAYSTATE_H

#include <vector>
#include "GameState/GameState.h"
#include "GameObject.h"
#include "Level.h"

class ShooterObject;

class PlayState : public GameState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    bool checkCollision(ShooterObject* a, ShooterObject* b);

    virtual std::string getStateID() const { return s_playID; }
private:
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
    Level* pLevel;
};

#endif //PLATFORMER_PLAYSTATE_H
