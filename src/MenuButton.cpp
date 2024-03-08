#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams *pParams) : SDLGameObject(pParams){
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
        m_currentFrame = MOUSE_OVER;

        if (InputHandler::Instance() ->getMouseButtonState(LEFT)) {
            m_currentFrame = CLICKED;
        }
    } else {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean() {
    SDLGameObject::clean();
}