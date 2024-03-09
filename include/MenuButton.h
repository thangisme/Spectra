#ifndef PLATFORMER_MENUBUTTON_H
#define PLATFORMER_MENUBUTTON_H

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public SDLGameObject {
public:
    MenuButton(const LoaderParams* pParams, void (*callback) ());

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

    void setCallback(void(*callback)()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }
private:
    void (*m_callback)();
    bool m_bReleased;
    int m_callbackID;
};

#endif //PLATFORMER_MENUBUTTON_H
