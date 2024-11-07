#include "src/include/SDL2/SDL.h"
#include <algorithm>
#include <vector>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 600;
const int RADIUS = 25; // Raio do círculo principal
const float TRAIL_MAX = RADIUS * 3; // Distância máxima antes do follower se mover
const float SPEED = 5.0f; // Velocidade de movimento

struct Point {
    float x;
    float y;
};

struct Pixel {
    int x;
    int y;
};

struct Line {
    Point p1;
    Point p2;
};

struct Circle {
    Point p;
    int r;
};

// Atualize moveTo para retornar a distância entre p1 e p2
float moveTo(Line& l) {
    float dx = l.p2.x - l.p1.x;
    float dy = l.p2.y - l.p1.y;
    float d = std::sqrt(dx * dx + dy * dy);

    if (d > 0) {
        float moveX = (dx / d) * SPEED;
        float moveY = (dy / d) * SPEED;

        l.p1.x += moveX;
        l.p1.y += moveY;

        if (d < SPEED) {
            l.p1 = l.p2;
        }
    }
    return d; // Retorne a distância
}

// Função para desenhar um círculo preenchido usando o algoritmo do ponto médio
void drawFilledCircle(SDL_Renderer* renderer, const Circle& c) {
    int x = 0, y = c.r;
    int d = 1 - c.r;  // Parâmetro de decisão inicial

    while (x <= y) {
        // Desenha linhas horizontais para preencher o círculo
        for (int i = c.p.x - x; i <= c.p.x + x; ++i) {
            SDL_RenderDrawPoint(renderer, i, c.p.y + y);  // Parte superior
            SDL_RenderDrawPoint(renderer, i, c.p.y - y);  // Parte inferior
        }
        for (int i = c.p.x - y; i <= c.p.x + y; ++i) {
            SDL_RenderDrawPoint(renderer, i, c.p.y + x);  // Lado direito
            SDL_RenderDrawPoint(renderer, i, c.p.y - x);  // Lado esquerdo
        }

        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }
    }
}

// Função para desenhar um círculo sem preenchimento
void drawCircle(SDL_Renderer* renderer, const Circle& c) {
    int x = 0, y = c.r;
    int d = 1 - c.r;  // Parâmetro de decisão inicial

    while (x <= y) {
        // Desenha pontos em todos os 8 octantes do círculo
        SDL_RenderDrawPoint(renderer, c.p.x + x, c.p.y + y);
        SDL_RenderDrawPoint(renderer, c.p.x - x, c.p.y + y);
        SDL_RenderDrawPoint(renderer, c.p.x + x, c.p.y - y);
        SDL_RenderDrawPoint(renderer, c.p.x - x, c.p.y - y);
        SDL_RenderDrawPoint(renderer, c.p.x + y, c.p.y + x);
        SDL_RenderDrawPoint(renderer, c.p.x - y, c.p.y + x);
        SDL_RenderDrawPoint(renderer, c.p.x + y, c.p.y - x);
        SDL_RenderDrawPoint(renderer, c.p.x - y, c.p.y - x);

        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }
    }
}

// Função para desenhar uma linha usando o struct Line
void DrawLine(SDL_Renderer* renderer, const Line& line) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Preto para a linha
    SDL_RenderDrawLine(renderer, static_cast<int>(line.p1.x), static_cast<int>(line.p1.y), 
                             static_cast<int>(line.p2.x), static_cast<int>(line.p2.y));
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Círculo Seguindo o Mouse", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    Point circle = { WIDTH / 2, HEIGHT / 2 }; // Posição inicial do círculo principal
    std::vector<Point> trail; // Vetor para armazenar o histórico de posições do círculo
    bool followMouse = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN)
                if (event.button.button == SDL_BUTTON_LEFT)
                    followMouse = true;
            if (event.type == SDL_MOUSEBUTTONUP)
                if (event.button.button == SDL_BUTTON_LEFT)
                    followMouse = false;
        }

        // Pega a posição do mouse
        Pixel mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        // Move o círculo principal em direção ao mouse se o botão esquerdo estiver pressionado
        if (followMouse) {
            Line dist;
            dist.p1 = {circle.x, circle.y};
            dist.p2 = {static_cast<float>(mouse.x), static_cast<float>(mouse.y)};
            moveTo(dist);
            circle = dist.p1;
        }

        // Adiciona a posição atual ao histórico da trilha
        trail.push_back(circle);

        // Calcula o comprimento total da trilha e remove o ponto mais antigo se exceder o comprimento máximo
        float totalLength = 0.0f;
        for (size_t i = 1; i < trail.size(); ++i) {
            Line segment = { trail[i - 1], trail[i] };
            totalLength += moveTo(segment);
            if (totalLength > TRAIL_MAX) {
                trail.erase(trail.begin()); // Remove apenas o ponto mais antigo
                break;
            }
        }

        // Limpa a tela
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Branco
        SDL_RenderClear(renderer);

        // Desenha a trilha
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Preto para a trilha
        for (size_t i = 1; i < trail.size(); ++i) {
            Line segment = { trail[i - 1], trail[i] };
            
            DrawLine(renderer, segment);
        }

        // Desenha o círculo principal
        Circle c = {circle,RADIUS};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
        drawCircle(renderer, c);

        SDL_RenderPresent(renderer);

        // Controla o FPS
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    // Limpeza
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}