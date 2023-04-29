#pragma once
#include "game_class.hpp"

Tictactoe::Tictactoe(){
    // Instantiating the game;
    std::memset(board, ' ', sizeof(board));
    score_board();
}


void Tictactoe::put_pic(){
    srand(time(nullptr));
    Pic c;
    c.x = rand() % (WIDTH) + 1;
    c.y = rand() % (HEIGHT) + 1;
    c.shape = player2;

    while(!fill_n_check(c)){
        c.x = rand() % (WIDTH) + 1;
        c.y = rand() % (HEIGHT) + 1;
    }
}


void Tictactoe::draw_board(){
    std::cout << std::endl;
    for(int i = 0; i < HEIGHT; i++){
        std::cout << "\t\t\t\t\t\t\t  |   |  " << std::endl;
        std::cout << "\t\t\t\t\t\t\t" << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << std::endl;
        if(i != 2){
            std::cout << "\t\t\t\t\t\t\t~~~~~~~~~" << std::endl;
        }
    }
    std::cout << std::endl;
}


void Tictactoe::score_board(){
    scores[ai] = 10;
    scores[human] = -10;
    scores[tie] = 0;
}



bool Tictactoe::fill_n_check(Pic c){
    --c.x;
    --c.y;
    
    if(
        (c.x >= 0 && c.x <= 2) &&
        (c.y >= 0 && c.y <= 2)
    ){

        if(board[c.x][c.y] == ' '){
            board[c.x][c.y] = c.shape;
            return true;
        }
    }

    return false;
}


// check winner. Check if the counts are three for anyone
char Tictactoe::check_winner(int player2_count, int player1_count){
    if(player2_count == 3 || player1_count == 3){
        return player2_count == 3? ai: human;
    }
    return no_winner;
}

// find winner
std::pair<char, int> Tictactoe::find_winner(){

    int player2_count = 0, player1_count = 0, space_count = 0;
    char result;
    char flag = no_winner;
    // Look for winner horizontally
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == ai){
                player2_count++;
            }
            else if(board[i][j] == human){
                player1_count++;
            }
            else{
                space_count++;
            }
        }
        result = check_winner(player2_count, player1_count);
        if(result != no_winner){
            flag = result;
        }
        player2_count = 0, player1_count = 0;
    }

    if(flag != no_winner){
        return {result, space_count};
    }

    player2_count = 0, player1_count = 0;

    // Look for winner horizontally
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[j][i] == ai){
                player2_count++;
            }
            else if(board[j][i] == human){
                player1_count++;
            }
        }
        result = check_winner(player2_count, player1_count);
        if(result != no_winner)
            return {result, space_count};
        player2_count = 0, player1_count = 0;
    }


    
    // Look for winner diagonally
    // diagonal 1: top left to bottom right

    for(int i = 0; i < 3; i++){
        if(board[i][i] == ai){
            player2_count++;
        }
        else if(board[i][i] == human){
            player1_count++;
        }
    }

    result = check_winner(player2_count, player1_count);
    if(result != no_winner)
        return {result, space_count};

    // diagonal 2: top right to bottom left
    player2_count = 0, player1_count = 0;

    for(int i = 0; i < 3; i++){
        if(board[i][2 - i] == ai){
            player2_count++;
        }
        else if(board[i][2 - i] == human){
            player1_count++;
        }
    }

    result = check_winner(player2_count, player1_count);
    if(result != no_winner)
        return {result, space_count};

    if(space_count == 0)
        return {tie, space_count};
    return {result, space_count};
}



int Tictactoe::minimax(int alpha, int beta, bool is_maximizing){
    char result = find_winner().first;
    if(result != no_winner){
        return scores[result];
    }

    int best_score;
    int score;

    if(is_maximizing){
        best_score = -1000;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == ' '){
                    board[i][j] = ai;

                    score = minimax(alpha, beta, false);

                    board[i][j] = ' ';

                    best_score = std::max(score, best_score);
                    alpha = std::max(best_score, alpha);

                    if(alpha >= beta){
                        return best_score;
                    }
                }
            }
        }
        return best_score;
    }

    else{
        best_score = +1000;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == ' '){
                    board[i][j] = human;

                    score = minimax(alpha, beta, true);

                    board[i][j] = ' ';

                    best_score = std::min(score, best_score);
                    beta = std::min(best_score, beta);

                    if(alpha >= beta){
                        return best_score;
                    }
                }
            }
        }
        return best_score;
    }
}


void Tictactoe::next_best_move(){
    int best_score = -1000;
    int score;
    std::pair<int, int> move;
    int alpha = -1000;
    int beta = +1000;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == ' '){
                // store ai in this coordinate temorarily to look at all the possible
                // futures of the board, in order to choose the most
                // optimal one, assuming the human opponent is also 
                // playing optimally.
                // alpha: Maximizing
                // Beta: Minimizing

                board[i][j] = ai;

                score = minimax(alpha, beta, false);

                board[i][j] = ' ';

                if(score > best_score){
                    best_score = score;
                    move.first = i;
                    move.second = j;
                }
            }
        }
    }

    board[move.first][move.second] = ai; 
}


void Tictactoe::game_over(char winner){
    clearScreen();
    std::cout << "\t\t\t.__________________________________________________________________________________________." << std::endl;
    std::cout << "\t\t\t|                                                                                          |" << std::endl;
    std::cout << "\t\t\t|\tG\tA\tM\tE\t\tO\tV\tE\tR\t!\t   |" << std::endl;
    std::cout << "\t\t\t|__________________________________________________________________________________________|" << std::endl;

    std::cout << "\n\n";
    if(winner == tie)
        std::cout << "\t\t\t\t\t\t  The game was a DRAW!\n";
    
    else{
        if(winner == player1)
            std::cout << "\t\t\t\t\t\t  " << "PLAYER 1" << " Wins!"<< std::endl;
        else
            std::cout << "\t\t\t\t\t\t  " << "PLAYER 2" << " Wins!"<< std::endl;

    }
    
    std::cout << std::endl;
    draw_board();
    pause;
    exit(EXIT_SUCCESS);
}