#include "PlayState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {

}

void PlayState::render() {

}

bool PlayState::onEnter() {
    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit() {
    std::cout << "Exiting PlayState" << std::endl;
    return true;
}