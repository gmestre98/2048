#include <stdio.h>
#include <stdlib.h>

#include "Stores_Undos.h"


// Função que verifica se houve alterações na posição das peças
int VerificaMudanca(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao,
                    int board_anterior[MAX_BOARD_POS][MAX_BOARD_POS])
{
    int i, j;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao; j++)
        {
            if(board_anterior[i][j]!= board[i][j])
            {
                return 1;       // Caso encontre uma posição diferente retorna 1
            }
        }
    }
    return 0;
}


// Função que guarda a posição das peças antes da última jogada
void Store(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao, int board_anterior[MAX_BOARD_POS][MAX_BOARD_POS])
{
    int i, j;
    for(i = 0; i < dimensao; i++)
    {
        for(j = 0; j < dimensao; j++)
        {
            board_anterior[i][j] = board[i][j];         // Copia as peças da jogada anterior
        }
    }
}



// Função que guarda a jogada anterior
void Jogada_anterior(int board[][MAX_BOARD_POS], int board_anterior[][MAX_BOARD_POS],
                     int dimensao, int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS])
{
    int i, j, k;
    if(VerificaMudanca(board, dimensao, board_anterior) == 1)
    {
        for(i=0; i < dimensao; i++)
        {
            for(j=0; j < dimensao; j++)
            {
                // Copia as peças do tabuleiro para a matriz 3D(Undos)
                for(k=MAX_UNDOS -2; k>=0 ; k--)
                {
                    board_ultima_jogada[k+1][i][j] = board_ultima_jogada[k][i][j];
                }
                board_ultima_jogada[0][i][j] = board_anterior[i][j];
            }
        }
    }
}


// Função que permite ao utilizador fazer undo
void Undo (int board[][MAX_BOARD_POS], int board_anterior[][MAX_BOARD_POS], int dimensao,
           int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS], int pontuacao[MAX_UNDOS])
{
    int i, j, k;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao; j++)
        {
            // Transforma a matriz actual na última matriz guardada
            board[i][j] = board_ultima_jogada[0][i][j];
            board_anterior[i][j] = board_ultima_jogada[0][i][j];
            // Passa os valores todos na dimensão k+1 para a dimensão k
            for(k=0; k < MAX_UNDOS - 1 ; k++)
            {
                board_ultima_jogada[k][i][j] = board_ultima_jogada[k+1][i][j];
            }
        }
    }
    for(k=0; k < MAX_UNDOS - 1; k++)
    {
            pontuacao[k] = pontuacao[k+1];
    }
}

