#include "include/game.h"

Game::Game() {}
Game::~Game() {}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        isRunning = true;
    } else {
        isRunning = false;
    }
}
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
};
void Game::update() {
    // Get the mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
};
void Game::render() {
    SDL_RenderClear(renderer);
    //Render
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
};
void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

bool Game::running() {
    return isRunning;
}


