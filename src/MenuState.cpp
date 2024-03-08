#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void MenuState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool MenuState::onEnter() {
    if (!TextureManager::Instance() ->load("assets/ui/button.png", "playbutton", Game::Instance() -> getRenderer())) {
        return false;
    }
    if (!TextureManager::Instance() ->load("assets/ui/exit.png", "exitbutton", Game::Instance() -> getRenderer())) {
        return false;
    }

    GameObject* playBtn = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
    GameObject* exitBtn = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);

    m_gameObjects.push_back(playBtn);
    m_gameObjects.push_back(exitBtn);

    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MenuState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();
    TextureManager::Instance() ->clearFromTextureMap("playbutton");
    TextureManager::Instance() ->clearFromTextureMap("exitbutton");

    std::cout << "Exiting MenuState" << std::endl;
    return true;
}

void MenuState::s_menuToPlay() {
    Game::Instance() -> getStateManager() -> changeState(new PlayState());
}

void MenuState::s_exitFromMenu() {
    Game::Instance() -> quit();
}