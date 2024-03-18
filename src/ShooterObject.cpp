#include "ShooterObject.h"

ShooterObject::ShooterObject() : GameObject(),
                                 m_bulletFiringSpeed(0),
                                 m_bulletCounter(0),
                                 m_moveSpeed(0),
                                 m_dyingTime(0),
                                 m_dyingCounter(0),
                                 m_bPlayedDeathSound(false) {
}

void ShooterObject::load(const LoaderParams* pParams) {
    // get position
    m_position = Vector2D(pParams->getX(), pParams->getY());

    // get drawing variables
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
}

void ShooterObject::doDyingAnimation() {
    scroll(Game::Instance()->getScrollSpeed());

    m_currentFrame = int(((SDL_GetTicks() / (1000 / 3))) % m_numFrames);

    if (m_dyingCounter == m_dyingTime) {
        m_bDead = true;
    }

    m_dyingCounter++;
}

void ShooterObject::draw() {
    if (m_velocity.getX() < 0) {
        TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height,
                                              m_currentRow, m_currentFrame, Game::Instance()->getRenderer(),0, m_alpha, m_scaleFactor,
                                              SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height,
                                              m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), 0, m_alpha, m_scaleFactor);
    }
}

void ShooterObject::update() {
    m_velocity += m_acceleration;
    m_position += m_velocity;
}
