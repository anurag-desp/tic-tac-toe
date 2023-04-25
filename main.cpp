#include <iostream>
#include <cctype>
#include <chrono>
#include <thread>
#include "./include/globals.hpp"
#include "./include/game_class.hpp"
#include "./include/game_definitions.hpp"

#define print_area(this_game) clearScreen();printLogo();this_game.drawArea()
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
    char choice;
    int repetition = 0;

    std::cout << "a. Single Player" << std::endl;
    std::cout << "b. Multi Player" << std::endl;
    choice = getchar();
    std::cout << "choice: " << choice << std::endl;
    choice = toupper(choice);

    clearScreen();
    printLogo();
    if (choice == 'A'){
        std::cout << "\t\t\t\t\t S I N G L E  P L A Y E R" << std::endl;

        std::cout << "\t\t\t You are PLAYER 1" << std::endl;
        std::cout << "\t\t\t Enter the symbol you wish to play with: ";
        std::cin >> player1_pic.shape;
        player1_pic.shape = toupper(player1_pic.shape);

        game.setPics(player1_pic.shape, ' '); // ' ' -> single player indication
    }

    else
    {
        std::cout << "\t\t\t\t\t M U L T I  P L A Y E R" << std::endl;

        std::cout << "Go with default settings? (Y/N): ";
        std::cin >> choice;
        choice = toupper(choice);

        if (choice == 'Y')
        {
            game.setPics('X', 'O');
            player1_pic.shape = 'X';
            player2_pic.shape = 'O';
        }

        else
        {
            std::cout << "\t\t\t PLAYER 1" << std::endl;
            std::cout << "\t\t Enter the symbol you wish to play with: ";
            std::cin >> player1_pic.shape;
            player1_pic.shape = toupper(player1_pic.shape);

            do
            {
                std::cout << "\t\t\t PLAYER 2" << std::endl;

                if (repetition > 0)
                {
                    std::cout << "\n\t\t NOT ALLOWED!\n\t\t Same as Player 1\n";

                    clearScreen();
                    printLogo();
                    std::cout << "\n\n\t\t\t\t\t M U L T I  P L A Y E R" << std::endl;
                    std::cout << "\n\t\t\t PLAYER 1: " << player1_pic.shape << std::endl << std::endl; 
                    std::cout << "\t\t\t PLAYER 2" << std::endl;
                }
                repetition = 1;

                std::cout << "\t\t Enter the symbol you wish to play with: ";
                std::cin >> player2_pic.shape;
                player2_pic.shape = toupper(player2_pic.shape);

            } while (!game.setPics(player1_pic.shape, player2_pic.shape));
        }
    }


    repetition = 0;
    print_area(game);
    while(true){
        std::cout << "\n\n\t\t\t\t PLAYER 1" << std::endl;
        std::cout << "\n\t\t Enter the coordinates: ";
        std::cin >> player1_pic.x >> player1_pic.y;

        if(!game.fillnCheck(player1_pic)){
            std::cout << "\t\t\t\t\t Coordinates already FILLED or INVALID!" << std::endl;
            pause;

            print_area(game);
            continue;
        }

        print_area(game);

        if(choice == 'A'){
            game.putPic();
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        else{
            do{
                if(repetition > 0){
                    std::cout << "\t\t\t\t\t Coordinates already FILLED or INVALID!" << std::endl;
                    pause;
                    print_area(game);
                }
                std::cout << "\n\n\t\t\t\t PLAYER 2" << std::endl;
                std::cout << "\n\t\t Enter the coordinates: ";
                std::cin >> player2_pic.x >> player2_pic.y;

                repetition++;
            }while(!game.fillnCheck(player2_pic));
        }
        print_area(game); // Prints both the latest moves of the player 1 and player 2 
        repetition = 0;
    }

    return 0;
}