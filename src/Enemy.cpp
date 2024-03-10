#include "Enemy.h"

Enemy::Enemy() : SDLGameObject(){}

void Enemy::load(const LoaderParams *pParams) {
    SDLGameObject::load(pParams);
    m_velocity.setY(2);
}

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::update() {
    m_currentFrame = (SDL_GetTicks() / 100) % 6;
    if (m_pos.getY() < 0) {
        m_velocity.setY(2);
    } else if (m_pos.getY() + m_height > 720) {
        m_velocity.setY(-2);
    } else if (m_pos.getX() < 0) {
        m_velocity.setX(1);
    } else if (m_pos.getX() > 1080) {
        m_velocity.setX(-1);
    }

    SDLGameObject::update();
}

void Enemy::clean() {

}

