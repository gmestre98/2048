#include "FimJogo.h"


/**
 * Shows some information about the game:
 * - Level to achieve (difficulty)
 * - Score of the game
 * - Time spent in seconds
 * \param _renderer renderer to handle all rendering in a window
 * \param _level current level
 * \param _score actual score
 * \param _time time to display in seconds
 */
void RenderStats( SDL_Renderer *_renderer, int _level, int _score[MAX_UNDOS], int _time, TTF_Font* _font, char nome_jogador[])
{
    int nivel;
    char charnivel[STRING_SIZE];
    char charpontuacao[STRING_SIZE];
    char chartime[STRING_SIZE];
    SDL_Color white = {255, 255, 255};
    // Conversão da dificuldade para o número que se pretende alcançar
    nivel = pow(2, _level);



    // Conversão dos valores do tipo int para o tipo char
    sprintf(charnivel, "%d", nivel);
    sprintf(charpontuacao, "%d", _score[0]);
    sprintf(chartime, "%d", _time);


    // Render das estatísticas correntes referentes ao nivel, pontuação, nome de jogador e tempo de jogo nas janelas
    if(_level == 1)
    {
        RenderText(STATSX1 + STATSVAR1, STATSY2, "0", _font, &white, _renderer);
    }
    else
    {
        RenderText(STATSX1 + STATSVAR2, STATSY2, charnivel, _font, &white, _renderer);
    }
    if(nome_jogador[0] != 0)
    {
        RenderText(STATSX2, STATSY3, nome_jogador, _font, &white, _renderer);
    }
    RenderText(STATSX2, STATSY2, charpontuacao, _font, &white, _renderer);
    RenderText(STATSX3, STATSY2, chartime, _font, &white, _renderer);
    RenderText(STATSX1, STATSY1, "Dificuldade", _font, &white, _renderer);
    RenderText(STATSX2, STATSY1, "Pontuacao", _font, &white, _renderer);
    RenderText(STATSX3, STATSY1, "Tempo", _font, &white, _renderer);
    RenderText(STATSX1 + STATSVAR1, STATSY3, "Jogador:", _font, &white, _renderer);
}


// Função que gera 2 peças 2 ou 4 aleatoriamente no inicio do jogo
void Gerador_pecas_inicio(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao)
{
    int i=0;
    int j=0;
    int k=0;
    int l=0;
    srand(time(NULL));
    // Atribuição de um valor random ao i e ao j(posição do tabuleiro)
    i = (rand() %dimensao);
    j = (rand() %dimensao);
    // Atribuição de um valor random ao k e ao l
    // Verificação de que a casa gerada é diferente da gerada anteriormente
    do
    {
        k = (rand() %dimensao);
        l = (rand() %dimensao);
    }
    while((k == i) && (l == j));
    // Atribuição de peças(2 ou 4) às posições geradas
    board[i][j] = (rand() % 2 + 1);
    board[k][l] = (rand() % 2 + 1);
}


// Função que gera a peça 2 ou 4 aleatoriamente caso tenham existido alterações no tabuleiro
void Gerador_pecas(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao,
                   int board_anterior[MAX_BOARD_POS][MAX_BOARD_POS])
{
    int i=0;
    int j=0;
    int a=0;
    srand(time(NULL));
    // Verificação se o tabuleiro cumpre as condições para que uma peça seja gerada
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao; j++)
        {
            // Verifica se estamos em condições de gerar peças
            if((VerificaMudanca(board, dimensao, board_anterior) == 1) && (board[i][j] == 0))
            {
                a=1;
            }
        }
    }

    // Criação da peça caso tenham existido mudanças no tabuleiro
    if(a == 1)
    {
        do
        {
            // Atribuição de valores random ao i e ao j
            i = (rand() %dimensao);
            j = (rand() %dimensao);
            // Verificação de que a posição não tem peças
            if(board[i][j] == 0)
            {
                // Atribuição de uma peça(2 ou 4) à posição gerada
                board[i][j] = ((rand() % 2) + 1);
                a = 0;
            }
            else
                a = 1;
        }
        while(a == 1);
    }
}

