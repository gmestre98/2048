#include "Defines.h"

// Declaração das funções relativas à parte gráfica
void InitEverything(int, int, TTF_Font **, SDL_Surface **, SDL_Window **, SDL_Renderer **, TTF_Font **, TTF_Font **);
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int, int );
SDL_Renderer* CreateRenderer(int, int, SDL_Window *);

// Funções para render de imagens, tabuleiro e mesa de jogo
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
int RenderLogo(int, int, SDL_Surface *, SDL_Renderer *);
void RenderTable(int, int *, int *, TTF_Font *, SDL_Surface **, SDL_Renderer *);
void RenderBoard(int [][MAX_BOARD_POS], SDL_Surface **, int, int, int, SDL_Renderer *);
void LoadValues(SDL_Surface **);
void UnLoadValues(SDL_Surface **);
void RenderImagens(SDL_Renderer *, char [STRING_SIZE], int, int);

// Funções para as decisões de um novo jogo
void DecideNovoJogo(int *, SDL_Renderer *, TTF_Font *, int *, int *, char [MEDIUMSTR], int *, SDL_Surface **, TTF_Font *);
void LimpaNome(char [MEDIUMSTR]);
int ClicouNaCaixa(SDL_Event, int, int, int, int);
void LeNome(SDL_Event, char [MEDIUMSTR], int *);
void ApagaLetra(SDL_Event, char [MEDIUMSTR], int *);
void LeTamanho(SDL_Event, int *);
void LeDificuldade(SDL_Event, int *);
void ClicksNovoJogo(SDL_Event, int *, int *, int *, int *, int *, int *, int *, char []);
