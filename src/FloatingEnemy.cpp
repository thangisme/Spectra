#include "FloatingEnemy.h"
#include <SDL.h>
#include <iostream>

FloatingEnemy::FloatingEnemy() : m_health(5), m_dyingTime(30), m_moveSpeed(2) {}

void FloatingEnemy::load(const LoaderParams *pParams) {
    ShooterObject::load(pParams);
    m_velocity.setX(-m_moveSpeed);
    if (SDL_GetTicks() % 2) {
        m_velocity.setY(m_moveSpeed / 2);
    } else {
        m_velocity.setY(-m_moveSpeed / 2);
    }
}

void FloatingEnemy::update() {
    scroll(Game::Instance() -> getScrollSpeed());
    m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
    if (!m_bDying) {
        if (m_position.getY() + m_height * m_scaleFactor >= Game::Instance() ->getGameHeight()) {
            m_velocity.setY(-m_moveSpeed / 2);
        } else if (m_position.getY() <= 0) {
            m_velocity.setY(m_moveSpeed / 2);
        }
    } else {
        m_velocity.setY(0);
        m_velocity.setX(0);
        doDyingAnimation();
    }
    ShooterObject::update();
}

void FloatingEnemy::collision() {
    m_health -= 1;
    if (m_health == 0) {
        if (!m_bPlayedDeathSound) {
            m_textureID = "explosion";
            m_currentFrame = 0;
            m_numFrames = 7;
            m_width = 64;
            m_height = 64;
            m_bDying = true;
        }
    }
}

void FloatingEnemy::draw() {
    ShooterObject::draw();
}

void FloatingEnemy::clean() {
    ShooterObject::clean();
}