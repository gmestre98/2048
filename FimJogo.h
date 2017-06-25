#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "Defines.h"
#ifndef Grafica
    #include "Gráfica.h"
#endif
#ifndef Stores_Undos
    #include "Stores_Undos.h"
#endif

typedef struct Estatistica{
    int pont_max;
    long int maior_peca;
    int tempojogo;
    int dims;
    long int level;
    char *names;
}Estatistica;

// Funções que geram as peças
void Gerador_pecas_inicio(int [MAX_BOARD_POS][MAX_BOARD_POS], int);
void Gerador_pecas(int [MAX_BOARD_POS][MAX_BOARD_POS], int, int [MAX_BOARD_POS][MAX_BOARD_POS]);

// Função que dá ao utilizador as instruções de jogo
void Instrucoes_jogo(SDL_Renderer *, TTF_Font *);

// Funções para novo jogo
void Novo_jogo(int [MAX_BOARD_POS][MAX_BOARD_POS], int, int [MAX_UNDOS], int*,
               int [MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS]);
void ResetVars(int [][MAX_BOARD_POS], int *);

// Função que gera o tempo
void Tempo(time_t*, time_t, int, int, int, int [][MAX_BOARD_POS], time_t);

// Funções para vitória e derrota
int Ganhar(int, int, int [MAX_BOARD_POS][MAX_BOARD_POS]);
int Perder(int, int [MAX_BOARD_POS][MAX_BOARD_POS]);

// Funções para a estatística
void SaveStats(int, Estatistica *, int, int, int [][MAX_BOARD_POS], int [], time_t, char []);
void WriteStats(int, Estatistica *);
void RenderStats( SDL_Renderer *, int, int[MAX_UNDOS], int, TTF_Font*, char []);

// Funções para abrir um jogo guardado
void Save(int, int, time_t, char [], int [][MAX_BOARD_POS], int []);
void OpenGame(int *, int *, time_t *, char[], int[][MAX_BOARD_POS], int []);
