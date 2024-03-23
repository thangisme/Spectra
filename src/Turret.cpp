#include "Turret.h"
#include "BulletHandler.h"

Turret::Turret() : m_dyingTime(50), m_health(10), m_bulletFiringSpeed(50){}

Turret::~Turret(){}

void Turret::load(const LoaderParams *pParams) {
    ShooterObject::load(pParams);
}

void Turret::draw() {
    ShooterObject::draw();
}

void Turret::clean() {
    ShooterObject::clean();
}

void Turret::collision() {
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

void Turret::update() {
    if (!m_bDying) {
        scroll(Game::Instance() -> getScrollSpeed());

        if (m_bulletCounter == m_bulletFiringSpeed) {
            BulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet", 1, Vector2D(-3, -3));
            BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY(), 16, 16, "bullet", 1, Vector2D(0, -3));
            BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY(), 16, 16, "bullet", 1, Vector2D(3, -3));
            m_bulletCounter = 0;
        }
        m_bulletCounter++;
    } else {
        scroll(Game::Instance() -> getScrollSpeed());
        doDyingAnimation();
    }
}