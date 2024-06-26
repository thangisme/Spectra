#include "Enemies/FlyingEnemy.h"
#include "BulletHandler.h"

FlyingEnemy::FlyingEnemy() : m_dyingTime(50), m_health(10), m_bulletFiringSpeed(100){}

void FlyingEnemy::update() {
    if (!m_bDying) {
        scroll(Game::Instance() -> getScrollSpeed());

        if (m_bulletCounter == m_bulletFiringSpeed) {
            BulletHandler::Instance()->addEnemyBullet(m_position.getX() + m_width / 2, m_position.getY() + m_height / 2, 16, 16, "bullet", 1, Vector2D(-3, 0));
            m_bulletCounter = 0;
        }
        m_bulletCounter++;
        m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
    } else {
        scroll(Game::Instance() -> getScrollSpeed());
        doDyingAnimation();
    }
}

void FlyingEnemy::collision() {
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

void FlyingEnemy::load(const LoaderParams *pParams) {
    ShooterObject::load(pParams);
}

void FlyingEnemy::draw() {
    ShooterObject::draw();
}

void FlyingEnemy::clean() {
    ShooterObject::clean();
}

