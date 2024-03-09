#include "GameOverState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include <iostream>

const std::string GameOverState::s_overID = "Over";

void GameOverState::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void GameOverState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool GameOverState::onEnter() {
    if (!TextureManager::Instance() ->load("assets/ui/restartBtn.png", "restartbutton", Game::Instance() -> getRenderer())) {
        return false;
    }
    if (!TextureManager::Instance() ->load("assets/ui/mainBtn.png", "menubutton", Game::Instance() -> getRenderer())) {
        return false;
    }
    if (!TextureManager::Instance() ->load("assets/ui/banner.png", "banner", Game::Instance() -> getRenderer())) {
        return false;
    }

    GameObject* overBanner = new SDLGameObject(new LoaderParams(100, 100, 200, 100,  "banner"));
    GameObject* restartBtn = new MenuButton(new LoaderParams(100, 300, 200, 100, "restartbutton"), s_restartPlay);
    GameObject* menuBtn = new MenuButton(new LoaderParams(100, 500, 200, 100, "menubutton"), s_gameOverToMain);

    m_gameObjects.push_back(overBanner);
    m_gameObjects.push_back(restartBtn);
    m_gameObjects.push_back(menuBtn);

    std::cout << "Entering GameOverState" << std::endl;
    return true;
}

bool GameOverState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();
    TextureManager::Instance() ->clearFromTextureMap("playbutton");
    TextureManager::Instance() ->clearFromTextureMap("exitbutton");

    std::cout << "Exiting GameOverState" << std::endl;
    return true;
}

void GameOverState::s_gameOverToMain() {
    Game::Instance() -> getStateManager() ->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay() {
    Game::Instance() -> getStateManager() ->changeState(new PlayState());
}