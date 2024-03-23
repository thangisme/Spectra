#include "Player.h"
#include "InputHandler.h"
#include "BulletHandler.h"

Player::Player() : ShooterObject(), m_invulnerable(false),
                   m_invulnerableTime(100),
                   m_invulnerableCounter(0){}

void Player::load(const LoaderParams* pParams) {
    ShooterObject::load(pParams);
    m_moveSpeed = 5;
    m_bulletFiringSpeed = 13;

    m_bulletCounter = m_bulletFiringSpeed;

    m_dyingTime = 50;
}

void Player::draw() {
    ShooterObject::draw();
}

void Player::update() {
    if (Game::Instance() -> getLevelComplete()) {
        if (m_position.getX() >= Game::Instance() -> getGameWidth()) {
            Game::Instance() -> setCurrentLevel(Game::Instance() -> getCurrentLevel() + 1);
        } else {
            m_velocity.setY(0);
            m_velocity.setX(3);
            ShooterObject::update();
            handleAnimation();
        }
    } else {
        if (!m_bDying) {
            m_velocity.setX(0);
            m_velocity.setY(0);

            handleInput();

            ShooterObject::update();

            handleAnimation();
        } else {
            m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);

            if (m_dyingCounter == m_dyingTime) {
                resurrect();
            }

            m_dyingCounter++;
        }
    }
}

void Player::clean() {

}

void Player::handleInput() {
    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0) {
        m_velocity.setY(-m_moveSpeed);
    } else if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_DOWN) && m_position.getY() + m_height < Game::Instance() -> getGameHeight()) {
        m_velocity.setY(+m_moveSpeed);
    }

    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0) {
        setTurnLeft(true);
        m_velocity.setX(-m_moveSpeed);
    } else if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_RIGHT) && m_position.getX() + m_width < Game::Instance() -> getGameWidth()) {
        setTurnLeft(false);
        m_velocity.setX(+m_moveSpeed);
    }

    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_SPACE)) {
        if (m_bulletCounter == m_bulletFiringSpeed) {
            Vector2D bulletHeading(m_bulletFiringSpeed, 0);
            int tempX = m_position.getX() + m_width * m_scaleFactor / 2;
            if (isTurnLeft()) {
                bulletHeading.setX(-m_bulletFiringSpeed);
                tempX = m_position.getX() - m_width * m_scaleFactor / 2;
            }
            BulletHandler::Instance() ->addPlayerBullet(tempX, m_position.getY() + (m_height * m_scaleFactor) / 2, 16, 16, "bullet", 1, bulletHeading);
            m_bulletCounter = 0;
        }
        m_bulletCounter++;
    } else {
        m_bulletCounter = m_bulletFiringSpeed;
    }
}

void Player::resurrect() {
    Game::Instance() -> setPlayerLives(Game::Instance() -> getPlayerLives() - 1);

    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;

    m_textureID = "spectra";

    m_currentFrame = 0;
    m_currentRow = 0;
    m_numFrames = 2;
    m_width = 64;
    m_height = 64;

    m_dyingCounter = 0;
    m_invulnerable = true;
}

void Player::handleAnimation() {
    if (m_invulnerable) {
        if (m_invulnerableCounter == m_invulnerableTime) {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        } else {
            if (m_alpha == 255) {
                m_alpha = 0;
            } else {
                m_alpha = 255;
            }
        }
        m_invulnerableCounter++;
    }

    if (!m_bDead) {
        if (m_velocity.getX() < 0) {
            m_angle = -10.0;
        } else if (m_velocity.getX() > 0) {
            m_angle = 10.0;
        } else {
            m_angle = 0.0;
        }
    }

    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::collision() {
    if (!m_invulnerable && !Game::Instance() -> getLevelComplete()) {
        m_textureID = "spectra";
        m_currentFrame = 0;
        m_currentRow = 7;
        m_numFrames = 8;
        m_width = 64;
        m_height = 64;
        m_bDying = true;
    }
}