#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "PauseState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance() -> getStateManager() ->pushState(new PauseState());
    }
    for (auto& obj : m_gameObjects) {
        obj -> update();
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