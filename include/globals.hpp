#pragma once
#include <map>

#define clearScreen() printf("\033[H\033[J")
#define pause getchar();getchar()
#define HEIGHT 3
#define WIDTH 3
#define ai 'O'
#define human 'X'
#define player1 'X'
#define player2 'O'
#define no_winner 'N'
#define tie 'T'

std::map<char, int> scores;
