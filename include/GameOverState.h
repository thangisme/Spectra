#ifndef PLATFORMER_GAMEOVERSTATE_H
#define PLATFORMER_GAMEOVERSTATE_H


#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class GameOverState : public MenuState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_overID; };

    virtual void setCallbacks(const std::vector<Callback>& callbacks);
private:
    static const std::string s_overID;

    std::vector<GameObject*> m_gameObjects;

    static void s_gameOverToMain();
    static void s_restartPlay();
};

#endif //PLATFORMER_GAMEOVERSTATE_H
