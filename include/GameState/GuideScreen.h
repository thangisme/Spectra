#ifndef SPECTRA_GUIDESCREEN_H
#define SPECTRA_GUIDESCREEN_H

#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class GuideScreen : public MenuState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_guideID; };

    virtual void setCallbacks(const std::vector<Callback>& callbacks);
private:
    static const std::string s_guideID;

    std::vector<GameObject*> m_gameObjects;

    static void s_startPlay();
};

#endif //SPECTRA_GUIDESCREEN_H
