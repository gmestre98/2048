//include das  bibliotecas
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
#include "Gráfica.h"
#include "Movimentos.h"
#include "Stores_Undos.h"


/**
 * main function: entry point of the program
 * only to invoke other functions !
 */
int main(void)
{
    SDL_Window *window = NULL;                                                  // Janela
    SDL_Renderer *renderer = NULL;                                              // Renderer
    TTF_Font *serif = NULL;                                                     // Fonte Serif
    TTF_Font *Demonized = NULL;                                                 // Fonte Demonized
    TTF_Font *Queen = NULL;                                                     // Fonte Queen
    SDL_Surface *array_of_numbers[MAX_LEVELS], *imgs[2];                        // Números
    SDL_Event event;                                                            // Evento
    int delay = 100;                                                            // Delay
    int quit = 0;                                                               // Variável para quit do teclado
    int width = (TABLE_SIZE + LEFT_BAR_SIZE);                                   // Largura da Janela
    int height = TABLE_SIZE;                                                    // Altura da Janela
    int dimensao_tabuleiro = 1;                                                 // Dimensão do Tabuleiro
    int square_size_px, board_size_px, board_pos;                               // Variavéis do Tabuleiro
    char nome_jogador [MEDIUMSTR] = {0};                                        // Nome do Jogador
    int dificuldade = 1;                                                        // Dificuldade
    int pontuacao[MAX_UNDOS] = {0};                                             // Vector com as Pontuações do Jogo
    time_t tempoactual = 0;                                                     // Tempo Actual
    time_t tempoinicial = 0;                                                    // Tempo inicial
    time_t tempoguardado = 0;                                                   // Tempo do Jogo quando aberto
    int t=0;                                                                    // Enable da Contagem do tempo
    int board[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};                            // Tabuleiro
    int board_anterior[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};                   // Matriz anterior
    int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS] = {{{0}}}; // Jogadas anteriores
    int n_jogos=0;                                                              // Número de Jogos
    int dados = 0;                                                              // Posição da Leitura de dados para novo jogo
    int newgame = 0;                                                            // Indica se deve ser iniciado um novo jogo
    int clicou = 0;                                                             // Indica se foi selecionada a caixa
    int readname = 0;                                                           // Indica se deve ser lido o nome
    int posicaonome = 0;                                                        // Posição da letra do nome que estamos a ler
    Estatistica *Stats=NULL;                                                    // Estatisticas
    Stats = (Estatistica *)calloc(100, sizeof(Estatistica));
    if( Stats == NULL)
    {
        printf("ERROR, memory NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    board_pos = dimensao_tabuleiro;

    // Inicializa os gráficos do jogo
    InitEverything(width, height, &serif, imgs, &window, &renderer, &Demonized, &Queen);
    // Carrega as peças com os números
    LoadValues(array_of_numbers);


    // Enquanto o sinal quit for 0 este loop deixa o utilizador ir fazendo jogadas
    while( quit == 0 )
    {
        // Função que vai fazendo a contagem do tempo
        Tempo(&tempoactual, tempoinicial, t, dificuldade, dimensao_tabuleiro, board, tempoguardado);
        // while there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if(newgame == 1)
            {
                Novo_jogo(board, dimensao_tabuleiro, pontuacao, &t, board_ultima_jogada);
                newgame = 0;
                clicou = 0;
                // Inicialização do tempo
                tempoinicial = time(NULL);
                tempoguardado = 0;
            }
            // Condição que indica que o jogo foi fechado
            if( event.type == SDL_QUIT )
            {
                quit = 1;
            }
            // Condição que indica que uma tecla foi pressionada
            else if ( event.type == SDL_KEYDOWN )
            {
                if(readname == 1)                                                  // Leitura do nome de jogador
                {
                    if (posicaonome > 0)
                    {
                        ApagaLetra(event, nome_jogador, &posicaonome);
                    }
                    if (posicaonome < NAMESIZE)
                    {
                        LeNome(event, nome_jogador, &posicaonome);
                    }
                }
                else if(dados == 0)
                {
                    switch ( event.key.keysym.sym )
                    {
                    // Jogar para cima
                    case SDLK_UP:
                        if(Ganhar(dificuldade, dimensao_tabuleiro, board) != 1)
                        {
                            BotaCima(dificuldade, dimensao_tabuleiro, board, board_anterior, board_ultima_jogada, pontuacao);
                        }
                        break;
                    // Jogar para baixo
                    case SDLK_DOWN:
                        if(Ganhar(dificuldade, dimensao_tabuleiro, board) != 1)
                        {
                            BotaBaixo(dificuldade, dimensao_tabuleiro, board, board_anterior, board_ultima_jogada, pontuacao);
                        }
                        break;
                    // Jogar para a esquerda
                    case SDLK_LEFT:
                        if(Ganhar(dificuldade, dimensao_tabuleiro, board) != 1)
                        {
                            BotaLeft(dificuldade, dimensao_tabuleiro, board, board_anterior, board_ultima_jogada, pontuacao);
                        }
                        break;
                    // Jogar para a direita
                    case SDLK_RIGHT:
                        if(Ganhar(dificuldade, dimensao_tabuleiro, board) != 1)
                        {
                            BotaRight(dificuldade, dimensao_tabuleiro, board, board_anterior, board_ultima_jogada, pontuacao);
                        }
                        break;
                    // Termina o programa
                    case SDLK_q:
                        quit = 1;
                        // Guarda o jogo que está a ser jogado nesse momento
                        SaveStats(n_jogos, Stats, dimensao_tabuleiro, dificuldade, board, pontuacao, tempoactual, nome_jogador);
                        break;
                    // Novo jogo
                    case SDLK_n:
                        // Guarda o jogo que está a ser jogado nesse momento
                        SaveStats(n_jogos, Stats, dimensao_tabuleiro, dificuldade, board, pontuacao, tempoactual, nome_jogador);
                        // Alteração dos valores para o começo de um novo jogo
                        ResetVars(board, &board_pos);
                        n_jogos ++;
                        dados = 4;
                        break;
                    // Faz undo
                    case SDLK_u:
                        if(Ganhar(dificuldade, dimensao_tabuleiro, board) == 0)
                        {
                            Undo(board, board_anterior, dimensao_tabuleiro, board_ultima_jogada, pontuacao);
                        }
                        break;
                    // Abre um jogo guardado
                    case SDLK_o:
                        SaveStats(n_jogos, Stats, dimensao_tabuleiro, dificuldade, board, pontuacao, tempoactual, nome_jogador);
                        OpenGame(&dimensao_tabuleiro, &dificuldade, &tempoguardado, nome_jogador, board, pontuacao);
                        // Inicialização do tempo
                        tempoinicial = time(NULL);
                        break;
                    case SDLK_s:
                        Save(dimensao_tabuleiro, dificuldade, tempoactual, nome_jogador, board, pontuacao);
                        break;
                    default:
                        break;
                    }
                }
            }
            else if( event.type == SDL_MOUSEBUTTONDOWN)
            {
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        if(ClicouNaCaixa(event, UNDOXMIN+VARUNDO, UNDOXMAX-VARUNDO, UNDOYMIN+VARUNDO, UNDOYMAX-VARUNDO) == 1)
                        {
                            Undo(board, board_anterior, dimensao_tabuleiro, board_ultima_jogada, pontuacao);
                        }
                        else
                        {
                            ClicksNovoJogo(event, &dados, &dimensao_tabuleiro, &board_pos, &clicou, &readname, &posicaonome, &dificuldade, nome_jogador);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        RenderTable( board_pos, &board_size_px, &square_size_px, serif, imgs, renderer);            // Render da mesá de jogo
        RenderBoard(board, array_of_numbers, board_pos, board_size_px, square_size_px, renderer);   // Render do tabuleiro
        RenderStats(renderer, dificuldade, pontuacao, tempoactual, Queen, nome_jogador);                      // Render da estatistica
        if (Ganhar(dificuldade, dimensao_tabuleiro, board) == 1)
        {
            RenderImagens(renderer, ".//Vitoria_Derrota//win.bmp", XVICTORY, YVICTORY);             // Render da imagem de vitória
        }
        if (Perder(dimensao_tabuleiro, board) == 1)
        {
            RenderImagens(renderer, ".//Vitoria_Derrota//defeat.bmp", XDEFEAT, YDEFEAT);            // Render da imagem de derrota
        }
        RenderImagens(renderer, "Undo.bmp", UNDOXMIN, UNDOYMIN);                                    // Render do botão de undo
        DecideNovoJogo(&dados, renderer, serif, &newgame, &clicou, nome_jogador, &readname,         // Render dos menus de novo jogo
                       array_of_numbers, Queen);
        Instrucoes_jogo(renderer, serif);                                                           // Render das instruções
        SDL_RenderPresent(renderer);                                                                // Aplicação de todo o render
        SDL_Delay( delay );
    }
    WriteStats(n_jogos, Stats);
    UnLoadValues(array_of_numbers);
    TTF_CloseFont(serif);
    TTF_CloseFont(Demonized);
    TTF_CloseFont(Queen);
    SDL_FreeSurface(imgs[0]);
    SDL_FreeSurface(imgs[1]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
