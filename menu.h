#include "src/include/SDL2/SDL.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct MenuOption {
    const char* text;
    SDL_Color color;
};

// Assumindo que temos 3 opções de menu
void renderMenu(SDL_Renderer* renderer, MenuOption (&options)[3], int selectedOption) {
    for (int i = 0; i < 3; ++i) {
        SDL_Color color = (i == selectedOption) ? SDL_Color{ 255, 0, 0 } : SDL_Color{ 255, 255, 255 };

        SDL_Rect optionRect = { SCREEN_WIDTH / 2 - 50, 100 + i * 50, 100, 40 };
        
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderFillRect(renderer, &optionRect);
    }
}


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Menu Interface", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Array fixo de opções de menu
    MenuOption options[] = {
        { "Start Game", { 255, 255, 255 } },
        { "Options", { 255, 255, 255 } },
        { "Quit", { 255, 255, 255 } }
    };
    int optionsCount = sizeof(options) / sizeof(MenuOption); // número de opções no array
    int selectedOption = 0;

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                running = false;
                
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        selectedOption = (selectedOption - 1 + optionsCount) % optionsCount;
                        break;
                    case SDLK_DOWN:
                        selectedOption = (selectedOption + 1) % optionsCount;
                        break;
                    case SDLK_RETURN:
                        if (std::string(options[selectedOption].text) == "Quit") {
                            running = false;
                        } else {
                            std::cout << "Selected Option: " << options[selectedOption].text << "\n";
                        }
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderMenu(renderer, options, selectedOption);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
