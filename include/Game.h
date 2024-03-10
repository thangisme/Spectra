#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "GameStateManager.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include "TextureManager.h"

class Game {
public:
    static Game* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }
    ~Game();
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit() { m_bRunning = false; };
    bool running() { return m_bRunning; }
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    GameStateManager* getStateManager() { return m_pGameStateManager; }

    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }
private:
    Game();
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;

    int m_gameWidth;
    int m_gameHeight;

    GameStateManager* m_pGameStateManager;
};

#endif //PLATFORMER_GAME_H
