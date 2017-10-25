#include <stdio.h>
#include <stdlib.h>

#include "Defines.h"
#ifndef Movimentos
    #include "Movimentos.h"
#endif
#ifndef Stores_Undos
    #include "Stores_Undos.h"
#endif // Stores_Undos

void Move(int, int, int [][MAX_BOARD_POS], int [][MAX_BOARD_POS], int [],
          int [][MAX_BOARD_POS][MAX_BOARD_POS]);
int SomaCol(int [][MAX_BOARD_POS], int);
int SomaLin(int [][MAX_BOARD_POS], int);
int IgualnaLinha(int [][MAX_BOARD_POS], int);
int IgualnaColuna(int [][MAX_BOARD_POS], int);
