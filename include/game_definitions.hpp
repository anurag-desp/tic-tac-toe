#pragma once
#include "game_class.hpp"

Tictactoe::Tictactoe(){
    // Instantiating the game with each cell filled with ' '
    std::memset(game_area, ' ', sizeof(game_area));
}

void Tictactoe::checkDiagonals(int* count_player1_pic, int* count_player2_pic, int indx, int indy){
    if(game_area[indx][indy] == player1_pic){
        ++(*count_player1_pic);
    }
    else if(game_area[indx][indy] == player2_pic){
        ++(*count_player2_pic);
    }
}

void Tictactoe::checkWinner(int count_player1_pic, int count_player2_pic){
    if(count_player1_pic == 3 || count_player2_pic == 3){
        game_over = true;
        char winner = count_player1_pic = 3? player1_pic: player2_pic;
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
    int count_player1_pic = 0, count_player2_pic = 0, count_spaces = 0;

    // checking horizontailly
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(game_area[i][j] == player1_pic)
                count_player1_pic++;
            else if(game_area[i][j] == player2_pic)
                count_player2_pic++;
            else{
                count_spaces++;
            }
        }
        checkWinner(count_player1_pic, count_player2_pic);
        count_player1_pic = 0;
        count_player2_pic = 0;
    }

    // Checking Vertically
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(game_area[j][i] == player1_pic)
                count_player1_pic++;
            else if(game_area[j][i] == player2_pic)
                count_player2_pic++;
        }
        checkWinner(count_player1_pic, count_player2_pic);
        count_player1_pic = 0;
        count_player2_pic = 0;
    }


    // Check Diagonally
    // Diagonal 1
    for(int i = 0; i < HEIGHT; i++)
        checkDiagonals(&count_player1_pic, &count_player2_pic, i, i);
    
    checkWinner(count_player1_pic, count_player2_pic);
    count_player1_pic = 0;
    count_player2_pic = 0;

    // Diagonal 2
    for(int i = 0; i < HEIGHT; i++)
        checkDiagonals(&count_player1_pic, &count_player2_pic, i, 2-i);

    checkWinner(count_player1_pic, count_player2_pic);
    count_player1_pic = 0;
    count_player2_pic = 0; 

    if(count_spaces == 0)
        gameOver('d');
    
}

bool Tictactoe::setPics(char pic1, char pic2){
    if(pic2 == ' '){
        if(pic1 == 'O')
            player2_pic = 'X';
        else
            player2_pic = 'O';
        player1_pic = pic1;
    }
    else{
        player1_pic = pic1;
        player2_pic = pic2;

        if(player1_pic == player2_pic)
            return false;
    }
    return true;
}

void Tictactoe::putPic(){
    srand(time(nullptr));
    Pic c;
    c.x = rand() % (WIDTH) + 1;
    c.y = rand() % (HEIGHT) + 1;
    c.shape = player2_pic;

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
        std::cout << "\t\t\t\t The WINNER IS: " << winner << std::endl;
    pause;
    exit(0);
}