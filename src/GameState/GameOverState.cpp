#include "GameState/GameOverState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "GameState/MainMenuState.h"
#include "GameState/PlayState.h"
#include "GameState/StateParser.h"
#include "SoundManager.h"
#include <iostream>

const std::string GameOverState::s_overID = "GAMEOVER";

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
    StateParser stateParser;
    stateParser.parseState("data/states.xml", s_overID, &m_gameObjects,&m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    SoundManager::Instance()->playMusic("introMusic", -1);

    std::cout << "Entering GameOverState" << std::endl;
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks) {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        if (dynamic_cast<MenuButton*> (m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*> (m_gameObjects[i]);
            pButton ->setCallback(callbacks[pButton -> getCallbackID()]);
        }
    }
}

bool GameOverState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList) {
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    std::cout << "Exiting GameOverState" << std::endl;
    return true;
}

void GameOverState::s_gameOverToMain() {
    SDL_Delay(1000);
    Game::Instance() -> getStateManager() ->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay() {
    Game::Instance() -> getStateManager() ->changeState(new PlayState());
}