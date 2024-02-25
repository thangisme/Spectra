#include <iostream>
#include "Game.h"

Game::Game() {}
Game::~Game() {}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL initialization succeeded" << std::endl;
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            std::cout << "Window creation succeeded" << std::endl;
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

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
    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    std::cout << "Cleaning game" << std::endl;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::update() {

}