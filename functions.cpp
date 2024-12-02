#include "header.h"
#include <iostream>
#include <iomanip>
using namespace std;

void displayBoards(char board1[][BOARD_SIZE], char board2[][BOARD_SIZE]) {
    // Print column headers
    cout << "    ";
    for (int col = 1; col <= BOARD_SIZE; col++) {
        cout << setw(3) << col; // Set width for even spacing
    }
    cout << "                "; // Space between the two boards
    for (int col = 1; col <= BOARD_SIZE; col++) {
        cout << setw(3) << col; // Set width for even spacing
    }
    cout << endl;

    cout << "  ";
    for (int col = 0; col < BOARD_SIZE; col++) {
        cout << "----"; // Column separator
    }
    cout << "              "; // Space between the two boards
    for (int col = 0; col < BOARD_SIZE; col++) {
        cout << "----"; // Column separator
    }
    cout << endl;

    // Print each row of the boards
    for (char row = 'A'; row < 'A' + BOARD_SIZE; row++) {
        cout << row << " |"; // Row header
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Check if the cell is empty and print accordingly
            if (board1[row - 'A'][col] == '\0') {
                cout << "   |"; // Print empty space
            } else {
                cout << " " << board1[row - 'A'][col] << " |"; // Print board1
            }
        }
        cout << "          " << row << " |"; // Row header for board2
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Check if the cell is empty and print accordingly
            if (board2[row - 'A'][col] == '\0') {
                cout << "   |"; // Print empty space
            } else {
                cout << " " << board2[row - 'A'][col] << " |"; // Print board2
            }
        }
        cout << endl;

        cout << "  ";
        for (int col = 0; col < BOARD_SIZE; col++) {
            cout << "----"; // Row separator
        }
        cout << "              "; // Space between the two boards
        for (int col = 0; col < BOARD_SIZE; col++) {
            cout << "----"; // Row separator
        }
        cout << endl;
    }
}

void initFleet(PlayerBoard &playerBoard) {
    // Initialize the board to empty spaces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            playerBoard.board[i][j] = ' '; // Use space for empty cells
        }
    }

    // Initialize the ships in the fleet
    playerBoard.fleet[0] = {"Carrier", 5, 0, {}};
    playerBoard.fleet[1] = {"Battleship", 4, 0, {}};
    playerBoard.fleet[2] = {"Cruiser", 3, 0, {}};
    playerBoard.fleet[3] = {"Submarine", 3, 0, {}};
    playerBoard.fleet[4] = {"Destroyer", 2, 0, {}};
}

void boardSetup(PlayerBoard &player1, PlayerBoard &player2) {
    // Implementation will go here
}

void placeShip(PlayerBoard &playerBoard, int shipIndex) {
    Ship &ship = playerBoard.fleet[shipIndex];

    // Example coordinates and orientation (assumed valid)
    int row; // Row index (0-9)
    int col; // Column index (0-9)
    char orientation; // 'h' for horizontal, 'v' for vertical

    // For demonstration, let's assume these values are provided
    cout << "Enter the starting coordinates of your " << ship.name << ": ";
    cin >> row >> col; // Assuming input is in the format A1, B2, etc.
    cout << "Enter the orientation of your " << ship.name << " (horizontal(h) or vertical(v)): ";
    cin >> orientation;

    // Place the ship on the board
    if (orientation == 'h') {
        for (int i = 0; i < ship.size; i++) {
            playerBoard.board[row][col + i] = ship.name[0]; // Place the ship using the first letter of its name
            ship.positions.push_back({row, col + i}); // Store the position
        }
    } else if (orientation == 'v') {
        for (int i = 0; i < ship.size; i++) {
            playerBoard.board[row + i][col] = ship.name[0]; // Place the ship using the first letter of its name
            ship.positions.push_back({row + i, col}); // Store the position
        }
    }
}

void getValidShipInfo(int &row, int &col, char &orientation, PlayerBoard &playerBoard, int shipIndex) {
    // Implementation will go here
}

bool spaceOccupied(const PlayerBoard &playerBoard, int row, int col, char orientation, int shipSize) {
    // Implementation will go here
    return false;
}