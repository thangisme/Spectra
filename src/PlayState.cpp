#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance() -> getStateManager() ->pushState(new PauseState());
    }
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }

    if (checkCollision(dynamic_cast<SDLGameObject *>(m_gameObjects[0]), dynamic_cast<SDLGameObject *>(m_gameObjects[1]))) {
        Game::Instance() -> getStateManager() ->pushState(new GameOverState());
    }
}

void PlayState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool PlayState::onEnter() {
    if (!TextureManager::Instance() -> load("assets/objects/warrior.png", "warrior", Game::Instance() -> getRenderer())) {
        return false;
    }

    if (!TextureManager::Instance() -> load("assets/objects/goblin.png", "goblin", Game::Instance() -> getRenderer())) {
        return false;
    }

    GameObject* player = new Player(new LoaderParams(0, 0, 192, 192, "warrior"));
    GameObject* enemy = new Enemy(new LoaderParams(400, 300, 192, 192, "goblin"));

    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);

    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();
    TextureManager::Instance() ->clearFromTextureMap("warrior");

    std::cout << "Exiting PlayState" << std::endl;
    return true;
}

bool PlayState::checkCollision(SDLGameObject *a, SDLGameObject *b) {
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