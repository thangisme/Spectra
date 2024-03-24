#ifndef SPECTRA_LEVELCOMPLETEDSTATE_H
#define SPECTRA_LEVELCOMPLETEDSTATE_H


#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class LevelCompletedState : public MenuState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_completedID; };

    virtual void setCallbacks(const std::vector<Callback>& callbacks);
private:
    static const std::string s_completedID;

    std::vector<GameObject*> m_gameObjects;

    static void s_ToMain();
    static void s_restartPlay();
};

#endif //SPECTRA_LEVELCOMPLETEDSTATE_H
