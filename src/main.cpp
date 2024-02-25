#include <SDL.h>
#include "Game.h"

Game* g_game = nullptr;

int main(int argc, char* args[]) {
    g_game = new Game();
    g_game -> init ("Platformer", 100, 100, 1280, 720, 0);

    while (g_game -> running()) {
        g_game -> handleEvents();
        g_game -> update();
        g_game -> render();
    }

    g_game -> clean();

    return 0;
}
