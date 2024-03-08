#include <SDL.h>
#include "Game.h"

const char* TITLE = "Platformer";
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int INITIAL_X = SDL_WINDOWPOS_CENTERED;
const int INITIAL_Y = SDL_WINDOWPOS_CENTERED;
const int SDL_FLAG = 0;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[]) {
    Uint32 frameStart, frameTime;

    if (!Game::Instance() -> init (TITLE, INITIAL_X, INITIAL_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAG)) return 1;
    while (Game::Instance() -> running()) {
        frameStart = SDL_GetTicks();

        Game::Instance() -> handleEvents();
        Game::Instance() -> update();
        Game::Instance() -> render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME) {
            SDL_Delay((int) (DELAY_TIME - frameTime));
        }
    }

    Game::Instance() -> clean();

    return 0;
}
