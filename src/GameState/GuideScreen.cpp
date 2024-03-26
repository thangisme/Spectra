#include "GameState/GuideScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "GameState/MainMenuState.h"
#include "GameState/PlayState.h"
#include "GameState/StateParser.h"
#include "SoundManager.h"
#include <iostream>

const std::string GuideScreen::s_guideID = "GUIDE";

void GuideScreen::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void GuideScreen::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool GuideScreen::onEnter() {
    StateParser stateParser;
    stateParser.parseState("data/states.xml", s_guideID, &m_gameObjects,&m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_startPlay);

    setCallbacks(m_callbacks);

    SoundManager::Instance()->playMusic("introMusic", -1);

    std::cout << "Entering GuideScreen" << std::endl;
    return true;
}

void GuideScreen::setCallbacks(const std::vector<Callback> &callbacks) {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        if (dynamic_cast<MenuButton*> (m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*> (m_gameObjects[i]);
            pButton ->setCallback(callbacks[pButton -> getCallbackID()]);
        }
    }
}

bool GuideScreen::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList) {
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    std::cout << "Exiting GuideScreen" << std::endl;
    return true;
}

void GuideScreen::s_startPlay() {
    Game::Instance() -> getStateManager() ->changeState(new PlayState());
}