#ifndef PLATFORMER_MENUBUTTON_H
#define PLATFORMER_MENUBUTTON_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"

enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public ShooterObject {
public:
    MenuButton();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams> &pParams);

    void setCallback(void(*callback)()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }
private:
    void (*m_callback)();
    bool m_bReleased;
    int m_callbackID;
};

class MenuButtonCreator : public BaseCreator {
    GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};

#endif //PLATFORMER_MENUBUTTON_H
