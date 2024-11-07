#pragma once
#include "structs.h"

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