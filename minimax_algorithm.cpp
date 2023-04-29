#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <cmath>
#include <map>

#define clearScreen() printf("\033[H\033[J")
#define pause getchar();getchar()
#define ai 'X'
#define human 'O'
#define no_winner 'N'
#define tie 'T'

std::map<char, int> scores;

void score_board(){
    scores[ai] = 10;
    scores[human] = -10;
    scores[tie] = 0;
}

void print_board(std::string str, char board[3][3]){
    std::cout << str << std::endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << board[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}

// check winner. Check if the counts are three for anyone
char check_winner(int ai_count, int human_count){
    if(ai_count == 3 || human_count == 3){
        return ai_count == 3? ai: human;
    }
    return no_winner;
}

// find winner
std::pair<char, int> find_winner(char board[3][3]){

    int ai_count = 0, human_count = 0, space_count = 0;
    char result;
    char flag = no_winner;
    // Look for winner horizontally
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == ai){
                ai_count++;
            }
            else if(board[i][j] == human){
                human_count++;
            }
            else{
                space_count++;
            }
        }
        result = check_winner(ai_count, human_count);
        if(result != no_winner){
            flag = result;
        }
        ai_count = 0, human_count = 0;
    }

    if(flag != no_winner){
        return {result, space_count};
    }

    ai_count = 0, human_count = 0;

    // Look for winner horizontally
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[j][i] == ai){
                ai_count++;
            }
            else if(board[j][i] == human){
                human_count++;
            }
        }
        result = check_winner(ai_count, human_count);
        if(result != no_winner) return {result, space_count};
        ai_count = 0, human_count = 0;
    }


    
    // Look for winner diagonally
    // diagonal 1: top left to bottom right

    for(int i = 0; i < 3; i++){
        if(board[i][i] == ai){
            ai_count++;
        }
        else if(board[i][i] == human){
            human_count++;
        }
    }

    result = check_winner(ai_count, human_count);
    if(result != no_winner) return {result, space_count};

    // diagonal 2: top right to bottom left
    ai_count = 0, human_count = 0;

    for(int i = 0; i < 3; i++){
        if(board[i][2 - i] == ai){
            ai_count++;
        }
        else if(board[i][2 - i] == human){
            human_count++;
        }
    }

    result = check_winner(ai_count, human_count);
    if(result != no_winner) return {result, space_count};

    if(space_count == 0) return {tie, space_count};
    return {result, space_count};
}



int minimax(char board[3][3], int alpha, int beta, bool is_maximizing){
    char result = find_winner(board).first;
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

                    // print_board("maximizing", board);
                    score = minimax(board, alpha, beta, false);

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

                    // print_board("minimizing", board);
                    score = minimax(board, alpha, beta, true);

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


std::pair<int, int> next_best_move(char board[3][3], int depth){
    int best_score = -1000;
    int score;
    std::pair<int, int> move;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == ' '){
                // store ai in this coordinate temorarily to look at all the possible
                // futures of the board, in order to choose the most
                // optimal one, assuming the human opponent is also 
                // playing optimally.

                board[i][j] = ai;

                // print_board("next_best_move", board);
                score = minimax(board, -1000, +1000, false);

                board[i][j] = ' ';

                if(score > best_score){
                    best_score = score;
                    move.first = i;
                    move.second = j;
                }
            }
        }
    }

    return move; 
}



int main(int argc, char** argv){
    score_board();
    char board[3][3] = {
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' }
    };
    
    std::pair<char, int>move;
    move.first =no_winner;
    move.second = 9;

    std::pair<int, int> best_move;
    int i, j;

    while(move.second != 0){

        if(find_winner(board).first != no_winner){
            exit(0);
        }
        std::cin >> i >> j;
        board[i][j] = human;

        best_move = next_best_move(board, move.second);
        board[best_move.first][best_move.second] = ai;
        print_board("Current Config", board);


    }

    // std::cout << move.first << " " << move.second << std::endl;
    return 0;
}