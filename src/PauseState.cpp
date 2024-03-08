#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() {
    Game::Instance() -> getStateManager() ->changeState(new MenuState());
}

void PauseState::s_resumePlay() {
    Game::Instance() -> getStateManager() -> popState();
}

void PauseState::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void PauseState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool PauseState::onEnter() {
    if (!TextureManager::Instance() -> load("assets/ui/resumeBtn.png", "resumeBtn", Game::Instance() -> getRenderer())) {
        return false;
    }

    if (!TextureManager::Instance() -> load("assets/ui/mainBtn.png", "mainBtn", Game::Instance() -> getRenderer())) {
        return false;
    }

    GameObject* mainBtn = new MenuButton(new LoaderParams(200, 100, 200, 80, "mainBtn"), s_pauseToMain);
    GameObject* resumeBtn = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumeBtn"), s_resumePlay);

    m_gameObjects.push_back(mainBtn);
    m_gameObjects.push_back(resumeBtn);

    std::cout << "Entering PauseState" << std::endl;
    return true;
}

bool PauseState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();
    TextureManager::Instance() ->clearFromTextureMap("mainBtn");
    TextureManager::Instance() ->clearFromTextureMap("resumeBtn");
    InputHandler::Instance() -> reset();

    std::cout << "exiting PauseState" << std::endl;
    return true;
}