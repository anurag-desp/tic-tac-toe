#include <iostream>
#include <cctype>
#include <chrono>
#include <thread>
#include "./include/globals.hpp"
#include "./include/game_class.hpp"
#include "./include/game_definitions.hpp"

#define print_board(this_game) clearScreen();printLogo();this_game.draw_board()
#define check_result() result = game.find_winner().first;if(result != no_winner){game.game_over(result);}
// #define print

void printLogo(){
    std::cout << "\t\t._________________________________________________________________________________." << std::endl;
    std::cout << "\t\t|  \t \t \t\t \t \t \t\t \t \t  |" << std::endl;
    std::cout << "\t\t| T\tI\tC\t\tT\tA\tC\t\tT\tO\tE |" << std::endl;
    std::cout << "\t\t|_________________________________________________________________________________|" << std::endl;
}



int main(int argc, char **argv){
    clearScreen();
    printLogo();

    Tictactoe game;
    Pic player1_pic, player2_pic;
    player1_pic.shape = 'X';
    player2_pic.shape = 'O';

    char choice;
    char result;
    int repetition = 0;

    std::cout << "a. Single Player" << std::endl;
    std::cout << "b. Multi Player" << std::endl;
    std::cout << " Choice: ";
    choice = getchar();
    choice = toupper(choice);

    clearScreen();
    printLogo();

    if(choice == 'A'){
        std::cout << "S I N G L E  P L A Y E R\n" << std::endl;
        std::cout << "e. Easy :)" << std::endl;
        std::cout << "i. Impossible ;]" << std::endl;
        
        std::cout << "\n Choice(e, i): ";
        std::cin >> choice;
        choice = toupper(choice);
    }


    repetition = 0;
    print_board(game);
    while(true){
        std::cout << "\n\n\t\t\t\t PLAYER 1  (X)" << std::endl;
        std::cout << "\n\t\t Enter the coordinates: ";
        std::cin >> player1_pic.x >> player1_pic.y;

        if(!game.fill_n_check(player1_pic)){
            std::cout << "\t\t\t\t\t Coordinates already FILLED or INVALID!" << std::endl;
            pause;

            print_board(game);
            continue;
        }
        check_result();

        print_board(game);

        if(
            choice == 'E' ||
            choice == 'I'
        ){
            if(choice == 'E'){
                game.put_pic();
            }
            else{
                game.next_best_move();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            check_result();
        }

        else{
            do{
                if(repetition != 0){
                    std::cout << "\t\t\t\t\t Coordinates already FILLED or INVALID!" << std::endl;
                    pause;
                    print_board(game);
                }
                std::cout << "\n\n\t\t\t\t PLAYER 2 (O)" << std::endl;
                std::cout << "\n\t\t Enter the coordinates: ";
                std::cin >> player2_pic.x >> player2_pic.y;

                repetition = 1;
            }while(!game.fill_n_check(player2_pic));
            check_result();

        }

        print_board(game); // Prints both the latest moves of the player 1 and player 2 
        repetition = 0;
    }

    return 0;
}