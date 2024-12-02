#include <iostream>
#include "header.h"
using namespace std;

int main() {
    PlayerBoard player1;
    PlayerBoard player2;

    // Initialize boards and fleets
    initFleet(player1);
    initFleet(player2);

    // Setup boards
    boardSetup(player1, player2);

    // Game loop would go here
    displayBoards(player1.board, player2.board);
    initFleet(player1);
    initFleet(player2);
    placeShip(player1, 0);
    placeShip(player2, 0);

    return 0;
}