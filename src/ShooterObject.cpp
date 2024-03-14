#include "ShooterObject.h"

void ShooterObject::doDyingAnimation() {
    scroll(Game::Instance() -> getScrollSpeed());

    m_currentFrame = int(((SDL_GetTicks() / (1000 / 3))) % m_numFrames);

    if (m_dyingCounter == m_dyingTime) {
        m_bDead = true;
    }

    m_dyingCounter++;
}

void ShooterObject::draw() {
    if (m_velocity.getX() < 0) {
        TextureManager::Instance() -> drawFrame(m_textureID, m_position.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance() -> getRenderer(), SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::Instance() -> drawFrame(m_textureID, m_position.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance() -> getRenderer());
    }
}

void ShooterObject::update() {
    m_velocity += m_acceleration;
    m_position += m_velocity;
}
