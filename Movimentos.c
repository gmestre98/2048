#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Movimentos.h"


// Função que faz com que as peças se movam para cima
void MoveUP(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao)
{
    int a, i, j;
    for(a=0; a < dimensao; a++)
    {
        for(i=0; i < dimensao; i++)
        {
            for(j=0; j < dimensao; j++)
            {
                if ((board[i][j-1] == 0) && (j-1 >= 0))         // Condição para a peça se mover
                {
                    board[i][j-1] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }

}

// Função que faz com que as peças se movam para baixo
void MoveDOWN(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao)
{
    int a, i, j;
    for(a=0; a < dimensao; a++)
    {
        for(i = dimensao - 1; i >= 0; i--)
        {
            for(j = dimensao -1 ; j > 0; j--)
            {
                if ((board[i][j] == 0) && (j < dimensao))       // Condição para a peça se mover
                {
                    board[i][j] = board[i][j-1];
                    board[i][j-1] = 0;
                }
            }
        }
    }
}


//Função que faz com que as peças se movam para a esquerda
void MoveLEFT(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao)
{
    int a, i, j;
    for(a=0; a < dimensao; a++)
    {
        for(i=0; i < dimensao; i++)
        {
            for(j=0; j < dimensao; j++)
            {
                if ((board[i-1][j] == 0) && (i-1 >= 0))         // Condição para a peça se mover
                {
                    board[i-1][j] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
}

// Função que faz com que as peças se movam para a direita
void MoveRIGHT(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao)
{
    int a, i, j;
    for(a=0; a < dimensao; a++)
    {
        for(i = dimensao - 1; i > 0; i--)
        {
            for(j = dimensao -1 ; j >= 0; j--)
            {
                if ((board[i][j] == 0) && (i < dimensao))       // Condição para a peça se mover
                {
                    board[i][j] = board[i-1][j];
                    board[i-1][j] = 0;
                }
            }
        }
    }
}


// Função que soma as peças no movimento para cima
void SomaUP(int board[][MAX_BOARD_POS], int dimensao, int pontuacao[MAX_UNDOS], int board_anterior[][MAX_BOARD_POS])
{
    int i, j, k;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao; j++)
        {
            // Condição que verifica se pode existir soma
            if ((board[i][j] == board[i][j+1]) && (board[i][j] != 0))
            {
                board[i][j] = (board[i][j+1] + 1);
                board[i][j+1] = 0;
                // Actualização do vector da pontuação
                for(k = MAX_UNDOS - 2; k >= 0; k--)
                {
                    pontuacao[k+1] = pontuacao[k];
                }
                pontuacao[0] = pontuacao[0] + pow(2, board[i][j]);
            }
        }
    }
}


// Função que soma as peças no movimento para baixo
void SomaDOWN(int board[][MAX_BOARD_POS], int dimensao, int pontuacao[MAX_UNDOS], int board_anterior[][MAX_BOARD_POS])
{
    int i, j, k;
    for(i = dimensao - 1; i >= 0; i--)
    {
        for(j = dimensao -1 ; j > 0; j--)
        {
            // Condição que verifica se pode existir soma
            if ((board[i][j] == board[i][j-1]) && (board[i][j] != 0))
            {
                board[i][j] = (board[i][j-1] + 1);
                board[i][j-1] = 0;
                // Actualização do vector da pontuação
                for(k = MAX_UNDOS - 2; k >= 0; k--)
                {
                    pontuacao[k+1] = pontuacao[k];
                }
                pontuacao[0] = pontuacao[0] + pow(2, board[i][j]);
            }
        }
    }
}

// Função que soma as peças no movimento para a esquerda
void SomaLEFT(int board[][MAX_BOARD_POS], int dimensao, int pontuacao[MAX_UNDOS], int board_anterior[][MAX_BOARD_POS])
{
    int i, j, k;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao; j++)
        {
            // Condição que verifica se pode existir soma
            if ((board[i][j] == board[i+1][j]) && (board[i][j] != 0))
            {
                board[i][j] = (board[i+1][j] + 1);
                board[i+1][j] = 0;
                // Actualização do vector da pontuação
                for(k = MAX_UNDOS - 2; k >= 0; k--)
                {
                    pontuacao[k+1] = pontuacao[k];
                }
                pontuacao[0] = pontuacao[0] + pow(2, board[i][j]);
            }
        }
    }
}

// Função que soma as peças no movimento para a direita
void SomaRIGHT(int board[][MAX_BOARD_POS], int dimensao, int pontuacao[MAX_UNDOS], int board_anterior[][MAX_BOARD_POS])
{
    int i, j, k;
    for(i = dimensao - 1; i > 0; i--)
    {
        for(j = dimensao -1 ; j >= 0; j--)
        {
            // Condição que verifica se pode existir soma
            if ((board[i][j] == board[i-1][j]) && (board[i][j] != 0))
            {
                board[i][j] = (board[i-1][j] + 1);
                board[i-1][j] = 0;
                // Actualização do vector da pontuação
                for(k = MAX_UNDOS - 2; k >= 0; k--)
                {
                    pontuacao[k+1] = pontuacao[k];
                }
                pontuacao[0] = pontuacao[0] + pow(2, board[i][j]);
            }
        }
    }
}


// Move para cima
void BotaCima(int dificuldade, int dimensao_tabuleiro, int board[MAX_BOARD_POS][MAX_BOARD_POS],
              int board_anterior[][MAX_BOARD_POS], int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS],
              int pontuacao [MAX_UNDOS])
{
    Store(board, dimensao_tabuleiro, board_anterior);
    MoveUP(board, dimensao_tabuleiro);
    SomaUP(board, dimensao_tabuleiro, pontuacao, board_anterior);
    MoveUP(board, dimensao_tabuleiro);
    Gerador_pecas(board, dimensao_tabuleiro, board_anterior);
    Jogada_anterior(board, board_anterior, dimensao_tabuleiro, board_ultima_jogada);
}

// Move para baixo
void BotaBaixo(int dificuldade, int dimensao_tabuleiro, int board[MAX_BOARD_POS][MAX_BOARD_POS],
               int board_anterior[][MAX_BOARD_POS], int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS],
               int pontuacao [MAX_UNDOS])
{
    Store(board, dimensao_tabuleiro, board_anterior);
    MoveDOWN(board, dimensao_tabuleiro);
    SomaDOWN(board, dimensao_tabuleiro, pontuacao, board_anterior);
    MoveDOWN(board, dimensao_tabuleiro);
    Gerador_pecas(board, dimensao_tabuleiro, board_anterior);
    Jogada_anterior(board, board_anterior, dimensao_tabuleiro, board_ultima_jogada);
}

// Move para a esquerda
void BotaLeft(int dificuldade, int dimensao_tabuleiro, int board[MAX_BOARD_POS][MAX_BOARD_POS],
              int board_anterior[][MAX_BOARD_POS], int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS],
              int pontuacao [MAX_UNDOS])
{
    Store(board, dimensao_tabuleiro, board_anterior);
    MoveLEFT(board, dimensao_tabuleiro);
    SomaLEFT(board, dimensao_tabuleiro, pontuacao, board_anterior);
    MoveLEFT(board, dimensao_tabuleiro);
    Gerador_pecas(board, dimensao_tabuleiro, board_anterior);
    Jogada_anterior(board, board_anterior, dimensao_tabuleiro, board_ultima_jogada);
}

// Move para a direita
void BotaRight(int dificuldade, int dimensao_tabuleiro, int board[MAX_BOARD_POS][MAX_BOARD_POS],
               int board_anterior[][MAX_BOARD_POS], int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS],
               int pontuacao [MAX_UNDOS])
{
    Store(board, dimensao_tabuleiro, board_anterior);
    MoveRIGHT(board, dimensao_tabuleiro);
    SomaRIGHT(board, dimensao_tabuleiro, pontuacao, board_anterior);
    MoveRIGHT(board, dimensao_tabuleiro);
    Gerador_pecas(board, dimensao_tabuleiro, board_anterior);
    Jogada_anterior(board, board_anterior, dimensao_tabuleiro, board_ultima_jogada);
}
