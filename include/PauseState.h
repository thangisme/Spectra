#ifndef PLATFORMER_PAUSESTATE_H
#define PLATFORMER_PAUSESTATE_H


#include <vector>
#include "GameState.h"
#include "GameObject.h"

class PauseState : public GameState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_pauseID; }
private:
    static const std::string s_pauseID;

    std::vector<GameObject*> m_gameObjects;

    static void s_pauseToMain();
    static void s_resumePlay();
};

#endif //PLATFORMER_PAUSESTATE_H
