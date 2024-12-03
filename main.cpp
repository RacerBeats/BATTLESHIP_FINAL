#include <iostream>
#include <cstdlib>
#include <ctime>
#include "header.h"
using namespace std;

int main() {
    // Seed the random number generator
    srand(time(0));

    PlayerBoard player, computer;

    // Setup boards
    boardSetup(player, computer);

    // Game loop
    while (!isGameOver(player, computer)) {
        playerTurn(player, computer);
        if (isGameOver(player, computer)) break;
        computerTurn(computer, player);
    }

    cout << "Game Over!" << endl;
    return 0;
}