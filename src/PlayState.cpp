#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "LoaderParams.h"
#include "ShooterObject.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "LevelParser.h"
#include "BulletHandler.h"
#include "GameObjectFactory.h"
#include "Turret.h"
#include "FlyingEnemy.h"
#include "FloatingEnemy.h"
#include "Map1Boss.h"
#include "SoundManager.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance() -> getStateManager() ->pushState(new PauseState());
    }

    BulletHandler::Instance()->updateBullets();

    pLevel -> update();

    if (Game::Instance() -> getPlayerLives() == 0) {
        Game::Instance() -> getStateManager() ->changeState(new GameOverState());
    }
}

void PlayState::render() {
    pLevel ->render();
    BulletHandler::Instance()->drawBullets();
    for (int i = 0; i < Game::Instance() -> getPlayerLives(); i++) {
        TextureManager::Instance() ->drawFrame("lives", 20 + 42 * i, 20, 42, 42, 0, 0, Game::Instance() -> getRenderer());
    }
}

bool PlayState::onEnter() {
    GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    GameObjectFactory::Instance()->registerType("FlyingEnemy", new FlyingEnemyCreator());
    GameObjectFactory::Instance()->registerType("FloatingEnemy", new FloatingEnemyCreator());
    GameObjectFactory::Instance()->registerType("Map1Boss", new Map1BossCreator());
    Game::Instance() ->setPlayerLives(3);
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("data/map1.tmx");

    SoundManager::Instance()->playMusic("bgMusic", -1);

    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList) {
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    BulletHandler::Instance() -> clearBullets();

    std::cout << "Exiting PlayState" << std::endl;
    return true;
}

bool PlayState::checkCollision(ShooterObject *a, ShooterObject *b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a -> getPosition().getX();
    rightA = a -> getPosition().getX() + a -> getWidth();
    topA = a -> getPosition().getY();
    bottomA = a -> getPosition().getY() + a -> getHeight();

    leftB = b -> getPosition().getX();
    rightB = b -> getPosition().getX() + b ->getWidth();
    topB = b ->getPosition().getY();
    bottomB = b ->getPosition().getY() + b ->getHeight();

    if( bottomA <= topB ){ return false; }
    if( topA >= bottomB ){ return false; }
    if( rightA <= leftB ){ return false; }
    if( leftA >= rightB ){ return false; }

    return true;
}