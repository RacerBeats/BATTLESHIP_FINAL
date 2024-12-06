#include <iostream>
#include <cstdlib>
#include <ctime>
#include "header.h"
using namespace std;

int main() {
    // Seed the random number generator
    srand(time(0));

    PlayerBoard player, player2, computer;

    cout << "Welcome to Battleship!" << endl;
    cout << "Select mode: 1 - Single Player, 2 - Two Player" << endl;
    int mode;
    cin >> mode;
    if (mode == 1) {
        cout << "Single Player Mode" << endl;
         // Setup boards
        boardSetupPVE(player, computer);

        // Game loop
        while (!isGameOver(player, computer)) {
            playerTurn(player, computer);
            if (isGameOver(player, computer)) break;
            computerTurn(computer, player);
        }
        
    } else if (mode == 2) {
        cout << "Two Player Mode" << endl;
         // Setup boards
        boardSetup(player, player2);

        // Game loop
        while (!isGameOver(player, player2)) {
            playerTurn(player, player2);
            if (isGameOver(player, player2)) break;
            playerTurn(player2, player);
        }
        
    } else {
        cout << "Invalid mode selected." << endl;
        return 1;
    }

    cout << "Game Over!" << endl;
    return 0;
}