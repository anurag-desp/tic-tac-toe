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
    Symbol userPic;
    std::cout << "Enter the symbol you wish to play with: (X  or  O): ";
    std::cin >> userPic.shape;
    userPic.shape = toupper(userPic.shape);
    game.setPics(userPic.shape);

    while(true){
        clearScreen();
        printLogo();
        game.drawArea();

        std::cout << "\nEnter the coordinates: ";
        std::cin >> userPic.x >> userPic.y;

        if(!game.fillnCheck(userPic)){
            std::cout << "Coordinates already FILLED!" << std::endl;
            pause;
            continue;
        }
        
        game.putSymbol();
    }
    return 0;
}