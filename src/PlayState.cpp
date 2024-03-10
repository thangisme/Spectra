#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance() -> getStateManager() ->pushState(new PauseState());
    }
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }

    if (checkCollision(dynamic_cast<SDLGameObject *>(m_gameObjects[0]), dynamic_cast<SDLGameObject *>(m_gameObjects[1]))) {
        Game::Instance() -> getStateManager() ->pushState(new GameOverState());
    }
}

void PlayState::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}

bool PlayState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("data/states.xml", s_playID, &m_gameObjects, &m_textureIDList);

    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit() {
    for (auto& obj : m_gameObjects) {
        obj -> clean();
    }

    m_gameObjects.clear();

    for (std::string textureID : m_textureIDList) {
        TextureManager::Instance() ->clearFromTextureMap(textureID);
    }

    std::cout << "Exiting PlayState" << std::endl;
    return true;
}

bool PlayState::checkCollision(SDLGameObject *a, SDLGameObject *b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a -> getPosition().getX();
    rightA = a -> getPosition().getX() + a -> getWidth();
    topA = a -> getPosition().getY();
    bottomA = a -> getPosition().getY() + a -> getHeight();

    leftB = b -> getPosition().getX();
    rightB = b -> getPosition().getX() + b ->getWidth();
    topB = b ->getPosition().getY();
    bottomB = b ->getPosition().getY() + b ->getHeight();

    if( bottomA <= topB ){ return false; }
    if( topA >= bottomB ){ return false; }
    if( rightA <= leftB ){ return false; }
    if( leftA >= rightB ){ return false; }

    return true;
}