#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "LoaderParams.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
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

    GameObject* player = new Player(new LoaderParams(0, 0, 192, 192, "warrior"));

    m_gameObjects.push_back(player);

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