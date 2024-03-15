#include "Player.h"
#include "InputHandler.h"

Player::Player() : ShooterObject(){}

void Player::load(const LoaderParams* pParams) {
    ShooterObject::load(pParams);
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
}

void Player::resurrect() {
    Game::Instance() -> setPlayerLives(Game::Instance() -> getPlayerLives() - 1);

    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;

    m_textureID = "Player";

    m_currentFrame = 0;
    m_numFrames = 6;
    m_width = 192;
    m_height = 192;

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