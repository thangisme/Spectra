#include <iostream>
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "MenuButton.h"

Game* Game::s_pInstance = 0;

Game::Game() : m_pWindow(0), m_pRenderer(0), m_bRunning(false), m_pGameStateManager(0){}
Game::~Game() {}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL initialization succeeded" << std::endl;
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            std::cout << "Window creation succeeded" << std::endl;
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            m_gameWidth = width;
            m_gameHeight = height;

            if (m_pRenderer != 0){
                std::cout << "Render creation succeeded" << std::endl;
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
            } else {
                std::cout << "Renderer init failed" << std::endl;
                return false;
            }
        } else {
            std::cout << "Window initialization failed" << std::endl;
            return false;
        }
    } else {
        std::cout << "SDL initialization failed" << std::endl;
        return false;
    }
    std::cout << "Initialization process succeed" << std::endl;
    m_bRunning = true;

    GameObjectFactory::Instance() ->registerType("SDLGameObject", new ShooterObjectCreator());
    GameObjectFactory::Instance() ->registerType("MenuButton", new MenuButtonCreator());
    GameObjectFactory::Instance() ->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance() ->registerType("Enemy", new EnemyCreator());
    m_pGameStateManager = new GameStateManager();
    m_pGameStateManager ->changeState(new MainMenuState());

    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);

    m_pGameStateManager -> render();

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    std::cout << "Cleaning game" << std::endl;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::handleEvents() {
    InputHandler::Instance() -> update();

    if (InputHandler::Instance() ->isKeyDown(SDL_SCANCODE_RETURN)) {
        m_pGameStateManager -> changeState(new PlayState());
    }
}

void Game::update() {
    m_pGameStateManager -> update();
}

void Game::setCurrentLevel(int currentLevel) {
    m_currentLevel = currentLevel;
    m_pGameStateManager ->changeState(new BetweenLevelState());
    m_bLevelComplete = false;
}