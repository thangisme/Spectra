#include "GameState/PauseState.h"
#include "Game.h"
#include "GameState/MainMenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "GameState/StateParser.h"
#include "SoundManager.h"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() {
    Game::Instance() -> getStateManager() ->changeState(new MainMenuState());
}

void PauseState::s_resumePlay() {
    SoundManager::Instance()->playMusic("bgMusic", -1);
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
    StateParser stateParser;
    stateParser.parseState("data/states.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    SoundManager::Instance()->playMusic("introMusic", -1);

    std::cout << "Entering PauseState" << std::endl;
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback> &callbacks) {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        if (dynamic_cast<MenuButton*> (m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*> (m_gameObjects[i]);
            pButton ->setCallback(callbacks[pButton -> getCallbackID()]);
        }
    }
}

bool PauseState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList) {
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    InputHandler::Instance() -> reset();

    std::cout << "exiting PauseState" << std::endl;
    return true;
}