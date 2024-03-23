#include "Map1Boss.h"
#include "BulletHandler.h"

Map1Boss::Map1Boss() : m_dyingTime(50), m_health(100), m_bulletFiringSpeed(70), m_moveSpeed(1) {}

void Map1Boss::load(const LoaderParams *pParams) {
    ShooterObject::load(pParams);
    m_velocity.setY(m_moveSpeed);
}

void Map1Boss::draw() {
    ShooterObject::draw();
}

void Map1Boss::clean() {
    ShooterObject::clean();
}

void Map1Boss::collision() {
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

void Map1Boss::update() {
    if (!m_bDying) {
        scroll(Game::Instance()->getScrollSpeed());

        if (m_position.getY() + m_height * m_scaleFactor >= Game::Instance()->getGameHeight()) {
            m_velocity.setY(-m_moveSpeed);
        } else if (m_position.getY() <= 0) {
            m_velocity.setY(m_moveSpeed);
        }

        if (m_bulletCounter == m_bulletFiringSpeed) {
            Vector2D headingDirections[] = {Vector2D(0, 3), Vector2D(3, 0), Vector2D(-3, 0), Vector2D(0, -3),
                                            Vector2D(3, 3), Vector2D(-3, 3), Vector2D(3, -3), Vector2D(-3, -3)};
            for (Vector2D heading: headingDirections) {
                BulletHandler::Instance()->addEnemyBullet(m_position.getX() + m_width / 2,
                                                          m_position.getY() + m_height / 2, 16, 16, "bullet", 1,
                                                          heading);
            }
            m_bulletCounter = 0;
        }
        m_bulletCounter++;
        ShooterObject::update();
    } else {
        scroll(Game::Instance()->getScrollSpeed());
        doDyingAnimation();
    }
}