// Função que imprime as instruções de jogo
void Instrucoes_jogo(SDL_Renderer *_renderer, TTF_Font *_font1)
{
    SDL_Color black = {0, 0, 0};
    RenderText(INSTRUCOES1X, INSTRUCOES1Y, "Teclas:", _font1, &black, _renderer);
    RenderText(INSTRUCOES1X, INSTRUCOES2Y, "N-Novo jogo", _font1, &black, _renderer);
    RenderText(INSTRUCOES1X, INSTRUCOES3Y, "Q-Fecha o programa", _font1, &black, _renderer);
    RenderText(INSTRUCOES1X, INSTRUCOES4Y, "U-Faz Undo", _font1, &black, _renderer);
    RenderText(INSTRUCOES1X, INSTRUCOES5Y, "O-Abre o ultimo jogo", _font1, &black, _renderer);
    RenderText(INSTRUCOES1X, INSTRUCOES6Y, "  desse tamanho", _font1, &black, _renderer);
    RenderText(INSTRUCOES1X, INSTRUCOES7Y, "S-Grava o jogo actual", _font1, &black, _renderer);
}

// Função que inicia um novo jogo
void Novo_jogo(int board[MAX_BOARD_POS][MAX_BOARD_POS], int dimensao, int pontuacao[MAX_UNDOS], int* t,
               int board_ultima_jogada[MAX_UNDOS][MAX_BOARD_POS][MAX_BOARD_POS])
{
    int i, j, k;
    for(i = 0; i < dimensao; i++)
    {
        for(j = 0; j < dimensao; j++)
        {
            // Definição de todas as posições a 0
            board[i][j] = 0;
        }
    }
    // Posicionamento de duas peças, 2 ou 4 no tabuleiro aleatoriamente
    Gerador_pecas_inicio(board, dimensao);
    // Flag que faz reset do tempo passa a 1
    *t = 1;
    for(k=0; k < MAX_UNDOS; k++)
    {
        for(i=0; i < MAX_BOARD_POS; i++)
        {
            for(j=0; j < MAX_BOARD_POS; j++)
            {
                // reset do board que guarda a ultima jogada de modo a nao permitir o undo
                board_ultima_jogada[k][i][j] = board[i][j];
            }
        }
        // reset da pontuacao
        pontuacao[k] = 0;
    }
}

// Função que gera o tempo actual
void Tempo(time_t* tempoactual, time_t tempoinicial, int t, int dificuldade, int dimensao, int board[][MAX_BOARD_POS], time_t tempoguardado)
{
    if(t==1)
    {
        // Definição da contagem do tempo
        if((Ganhar(dificuldade, dimensao, board) != 1) && (Perder(dimensao, board) != 1))
        {
            *tempoactual = time(NULL) - tempoinicial + tempoguardado;
        }
        // Bloqueio do tempo quando se ganha ou perde
        else
        {
            *tempoactual = *tempoactual;
        }
    }
}

// Função que informa o utilizador quando o mesmo ganhou o jogo
int Ganhar(int dificuldade, int dimensao, int board[MAX_BOARD_POS][MAX_BOARD_POS])
{
    int ganhar=0;
    int i, j;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao; j++)
        {
            // Caso o valor de uma das peças atinja o valor porposto ganhar passa a 1
            if (board[i][j] == dificuldade)
                ganhar=1;
        }
    }
    return ganhar;
}
// Função que informa o utilizador quando o mesmo perde o jogo
int Perder(int dimensao, int board[MAX_BOARD_POS][MAX_BOARD_POS])
{
    int i, j;
    int contagem=0;
    int perder=0;
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao; j++)
        {
            // Caso uma das posições não tenha 0 a flag contagem é incrementada
            if(board[i][j] == 0)
                contagem ++;
        }
    }
    for(i=0; i < dimensao - 1; i++)
    {
        for(j=0; j < dimensao; j++)
            // Caso seja possivel somar para cima ou para baixo a flag contagem é incrementada
            if((board[i+1][j] == board[i][j]) || (board[i][j] == board[i+1][j]))
                contagem ++;
    }
    for(i=0; i < dimensao; i++)
    {
        for(j=0; j < dimensao - 1; j++)
        {
            // Caso seja possivel somar para cima ou para baixo a flag contagem é incrementada
            if ((board[i][j+1] == board[i][j]) || (board[i][j] == board[i][j+1]))
                contagem ++;
        }
    }
    // Se nenhuma das condições anteriores acontecer, a flag contagem é 0 e portanto perder=1
    if(contagem == 0)
        perder=1;

    return perder;
}

