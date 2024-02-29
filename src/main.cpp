#include <SDL.h>
#include "Game.h"


int main(int argc, char* args[]) {
    if (!Game::Instance() -> init ("Platformer", 100, 100, 1280, 720, 0)) return 1;

    while (Game::Instance() -> running()) {
        Game::Instance() -> handleEvents();
        Game::Instance() -> update();
        Game::Instance() -> render();
    }

    Game::Instance() -> clean();

    return 0;
}
