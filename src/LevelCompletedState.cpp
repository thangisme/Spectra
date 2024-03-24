#include "LevelCompletedState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "SoundManager.h"
#include <iostream>

const std::string LevelCompletedState::s_completedID = "LEVELCOMPLETED";

void LevelCompletedState::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void LevelCompletedState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool LevelCompletedState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("data/states.xml", s_completedID, &m_gameObjects,&m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_ToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    SoundManager::Instance()->playMusic("introMusic", -1);

    std::cout << "Entering LevelCompletedState" << std::endl;
    return true;
}

void LevelCompletedState::setCallbacks(const std::vector<Callback> &callbacks) {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        if (dynamic_cast<MenuButton*> (m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*> (m_gameObjects[i]);
            pButton ->setCallback(callbacks[pButton -> getCallbackID()]);
        }
    }
}

bool LevelCompletedState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList) {
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    std::cout << "Exiting LevelCompletedState" << std::endl;
    return true;
}

void LevelCompletedState::s_ToMain() {
    SDL_Delay(1000);
    Game::Instance() -> getStateManager() ->changeState(new MainMenuState());
}

void LevelCompletedState::s_restartPlay() {
    Game::Instance() -> getStateManager() ->changeState(new PlayState());
}