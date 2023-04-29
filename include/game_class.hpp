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
        char board[HEIGHT][WIDTH];
        bool is_game_over = false;

        void score_board();
        char check_winner(int player1_count, int player2_count);

        int minimax(int alpha, int beta, bool is_maximizing);


    public:
        Tictactoe();
        void draw_board();
        bool fill_n_check(Pic c);   // true if the Coordinates were put successfully, false otherwise
        std::pair<char, int> find_winner();
        void put_pic();
        void next_best_move();
        void game_over(char winner);
};