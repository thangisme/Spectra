#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "GameStateManager.h"
#include "GameObject.h"
#include "ShooterObject.h"
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

    void setPlayerLives(int lives);
    int getPlayerLives();

    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel();

    void setNextLevel(int nextLevel);
    const int getNextLevel();

    void setLevelComplete(bool levelComplete);
    const bool getLevelComplete();

    std::vector<std::string> getLevelFiles() const { return m_levelFiles; };

    float getScrollSpeed();
private:
    Game();
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;

    int m_gameWidth;
    int m_gameHeight;
    float m_scrollSpeed;

    int m_playerLives;

    int m_currentLevel;
    int m_nextLevel;
    int m_bLevelComplete;

    std::vector<std::string> m_levelFiles;

    GameStateManager* m_pGameStateManager;
};

#endif //PLATFORMER_GAME_H
