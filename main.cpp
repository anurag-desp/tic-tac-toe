#include <iostream>
#include <cctype>
#include "./include/globals.hpp"
#include "./include/game_class.hpp"
#include "./include/game_definitions.hpp"

void printLogo(){
    std::cout << "\t\t._________________________________________________________________________________." << std::endl;
    std::cout << "\t\t|  \t \t \t\t \t \t \t\t \t \t  |" << std::endl;
    std::cout << "\t\t| T\tI\tC\t\tT\tA\tC\t\tT\tO\tE |" << std::endl;
    std::cout << "\t\t|_________________________________________________________________________________|" << std::endl;

}

int main(int argc, char** argv){
    clearScreen();
    printLogo();

    Tictactoe game;
    char choice;
    Symbol userPic1, userPic2;

    std::cout << "a. Single Player" << std::endl;
    std::cout << "b. Multi Player" << std::endl;
    choice = getchar();
    std::cout << "choice: " << choice << std::endl;

    if(choice == 'a'){
        std::cout << "S I N G L E  P L A Y E R" << std::endl;
        
        std::cout << "You are PLAYER 1" << std::endl;
        std::cout << "Enter the symbol you wish to play with: ";
        std::cin >> userPic1.shape;
        userPic1.shape = toupper(userPic1.shape);

        game.setPics(userPic1.shape);
    }

    else{
        std::cout << "M U L T I  P L A Y E R" << std::endl;

        std::cout << "PLAYER 1" << std::endl;
        std::cout << "Enter the symbol you wish to play with: ";
        std::cin >> userPic1.shape;
        userPic1.shape = toupper(userPic1.shape);

        do{
        std::cout << "PLAYER 2" << std::endl;
        std::cout << "Make sure your symbol doesn't match with player 1" << std::endl;
        std::cout << "Enter the symbol you wish to play with: ";
        std::cin >> userPic2.shape;
        userPic2.shape = toupper(userPic2.shape);
        }while(userPic1.shape == userPic2.shape);
    }

    
    return 0;
}