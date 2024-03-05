#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(const LoaderParams *pParams) : GameObject(pParams), m_pos(pParams -> getX(), pParams -> getY()),
                                                            m_velocity(0, 0){
    m_width = pParams -> getWidth();
    m_height = pParams -> getHeight();
    m_textureID = pParams -> getTextureID();
    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLGameObject::draw() {
    TextureManager::Instance() -> drawFrame(m_textureID, m_pos.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance() -> getRenderer());
}

void SDLGameObject::update() {
    m_pos += m_velocity;
}

void SDLGameObject::clean() {

}