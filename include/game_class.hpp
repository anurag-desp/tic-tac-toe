#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include "globals.hpp"

typedef struct Symbol{
    int x;
    int y;
    char shape;
} Pic;

class Tictactoe{
    private:
        char game_area[HEIGHT][WIDTH];
        char player1_pic;
        char player2_pic;
        bool game_over = false;

        void checkDiagonals(int* count_X, int* count_O, int indx, int indy);
        void checkWinner(int count_X, int count_O);
        void checkGame();
        void gameOver(char winner);

    public:
        Tictactoe();
        void drawArea();
        bool fillnCheck(Pic c);   // true if the Coordinates were put successfully, false otherwise
        bool setPics(char player1_pic, char player2_pic);
        void putPic();
};