// Função que guarda as estatísticas referentes a cada jogo feito desde que o programa foi aberto
void SaveStats(int n_jogos, Estatistica *Stats, int dimensao, int dificuldade, int board[][MAX_BOARD_POS],
               int pontuacao[], time_t tempoactual, char nome_jogador[])
{
    int i=0;
    int j=0;
    ((Stats)[n_jogos]).dims = dimensao;
    ((Stats)[n_jogos]).level = pow(2, dificuldade);
    ((Stats)[n_jogos]).maior_peca = 0;
    for(i=0; i < MAX_BOARD_POS; i++)
    {
        for(j=0; j < MAX_BOARD_POS; j++)
        {
            if(board[i][j] > ((Stats)[n_jogos]).maior_peca)
            {
                ((Stats)[n_jogos]).maior_peca = pow(2, board[i][j]);
            }
        }
    }
    ((Stats)[n_jogos]).pont_max = pontuacao[0];
    ((Stats)[n_jogos]).tempojogo = tempoactual;
    ((Stats)[n_jogos]).names = (char*)malloc(8*sizeof(char));
    if(((Stats)[n_jogos]).names == NULL)
    {
        printf("ERROR! Memory was NOT allocated!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(((Stats)[n_jogos]).names, nome_jogador);
}

// Função que escreve as estatísticas quando o programa é fechado
void WriteStats(int n_jogos, Estatistica *Stats)
{
    int a=0;
    FILE *fp = NULL;

    // Abertura do ficheiro em modo de escrita
    fp = fopen("stats.txt", "a");
    // Verificação de que o ficheiro foi aberto correctamente
    if (fp == NULL)
    {
        printf("File was NOT open sucessfully !!\n");
        exit(EXIT_FAILURE);
    }

    // Ciclo que para cada jogo escreve as estatísticas
    for(a=n_jogos; a > 0; a--)
    {
        // Escrita do nome do jogador no ficheiro
        fprintf(fp, "Nome do jogador:\t %s\n", Stats[a].names);

        // Escrita da pontuação máxima do jogo
        fprintf(fp, "Pontuação máxima obtida:\t %d\n", Stats[a].pont_max);

        // Escrita da maior peça obtida nesse jogo
        fprintf(fp, "Maior peça obtida:\t %ld\n", Stats[a].maior_peca);

        // Escrita do tempo gasto nesse jogo
        fprintf(fp, "Tempo de jogo:\t %d\n", Stats[a].tempojogo);

        // Escrita da dimensão desse jogo
        fprintf(fp, "Dimensão do tabuleiro:\t %d\n", Stats[a].dims);

        // Escrita da dificuldade escolhida para esse jogo
        fprintf(fp, "Dificuldade do jogo:\t %ld\n", Stats[a].level);

        fprintf(fp, "\n\n");
    }
    fclose(fp);
}

// Função que faz reset de duas variaveias
void ResetVars(int board[][MAX_BOARD_POS], int *board_pos)
{
    int i = 0;
    int j = 0;
    for(i=0; i < MAX_BOARD_POS; i++)
    {
        for(j=0; j < MAX_BOARD_POS; j++)
        {
            board[i][j] = 0;
        }
    }
    *board_pos = 1;
}

// Função que guarda num ficheiro o jogo fechado
void Save(int dimensao, int dificuldade, time_t tempoactual, char nome_jogador[], int board[][MAX_BOARD_POS], int pontuacao[])
{
    int i = 0;
    int j = 0;
    FILE *fp = NULL;


    // Consoante a dimensão, o jogo é guardado num ficheiro diferente
    switch(dimensao)
    {
    case 4:
        fp = fopen("JogoAnterior4.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    case 5:
        fp = fopen("JogoAnterior5.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    case 6:
        fp = fopen("JogoAnterior6.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    case 7:
        fp = fopen("JogoAnterior7.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    case 8:
        fp = fopen("JogoAnterior8.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    case 9:
        fp = fopen("JogoAnterior9.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    case 10:
        fp = fopen("JogoAnterior10.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    case 11:
        fp = fopen("JogoAnterior11.txt", "w");
        if(fp == NULL)
        {
            printf("ERRO na abertura do ficheiro!\n");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        printf("O ficheiro desejado não existe!\n");
        exit(EXIT_FAILURE);
    }
    // Impressão dos dados no ficheiro
    fprintf(fp, "%d\n", dimensao);
    fprintf(fp, "%d\n", dificuldade);
    fprintf(fp, "%ld\n", tempoactual);
    fprintf(fp, "%s\n", nome_jogador);
    for(i=0; i < MAX_BOARD_POS; i++)
    {
        for(j=0; j < MAX_BOARD_POS; j++)
        {
            fprintf(fp, "%d,", board[i][j]);
        }
        fprintf(fp, "\n");
    }
    for(i=0; i < MAX_UNDOS; i++)
    {
        fprintf(fp, "%d,", pontuacao[i]);
    }
    fclose(fp);
}

// Função que abre um jogo guardado
void OpenGame(int *dimensao, int *dificuldade, time_t *tempoactual, char nome_jogador[],
              int board[][MAX_BOARD_POS], int pontuacao[])
{
    int i = 0;
    int j = 0;
    int k = 0;
    FILE *fp = NULL;
    char str[STRING_SIZE];
    char *str2 = NULL;

    // Consoante a dimensão o jogo é guardado num ficheiro diferente
    switch(*dimensao)
    {
    case 4:
        fp = fopen("JogoAnterior4.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    case 5:
        fp = fopen("JogoAnterior5.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    case 6:
        fp = fopen("JogoAnterior6.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    case 7:
        fp = fopen("JogoAnterior7.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    case 8:
        fp = fopen("JogoAnterior8.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    case 9:
        fp = fopen("JogoAnterior9.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    case 10:
        fp = fopen("JogoAnterior10.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    case 11:
        fp = fopen("JogoAnterior11.txt", "r");
        if(fp == NULL)
        {
            printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
            return;
        }
        break;
    default:
        printf("Não existe nenhum ficheiro para o tamanho de tabuleiro actual!\n");
        return;
    }
    // Passagem dos dados do ficheiro para as variaveis desejadas
    fgets(str, STRING_SIZE, fp);
    if(str != NULL)
    {
        sscanf(str, "%d", dimensao);
    }
    fgets(str, STRING_SIZE, fp);
    if(str != NULL)
    {
        sscanf(str, "%d", dificuldade);
    }
    fgets(str, STRING_SIZE, fp);
    if(str != NULL)
    {
        sscanf(str, "%ld", tempoactual);
    }

    fgets(str, STRING_SIZE, fp);
    if(str != NULL)
    {
        while(str[i] != '\n')
        {
            nome_jogador[i] = str[i];
            i++;
        }
    }
    fgets(str, STRING_SIZE, fp);
    for(i=0; i < MAX_BOARD_POS; i++)
    {
        fgets(str, STRING_SIZE, fp);
        if(str != NULL)
        {
            str2 = strtok(str, ",");
        }
        for(j=0; j < MAX_BOARD_POS  &&  str2 != NULL; j++)
        {
            sscanf(str2, "%d", &k);
            board[i][j] = k;
            str2 = strtok(NULL, ",");
        }
    }
    fgets(str, STRING_SIZE, fp);
    if(str != NULL)
    {
        str2 = strtok(str, ",");
    }
    for(i=0; i < MAX_UNDOS; i++)
    {
        if(str2 != NULL)
        {
            sscanf(str2, "%d", &k);
            pontuacao[i] = k;
        }
        str2 = strtok(NULL, ",");
    }
    fclose(fp);
}
