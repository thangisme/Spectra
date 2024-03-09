#include "SDLGameObject.h"

SDLGameObject::SDLGameObject() : GameObject() {}

void SDLGameObject::load(const LoaderParams *pParams) {
    m_pos = Vector2D(pParams -> getX(), pParams -> getY());
    m_velocity = Vector2D(0,0);
    m_acceleration = Vector2D(0,0);
    m_width = pParams -> getWidth();
    m_height = pParams -> getHeight();
    m_textureID = pParams -> getTextureID();
    m_currentFrame = 0;
    m_currentRow = 0;
    m_numFrames = pParams -> getNumFrames();
}

void SDLGameObject::draw() {
    if (m_velocity.getX() < 0) {
        TextureManager::Instance() -> drawFrame(m_textureID, m_pos.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance() -> getRenderer(), SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::Instance() -> drawFrame(m_textureID, m_pos.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance() -> getRenderer());
    }
}

void SDLGameObject::update() {
    m_velocity += m_acceleration;
    m_pos += m_velocity;
}

void SDLGameObject::clean() {

}