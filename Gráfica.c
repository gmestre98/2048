#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "Gráfica.h"


// Função que faz o load dos números para um vector de imagens
void LoadValues(SDL_Surface **_array_of_numbers)
{
    int i;
    char filename[STRING_SIZE];

    // Leitura das imagens todas para um vector
    for ( i = 0 ; i < MAX_LEVELS; i++ )
    {
        // Criação de um filename
        sprintf(filename, ".//numbers//value_%02d.jpg", i+1);
        // Leitura das imagens
        _array_of_numbers[i] = IMG_Load(filename);
        // Verifica os erros
        if (_array_of_numbers[i] == NULL)
        {
            printf("Unable to load image: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }
}



// Função que liberta a memória de todas as peças
void UnLoadValues(SDL_Surface **_array_of_numbers)
{
    for ( int i = 0 ; i < MAX_LEVELS; i++ )
    {
        SDL_FreeSurface(_array_of_numbers[i]);
    }
}

/**
 * RenderBoard: renders the board
 * \param _board multidimensional array with the board numbers
 * \param _array_of_numbers vector with all loaded images
 * \param _board_pos number of positions in the board
 * \param _board_size_px size of the board in pixels
 * \param _square_size_px size of each square
 * \param _renderer renderer to handle all rendering in a window
 */
void RenderBoard(int _board[][MAX_BOARD_POS], SDL_Surface **_array_of_numbers, int _board_pos,
                 int _board_size_px, int _square_size_px, SDL_Renderer *_renderer )
{
    int x_corner, y_corner;
    SDL_Rect boardPos;
    SDL_Texture *number_text;

    // corner of the board
    x_corner = (TABLE_SIZE - _board_size_px) >> 1;
    y_corner = (TABLE_SIZE - _board_size_px - 15);

    // renders the squares where the numbers will appear
    for ( int i = 0; i < _board_pos; i++ )
    {
        for ( int j = 0; j < _board_pos; j++ )
        {
            // basic check
            if ( _board[i][j] > 23 || _board[i][j] < 0 )
            {
                printf("Invalid board value: RenderBoard\n");
                exit(EXIT_FAILURE);
            }
            // only draws a number if it corresponds to a non-empty space
            if ( _board[i][j] != 0 )
            {
                // define the size and copy the image to display
                boardPos.x = x_corner + (i+1)*SQUARE_SEPARATOR + i*_square_size_px;
                boardPos.y = y_corner + (j+1)*SQUARE_SEPARATOR + j*_square_size_px;
                boardPos.w = _square_size_px;
                boardPos.h = _square_size_px;
                number_text = SDL_CreateTextureFromSurface( _renderer, _array_of_numbers[ _board[i][j] - 1] );
                SDL_RenderCopy( _renderer, number_text, NULL, &boardPos );
                // destroy texture
                SDL_DestroyTexture(number_text);
            }
        }
    }
}


/**
 * RenderTable: Draws the table where the game will be played, namely:
 * -  some texture for the background
 * -  the right part with the IST logo and the student name and number
 * -  the grid for game board with squares and seperator lines
 * \param _board_pos number of squares in the board
 * \param _font font used to render the text
 * \param _img surfaces with the table background and IST logo (already loaded)
 * \param _renderer renderer to handle all rendering in a window
 */
void RenderTable( int _board_pos, int *_board_size_px, int *_square_size_px, TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer )
{
    SDL_Color black = { 0, 0, 0 }; // black
    SDL_Color light = { 205, 193, 181 };
    SDL_Color dark = { 120, 110, 102 };
    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest, board, board_square;
    int height, board_size_px, square_size_px;

    // set color of renderer to some color
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );

    // clear the window
    SDL_RenderClear( _renderer );

    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[0]->w;
    tableSrc.h = _img[0]->h;
    tableDest.w = TABLE_SIZE;
    tableDest.h = TABLE_SIZE;

    // draws the table texture
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

    // render the IST Logo
    height = RenderLogo(TABLE_SIZE, 0, _img[1], _renderer);

    // render the student name
    height += RenderText(TABLE_SIZE+3*MARGIN, height, "Goncalo Mestre", _font, &black, _renderer);

    // this renders the student number
    RenderText(TABLE_SIZE+3*MARGIN, height, "IST187005", _font, &black, _renderer);

    // compute and adjust the size of the table and squares
    board_size_px = (int)(BOARD_SIZE_PER*TABLE_SIZE);
    square_size_px = (board_size_px - (_board_pos+1)*SQUARE_SEPARATOR) / _board_pos;
    board_size_px -= board_size_px % (_board_pos*(square_size_px+SQUARE_SEPARATOR));
    board_size_px += SQUARE_SEPARATOR;

    // renders the entire board background
    SDL_SetRenderDrawColor(_renderer, dark.r, dark.g, dark.b, dark.a );
    board.x = (TABLE_SIZE - board_size_px) >> 1;
    board.y = (TABLE_SIZE - board_size_px - 15);
    board.w = board_size_px;
    board.h = board_size_px;
    SDL_RenderFillRect(_renderer, &board);

    // renders the squares where the numbers will appear
    SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a );

    // iterate over all squares
    for ( int i = 0; i < _board_pos; i++ )
    {
        for ( int j = 0; j < _board_pos; j++ )
        {
            board_square.x = board.x + (i+1)*SQUARE_SEPARATOR + i*square_size_px;
            board_square.y = board.y + (j+1)*SQUARE_SEPARATOR + j*square_size_px;
            board_square.w = square_size_px;
            board_square.h = square_size_px;
            SDL_RenderFillRect(_renderer, &board_square);
        }
    }

    // destroy everything
    SDL_DestroyTexture(table_texture);
    // store some variables for later use
    *_board_size_px = board_size_px;
    *_square_size_px = square_size_px;
}

/**
 * RenderLogo function: Renders the IST logo on the app window
 * \param x X coordinate of the Logo
 * \param y Y coordinate of the Logo
 * \param _logoIST surface with the IST logo image to render
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderLogo(int x, int y, SDL_Surface *_logoIST, SDL_Renderer* _renderer)
{
    SDL_Texture *text_IST;
    SDL_Rect boardPos;

    // space occupied by the logo
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = _logoIST->w;
    boardPos.h = _logoIST->h;

    // render it
    text_IST = SDL_CreateTextureFromSurface(_renderer, _logoIST);
    SDL_RenderCopy(_renderer, text_IST, NULL, &boardPos);

    // destroy associated texture !
    SDL_DestroyTexture(text_IST);
    return _logoIST->h;
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}

/**
 * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with the table background and IST logo
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 */
void InitEverything(int width, int height, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window,
                    SDL_Renderer** _renderer, TTF_Font **_font2, TTF_Font **_font3)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    // load the table texture
    _img[0] = IMG_Load("table_texture.png");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // load IST logo
    _img[1] = SDL_LoadBMP("ist_logo.bmp");
    if (_img[1] == NULL)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // this opens (loads) a font file and sets a size
    *_font = TTF_OpenFont(".//Fontes//FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // inicialização da font usada para as estatísticas presentes na janela
    *_font2 = TTF_OpenFont(".//Fontes//Demonized.ttf", 24);
    if(!* _font2)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // inicialização da font usada para as estatísticas presentes na janela
    *_font3 = TTF_OpenFont(".//Fontes//Queen.ttf", 24);
    if(!* _font3)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    // Para alterar o título da janela basta mudar a linha a baixo
    window = SDL_CreateWindow( "1024", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}


// Função que imprime no ecrã uma caixa de pedido de dados
void RenderImagens( SDL_Renderer *_renderer, char string[STRING_SIZE], int x, int y)
{
    SDL_Texture *Text_Imagem;
    SDL_Surface *Img_Imagem;
    SDL_Rect boardPos;

    // Faz render da imagem de derrota
    Img_Imagem = SDL_LoadBMP(string);
    if(Img_Imagem == NULL)
    {
        printf("Não foi possível fazer load da imagem: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Quadrado onde é impressa a imagem
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = Img_Imagem -> w;
    boardPos.h = Img_Imagem -> h;

    // Cria uma textura e faz render da mesma no ecrã
    Text_Imagem = SDL_CreateTextureFromSurface(_renderer, Img_Imagem);
    SDL_RenderCopy(_renderer, Text_Imagem, NULL, &boardPos);

    // Destruição da texture e surface
    SDL_DestroyTexture(Text_Imagem);
    SDL_FreeSurface(Img_Imagem);
}

// Função que apaga o nome de jogador
void LimpaNome(char nome_jogador[MEDIUMSTR])
{
    int i=0;
    for(i=0; i < 8; i++)
    {
        nome_jogador[i] = 0;
    }
}

// Função para os menus de novo jogo
void DecideNovoJogo(int *dados, SDL_Renderer *_renderer, TTF_Font *_font, int *newgame, int *clicou, char nome_jogador[MEDIUMSTR], int *readname,
                    SDL_Surface ** vectornumeros, TTF_Font *_font2)
{
    int i = 0;
    int x = 0;
    int y = 0;
    int j = 0;
    SDL_Color black = {0, 0, 0};
    SDL_Color lightwhite = {240, 240, 240};
    SDL_Rect boardPos;
    SDL_Texture *number_text;


    switch (*dados)
    {
    case 4:
        RenderText(XMSG, YMSG, "Selecione o nivel para o", _font2, &black, _renderer);
        RenderText(XMSG2, YMSG2, "tamanho do tabuleiro(4-11)", _font2, &black, _renderer);
        RenderImagens(_renderer, "TamanhoTabuleiro.bmp", XMINTAMANHO, YMINTAMANHO);
        break;
    case 3:
        RenderImagens(_renderer, "Caixa.bmp", XCAIXA-5, YCAIXA-10);
        RenderText(XCAIXA+CENTRAR, YCAIXA, "Introduza o nome de utilizador", _font, &black, _renderer);
        if(*clicou == 0  &&  nome_jogador[0] == 0)
        {

            RenderText(XMINCAIXINHA, YCAIXINHA, "Username", _font, &lightwhite, _renderer);
        }
        else if(*clicou == 0)
        {
            RenderText(XMINCAIXINHA, YCAIXINHA, nome_jogador, _font, &black, _renderer);
        }
        else
        {
            if(nome_jogador[0] != 0)
            {
                RenderText(XMINCAIXINHA, YCAIXINHA, nome_jogador, _font, &black, _renderer);
            }
        }
        break;
    case 2:
        *clicou = 0;
        *readname = 0;
        RenderText(XMSG3, YMSG, "Selecione a dificuldade!", _font2, &black, _renderer);
        x = XMINNUMS;
        y = YMINNUMS;
        for(i=(NIVELMIN-1); i < MAX_LEVELS; i++)
        {
            if(j == 5)
            {
                x = XMINNUMS;
                y += TAMANHONUM;
                j = 0;
            }
            // define the size and copy the image to display
            boardPos.x = x;
            boardPos.y = y;
            boardPos.w = TAMANHONUM;
            boardPos.h = TAMANHONUM;
            number_text = SDL_CreateTextureFromSurface( _renderer, vectornumeros[i] );
            SDL_RenderCopy( _renderer, number_text, NULL, &boardPos );
            // destroy texture
            SDL_DestroyTexture(number_text);
            j++;
            x += TAMANHONUM;
        }
        break;
    case 1:
        *dados = *dados -1;
        *newgame = 1;
        break;
    default:
        break;
    }
}

// Função que verifica se alguma zona do ecrã foi clicada com o rato
int ClicouNaCaixa(SDL_Event event, int xmin, int xmax, int ymin, int ymax)
{
    int retorno=0;
    if(event.button.x > xmin  &&  event.button.x < xmax  &&  event.button.y > ymin  &&  event.button.y < ymax)
    {
        retorno = 1;
    }
    else
    {
        retorno = 0;
    }
    return retorno;
}

// Função que faz a leitura do nome de jogador
void LeNome(SDL_Event event, char nome_jogador[MEDIUMSTR], int *posicaonome)
{
    int a=0;
    a=*posicaonome;
    if(event.key.keysym.sym >= SDLK_a  &&  event.key.keysym.sym <= SDLK_z)
    {
        nome_jogador[*posicaonome] = event.key.keysym.sym - SDLK_a + 'a';
        *posicaonome = *posicaonome + 1;
    }
    else if(event.key.keysym.sym >= SDLK_0  &&  event.key.keysym.sym <= SDLK_9)
    {
        nome_jogador[*posicaonome] = event.key.keysym.sym - SDLK_0 + '0';
        *posicaonome = *posicaonome + 1;
    }
    switch(event.key.keysym.mod)
    {
    case KMOD_CAPS:
        if(nome_jogador[a] >= 'a' && nome_jogador[a] <= 'z')
        {
            nome_jogador[a] = nome_jogador[a] - 32;
        }
        break;
    case KMOD_LSHIFT:
        if(nome_jogador[a] >= 'a' && nome_jogador[a] <= 'z')
        {
            nome_jogador[a] = nome_jogador[a] - 32;
        }
        break;
    case KMOD_RSHIFT:
        if(nome_jogador[a] >= 'a' && nome_jogador[a] <= 'z')
        {
            nome_jogador[a] = nome_jogador[a] - 32;
        }
        break;
    default:
        break;
    }
}

// Função que apaga uma letra do nome de jogador
void ApagaLetra(SDL_Event event, char nome_jogador[MEDIUMSTR], int *posicaonome)
{
    if(event.key.keysym.sym == SDLK_BACKSPACE)
    {
        *posicaonome = *posicaonome - 1;
        nome_jogador[*posicaonome] = 0;
    }
}

// Função que faz a leitura do tamanho do tabuleiro através do clique do rato na imagem
void LeTamanho (SDL_Event event, int *dimensao)
{
    int x=0;
    int y=0;

    x = event.button.x;
    y = event.button.y;
    x = x - XMINTAMANHO;
    x = x/TAMANHOTAMANHO;
    y = y- YMINTAMANHO;
    y = y/TAMANHOTAMANHO;
    *dimensao = x+(y*4)+DIMMIN;
}

// Função que faz a leitura da dificuldade através do clique do rato na imagem
void LeDificuldade(SDL_Event event, int *dificuldade)
{
    int x = 0;
    int y = 0;

    x = event.button.x;
    x -= XMINNUMS;
    x = x/TAMANHONUM;
    y = event.button.y;
    y -= YMINNUMS;
    y = y/TAMANHONUM;
    *dificuldade = x+(y*5)+NIVELMIN;
}

// Função que implementa todas as situações de clique nos menus de novo jogo
void ClicksNovoJogo(SDL_Event event, int *dados, int *dimensao, int *board_pos, int *clicou, int *readname, int *posicaonome,
                    int *dificuldade, char nome_jogador[])
{

    if(*dados == 4  &&  ClicouNaCaixa(event, XMINTAMANHO, XMAXTAMANHO, YMINTAMANHO, YMAXTAMANHO) == 1)
    {
        LeTamanho(event, dimensao);
        *dados = *dados - 1;
    }
    else if(*dados == 3  &&  ClicouNaCaixa(event, XMINCAIXINHA, XMAXCAIXINHA, YCAIXINHA, YCAIXINHA+VARCAIXINHA) == 1)
    {
        LimpaNome(nome_jogador);
        *clicou = 1;
        *readname = 1;
        *posicaonome = 0;
    }
    else if(*dados == 3  &&  ClicouNaCaixa(event, OKXMIN, OKXMAX, OKYMIN, OKYMAX) == 1   &&  nome_jogador[0] != 0)
    {
        *dados = *dados - 1;
    }
    else if(*dados == 2  && ClicouNaCaixa(event, XMINNUMS, XMAXNUMS, YMINNUMS, YMAXNUMS) == 1)
    {
        LeDificuldade(event, dificuldade);
        *board_pos = *dimensao;
        *dados = *dados - 1;
    }
}
