#include <stdio.h>
#include <stdlib.h>
#include "Playalone.h"

void Move(int dificuldade, int dimensao, int board[][MAX_BOARD_POS],
          int board_anterior[][MAX_BOARD_POS], int pontuacao[],
          int board_ultima_jogada[][MAX_BOARD_POS][MAX_BOARD_POS])
{
    int lin1 = 0;
    int colultima = 0;
    lin1 = SomaLin(board, 0);
    colultima = SomaCol(board, dimensao-1);
    if(IgualnaLinha(board, dimensao) == 1)
    {
        BotaRight(dificuldade, dimensao, board, board_anterior, board_ultima_jogada,
                  pontuacao);
    }
    else if(IgualnaColuna(board, dimensao) == 1)
    {
        BotaBaixo(dificuldade, dimensao, board, board_anterior, board_ultima_jogada,
                  pontuacao);
    }
    else if(lin1 > colultima)
    {
        BotaRight(dificuldade, dimensao, board, board_anterior,board_ultima_jogada,
                  pontuacao);
        if(VerificaMudanca(board, dimensao, board_anterior) != 1)
        {
            BotaBaixo(dificuldade, dimensao, board, board_anterior, board_ultima_jogada,
                  pontuacao);
            if(VerificaMudanca(board, dimensao, board_anterior) != 1)
            {
                BotaLeft(dificuldade, dimensao, board, board_anterior,
                        board_ultima_jogada, pontuacao);
                BotaRight(dificuldade, dimensao, board, board_anterior,board_ultima_jogada,
                          pontuacao);
                if(VerificaMudanca(board, dimensao, board_anterior) != 1)
                {
                    BotaCima(dificuldade, dimensao, board, board_anterior,
                            board_ultima_jogada, pontuacao);
                    BotaBaixo(dificuldade, dimensao, board, board_anterior, board_ultima_jogada,
                            pontuacao);
                }
            }
        }
    }
    else
    {
        BotaBaixo(dificuldade, dimensao, board, board_anterior,board_ultima_jogada,
                  pontuacao);
        if(VerificaMudanca(board, dimensao, board_anterior) != 1)
        {
            BotaRight(dificuldade, dimensao, board, board_anterior, board_ultima_jogada,
                  pontuacao);
            if(VerificaMudanca(board, dimensao, board_anterior) != 1)
            {
                BotaLeft(dificuldade, dimensao, board, board_anterior,
                        board_ultima_jogada, pontuacao);
                BotaRight(dificuldade, dimensao, board, board_anterior,board_ultima_jogada,
                          pontuacao);
                if(VerificaMudanca(board, dimensao, board_anterior) != 1)
                {
                    BotaCima(dificuldade, dimensao, board, board_anterior,
                            board_ultima_jogada, pontuacao);
                    BotaBaixo(dificuldade, dimensao, board, board_anterior, board_ultima_jogada,
                            pontuacao);
                }
            }
        }
    }
}

int SomaCol(int board[][MAX_BOARD_POS], int col)
{
    int a = 0;
    int j = 0;
    for(j=0; j < MAX_BOARD_POS; j++)
    {
        a += board[col][j];
    }
    return a;
}

int SomaLin(int board[][MAX_BOARD_POS], int lin)
{
    int a = 0;
    int i = 0;
    for(i=0; i < MAX_BOARD_POS; i++)
    {
        a += board[i][lin];
    }
    return a;
}

int IgualnaLinha(int board[][MAX_BOARD_POS], int dimensao)
{
    int a = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao -1; j++)
        {
            for(a=j+1; a < dimensao; a++)
            {
                if(board[i][j] != 0  &&  board[i][j] == board[i][a])
                {
                    k = 1;
                }
            }
        }
    }
    return k;
}

int IgualnaColuna(int board[][MAX_BOARD_POS], int dimensao)
{
    int a = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao -1; j++)
        {
            for(a=j; a < dimensao-1; a++)
            {
                if(board[j][i] == board[a+1][i])
                {
                    k = 1;
                }
            }
        }
    }
    return k;
}
