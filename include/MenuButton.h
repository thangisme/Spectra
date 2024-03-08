#ifndef PLATFORMER_MENUBUTTON_H
#define PLATFORMER_MENUBUTTON_H

#include "SDLGameObject.h"

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
private:
    void (*m_callback)();
    bool m_bReleased;
};

#endif //PLATFORMER_MENUBUTTON_H
