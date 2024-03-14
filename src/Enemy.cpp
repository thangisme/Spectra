#include "Enemy.h"

Enemy::Enemy() : ShooterObject(){}

void Enemy::load(const LoaderParams *pParams) {
    ShooterObject::load(pParams);
}

void Enemy::draw() {
    ShooterObject::draw();
}

void Enemy::update() {
    m_currentFrame = (SDL_GetTicks() / 100) % 6;

    ShooterObject::update();
}

void Enemy::clean() {

}

