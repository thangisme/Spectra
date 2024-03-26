#include "Enemies/Map2Boss.h"
#include "BulletHandler.h"

Map2Boss::Map2Boss() : m_dyingTime(5000), m_health(100), m_bulletFiringSpeed(100), m_moveSpeed(1), m_entered(false) {}

void Map2Boss::load(const LoaderParams *pParams) {
    ShooterObject::load(pParams);
    m_velocity.setY(m_moveSpeed);
    m_currentRow = 2;
}

void Map2Boss::draw() {
    ShooterObject::draw();
}

void Map2Boss::clean() {
    ShooterObject::clean();
}

void Map2Boss::collision() {
    m_health -= 1;
    if (m_health == 0) {
        if (!m_bPlayedDeathSound) {
            m_textureID = "explosion";
            m_currentFrame = 0;
            m_numFrames = 6;
            m_width = 64;
            m_height = 64;
            m_bDying = true;
        }
    }
}

void Map2Boss::update() {
    if (!m_entered) {
        scroll(Game::Instance()->getScrollSpeed());
        if (m_position.getX() <= Game::Instance()->getGameWidth() - m_width * m_scaleFactor - 100) {
            m_entered = true;
        }
    } else {
        if (!m_bDying) {
            m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);

            if (m_position.getY() + m_height * m_scaleFactor >= Game::Instance()->getGameHeight()) {
                m_velocity.setY(-m_moveSpeed);
            } else if (m_position.getY() <= 0) {
                m_velocity.setY(m_moveSpeed);
            }

            if (m_bulletCounter == m_bulletFiringSpeed) {
                BulletHandler::Instance() -> addEnemyBullet(m_position.getX() - 75,
                                                            m_position.getY() + 55, 100, 24, "map2boss_bullet", 3,
                                                            Vector2D(-3, 0));
                m_bulletCounter = 0;
            }
            m_bulletCounter++;
            ShooterObject::update();
        } else {
            scroll(Game::Instance()->getScrollSpeed());
            doDyingAnimation();
            Game::Instance()->setLevelComplete(true);
        }
    }
}