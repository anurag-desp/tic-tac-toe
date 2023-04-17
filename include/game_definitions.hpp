#pragma once
#include "game_class.hpp"

Tictactoe::Tictactoe(){
    // Instantiating the game;
    std::memset(game_area, ' ', sizeof(game_area));
}

void Tictactoe::checkDiagonals(int* count_user_pic, int* count_computer_pic, int indx, int indy){
    if(game_area[indx][indy] == user_pic){
        ++(*count_user_pic);
    }
    else if(game_area[indx][indy] == computer_pic){
        ++(*count_computer_pic);
    }
}

void Tictactoe::checkWinner(int count_user_pic, int count_computer_pic){
    if(count_user_pic == 3 || count_computer_pic == 3){
        game_over = true;
        char winner = count_user_pic = 3? user_pic: computer_pic;
        gameOver(winner);
    }
}

void Tictactoe::drawArea(){
    for(int i = 0; i < HEIGHT; i++){
        std::cout << "  |   |  " << std::endl;
        std::cout << game_area[i][0] << " | " << game_area[i][1] << " | " << game_area[i][2] << std::endl;
        if(i != 2){
            std::cout << "---------" << std::endl;
        }
    }
    std::cout << std::endl;
}

void Tictactoe::checkGame(){
    int count_user_pic = 0, count_computer_pic = 0, count_spaces = 0;

    // checking horizontailly
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(game_area[i][j] == user_pic)
                count_user_pic++;
            else if(game_area[i][j] == computer_pic)
                count_computer_pic++;
            else{
                count_spaces++;
            }
        }
        checkWinner(count_user_pic, count_computer_pic);
        count_user_pic = 0;
        count_computer_pic = 0;
    }

    // Checking Vertically
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(game_area[j][i] == user_pic)
                count_user_pic++;
            else if(game_area[j][i] == computer_pic)
                count_computer_pic++;
        }
        checkWinner(count_user_pic, count_computer_pic);
        count_user_pic = 0;
        count_computer_pic = 0;
    }


    // Check Diagonally
    // Diagonal 1
    for(int i = 0; i < HEIGHT; i++)
        checkDiagonals(&count_user_pic, &count_computer_pic, i, i);
    
    checkWinner(count_user_pic, count_computer_pic);
    count_user_pic = 0;
    count_computer_pic = 0;

    // Diagonal 2
    for(int i = 0; i < HEIGHT; i++)
        checkDiagonals(&count_user_pic, &count_computer_pic, i, 2-i);

    checkWinner(count_user_pic, count_computer_pic);
    count_user_pic = 0;
    count_computer_pic = 0; 

    if(count_spaces == 0)
        gameOver('d');
    
}

void Tictactoe::setPics(char symbol){
    if(symbol == 'O')
        computer_pic = 'X';
    else
        computer_pic = 'O';
    user_pic = symbol;
}

void Tictactoe::putSymbol(){
    srand(time(nullptr));
    Symbol c;
    c.x = rand() % (WIDTH) + 1;
    c.y = rand() % (HEIGHT) + 1;
    c.shape = computer_pic;

    while(!fillnCheck(c)){
        c.x = rand() % (WIDTH) + 1;
        c.y = rand() % (HEIGHT) + 1;
    }
}

bool Tictactoe::fillnCheck(Pic c){
    // To use them as indices of array
    --c.x;
    --c.y;

    // Fill the space
    if((c.x >= 0 && c.x <= 2) &&
       (c.y >= 0 && c.y <= 2)
    ){
        if(game_area[c.x][c.y] == ' '){
            game_area[c.x][c.y] = c.shape;
            checkGame();
            return true;
        }
    }
    return false;
}

void Tictactoe::gameOver(char winner){
    clearScreen();
    std::cout << "\t\t\t.__________________________________________________________________________________________." << std::endl;
    std::cout << "\t\t\t|                                                                                          |" << std::endl;
    std::cout << "\t\t\t|\tG\tA\tM\tE\t\tO\tV\tE\tR\t!\t   |" << std::endl;
    std::cout << "\t\t\t|__________________________________________________________________________________________|" << std::endl;

    std::cout << "\n\n";
    if(winner == 'd')
        std::cout << "\t\t\t\t The game was a DRAW!\n";
    
    else
        std::cout << "\t\t\t\t The WINNER IS: " << winner;
    pause;
    exit(0);
}