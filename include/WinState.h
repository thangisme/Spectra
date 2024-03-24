#ifndef SPECTRA_WINSTATE_H
#define SPECTRA_WINSTATE_H

#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class WinState : public MenuState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_winID; };

    virtual void setCallbacks(const std::vector<Callback>& callbacks);
private:
    static const std::string s_winID;

    std::vector<GameObject*> m_gameObjects;

    static void s_ToMain();
    static void s_restartPlay();
};


#endif //SPECTRA_WINSTATE_H
