#include "GameState/WinState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "GameState/MainMenuState.h"
#include "GameState/PlayState.h"
#include "GameState/StateParser.h"
#include "SoundManager.h"
#include <iostream>

const std::string WinState::s_winID = "WIN";

void WinState::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void WinState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool WinState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("data/states.xml", s_winID, &m_gameObjects,&m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_ToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    SoundManager::Instance()->playMusic("introMusic", -1);

    std::cout << "Entering WinState" << std::endl;
    return true;
}

void WinState::setCallbacks(const std::vector<Callback> &callbacks) {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        if (dynamic_cast<MenuButton*> (m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*> (m_gameObjects[i]);
            pButton ->setCallback(callbacks[pButton -> getCallbackID()]);
        }
    }
}

bool WinState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList) {
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    std::cout << "Exiting WinState" << std::endl;
    return true;
}

void WinState::s_ToMain() {
    SDL_Delay(1000);
    Game::Instance() -> getStateManager() ->changeState(new MainMenuState());
}

void WinState::s_restartPlay() {
    Game::Instance() -> getStateManager() ->changeState(new PlayState());
}