#include "Player.h"
#include "InputHandler.h"

Player::Player() : SDLGameObject(){}

void Player::load(const LoaderParams *pParams) {
    SDLGameObject::load(pParams);
}

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    SDLGameObject::update();
    m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    m_currentRow = 2;
    handleInput();
}

void Player::clean() {

}

void Player::handleInput() {
    Vector2D* target = InputHandler::Instance() -> getMousePosition();

    m_velocity = *target - m_pos;
    m_velocity /= 20;
}