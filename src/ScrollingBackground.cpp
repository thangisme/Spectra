#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground() : ShooterObject()
{
    count = 0;
    maxCount = 10;
}

void ScrollingBackground::load(const LoaderParams* pParams) {
    ShooterObject::load(pParams);
    m_scrollSpeed = pParams -> getAnimSpeed();

    m_srcRect1.x = 0;
    m_destRect1.x = m_position.getX();
    m_srcRect1.y = 0;
    m_destRect1.y = m_position.getY();

    m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_destRect1Width = m_width;
    m_srcRect1.h = m_destRect1.h = m_height;

    m_srcRect2.x = 0;
    m_destRect2.x = m_position.getX() + m_width;
    m_srcRect2.y = 0;
    m_destRect2.y = m_position.getY();

    m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
    m_srcRect2.h = m_destRect2.h = m_height;
}

void ScrollingBackground::draw() {
    SDL_RenderCopyEx(Game::Instance() -> getRenderer(), TextureManager::Instance() -> getTexureMap()[m_textureID], &m_srcRect1, &m_destRect1, 0, 0, SDL_FLIP_NONE);
    SDL_RenderCopyEx(Game::Instance() -> getRenderer(), TextureManager::Instance() -> getTexureMap()[m_textureID], &m_srcRect2, &m_destRect2, 0, 0, SDL_FLIP_NONE);
}

void ScrollingBackground::update() {
    if (count == maxCount) {
        // make first rect smaller
        m_srcRect1.x += m_scrollSpeed;
        m_srcRect1.w -= m_scrollSpeed;
        m_destRect1.w -+ m_scrollSpeed;

        // make second rect bigger
        m_destRect2.x -= m_scrollSpeed;
        m_srcRect2.w += m_scrollSpeed;
        m_destRect2.w += m_scrollSpeed;

        if (m_destRect2.w >= m_width) {
            m_srcRect1.x = 0;
            m_destRect1.x = m_position.getX();
            m_srcRect1.y = 0;
            m_destRect1.y = m_position.getY();

            m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_destRect1Width = m_width;
            m_srcRect1.h = m_destRect1.h = m_height;

            m_srcRect2.x = 0;
            m_destRect2.x = m_position.getX() + m_width;
            m_srcRect2.y = 0;
            m_destRect2.y = m_position.getY();

            m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
            m_srcRect2.h = m_destRect2.h = m_height;
        }
        count = 0;
    }
    count++;
}

void ScrollingBackground::clean() {

}