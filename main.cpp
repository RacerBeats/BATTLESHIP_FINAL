#include <iostream>
#include "header.h"

int main() {
    PlayerBoard player1;
    PlayerBoard player2;

    // Initialize boards and fleets
    initFleet(player1);
    initFleet(player2);

    // Setup boards
    boardSetup(player1, player2);

    // Game loop would go here

    return 0;
}