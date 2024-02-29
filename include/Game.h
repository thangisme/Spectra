#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "GameObject.h"
#include "Player.h"
#include "TextureManager.h"

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running() { return m_bRunning; }
private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;

    std::vector<GameObject*> m_gameObjects;
};

#endif //PLATFORMER_GAME_H
