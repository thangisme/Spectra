#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : m_bReleased(true){
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::load(const LoaderParams *pParams) {
    SDLGameObject::load(pParams);
    m_callbackID = pParams -> getCallbackID();
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw() {
    SDLGameObject::draw();
}

void MenuButton::update() {
    Vector2D* pMousePos = InputHandler::Instance() -> getMousePosition();

    if (pMousePos -> getX() < (m_pos.getX() + m_width)
        && pMousePos -> getX() > m_pos.getX()
        && pMousePos -> getY() < (m_pos.getY() + m_height)
        && pMousePos -> getY() > m_pos.getY()) {
        if (InputHandler::Instance() ->getMouseButtonState(LEFT) && m_bReleased) {
            m_currentFrame = CLICKED;
            m_callback();
            m_bReleased = false;
        } else if (!InputHandler::Instance() ->getMouseButtonState(LEFT)) {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    } else {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean() {
    SDLGameObject::clean();
}