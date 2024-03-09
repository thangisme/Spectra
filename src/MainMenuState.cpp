#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include <iostream>

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void MainMenuState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool MainMenuState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("states.xml", s_menuID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0); // callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);

    std::cout << "Entering MenuState" << std::endl;

    return true;
}

bool MainMenuState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList){
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    std::cout << "Exiting MenuState" << std::endl;
    return true;
}

void MainMenuState::s_menuToPlay() {
    Game::Instance() -> getStateManager() -> changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu() {
    Game::Instance() -> quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks) {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        if (dynamic_cast<MenuButton*> (m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*> (m_gameObjects[i]);
            pButton ->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}