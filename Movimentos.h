#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Defines.h"
#ifndef Stores_Undos
    #include "Stores_Undos.h"
#endif // Stores_Undos
#ifndef FimJogo
    #include "FimJogo.h"
#endif // FimJogo


// Funções que fazem com que as peças se movam para cima, baixo, esquerda, direita
void MoveUP(int [MAX_BOARD_POS][MAX_BOARD_POS], int);
void MoveDOWN(int [MAX_BOARD_POS][MAX_BOARD_POS], int);
void MoveLEFT(int [MAX_BOARD_POS][MAX_BOARD_POS], int);
void MoveRIGHT(int [MAX_BOARD_POS][MAX_BOARD_POS], int);

// Funções que somam 2 peças iguais consoante o movimento
void SomaUP(int [][MAX_BOARD_POS], int, int [MAX_UNDOS], int [][MAX_BOARD_POS]);
void SomaDOWN(int [][MAX_BOARD_POS], int, int [MAX_UNDOS], int [][MAX_BOARD_POS]);
void SomaLEFT(int [][MAX_BOARD_POS], int, int [MAX_UNDOS], int [][MAX_BOARD_POS]);
void SomaRIGHT(int [][MAX_BOARD_POS], int, int [MAX_UNDOS], int [][MAX_BOARD_POS]);

// Funções que aplicam todas as funções de movimento
void BotaCima(int, int, int [][MAX_BOARD_POS],int [][MAX_BOARD_POS],
              int [MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS], int [MAX_UNDOS]);
void BotaBaixo(int, int, int [][MAX_BOARD_POS],int [][MAX_BOARD_POS],
               int [MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS], int [MAX_UNDOS]);
void BotaLeft(int, int, int [][MAX_BOARD_POS],int [][MAX_BOARD_POS],
              int [MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS], int [MAX_UNDOS]);
void BotaRight(int, int, int [][MAX_BOARD_POS],int [][MAX_BOARD_POS],
               int [MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS], int [MAX_UNDOS]);


