# 2048
Implementation of 2048 game in C with plenty of extras

This game was made as my intermidiate project for my Programation discpline at my first year at high school
It allows the user to play the game and has a lot of extras I made for the delivery and some I made for fun after it, as allowing 25 undos, allowing to save, opening saved games, starting new games for a different player without running the program again.

The program can be compiled using gcc with the following command:
gcc 1024.c -g -I/usr/local/include -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o 1024

And runs using:
./2048

To play it was only needed to use the arrow keys, and the ones listed in the window.
