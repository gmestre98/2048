#include "Defines.h"

int VerificaMudanca(int [MAX_BOARD_POS][MAX_BOARD_POS], int,            // Verifica se o tabuleiro foi alterado
                    int [MAX_BOARD_POS][MAX_BOARD_POS]);
void Store(int [MAX_BOARD_POS][MAX_BOARD_POS], int,                     // Guarda o último tabuleiro
           int [MAX_BOARD_POS][MAX_BOARD_POS]);
void Jogada_anterior(int [][MAX_BOARD_POS], int [][MAX_BOARD_POS],      // Guarda a última jogada feita
                     int, int [MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS]);
void Undo(int [][MAX_BOARD_POS], int [][MAX_BOARD_POS], int,            // Volta à jogada anterior
          int [MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS], int[MAX_UNDOS]);
