#include "header.h"
#include <iostream>
#include <iomanip>
using namespace std;

void displayBoards(char board1[][BOARD_SIZE], char board2[][BOARD_SIZE]) {
    // Print column headers
    cout << " ";
    for (int col = 1; col <= BOARD_SIZE; col++) {
        cout << setw(4) << col; // Set width for even spacing
    }
    cout << "             "; // Space between the two boards
    for (int col = 1; col <= BOARD_SIZE; col++) {
        cout << setw(4) << col; // Set width for even spacing
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
            if (board1[row - 'A'][col] == ' ') {
                cout << "   |"; // Print empty space
            } else {
                cout << " " << board1[row - 'A'][col] << " |"; // Print board1
            }
        }
        cout << "          " << row << " |"; // Row header for board2
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Check if the cell is empty and print accordingly
            if (board2[row - 'A'][col] == ' ') {
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
    // Initialize the fleets for both players
    initFleet(player1);
    initFleet(player2);

    // Place ships for player 1
    cout << "Player 1, set your board." << endl;
    for (int i = 0; i < FLEET_SIZE; i++) {
        displayBoards(player1.board, player2.board); // Display boards before placing the ship
        placeShip(player1, i); // Place each ship in the player's fleet
    }

    // Place ships for player 2
    cout << "Player 2, set your board." << endl;
    for (int i = 0; i < FLEET_SIZE; i++) {
        displayBoards(player1.board, player2.board); // Display boards before placing the ship
        placeShip(player2, i); // Place each ship in the player's fleet
    }

    // Final display of both boards after setup
    displayBoards(player1.board, player2.board);
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

    //TODO: Validate input and handle errors

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
    Ship &ship = playerBoard.fleet[shipIndex];
    bool validInput = false;

    while (!validInput) {
        char letter;
        int number;

        //TODO: Add error handling for invalid input
        cout << "Enter the starting coordinates of your " << ship.name << " (e.g., A 1): ";
        cin >> letter >> number;

        // Convert letter to row index and number to column index
        row = toupper(letter) - 'A'; // Convert letter to row index
        col = number - 1; // Convert number to column index (0-based)

        // Check if the input is valid
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            cout << "Enter the orientation of your " << ship.name << " (horizontal(h) or vertical(v)): ";
            cin >> orientation;
            cout << endl;

            // Validate orientation
            if (orientation == 'h' || orientation == 'v') {
                // Check if the ship can be placed in the specified location
                if (spaceOccupied(playerBoard, row, col, orientation, ship.size)) {
                    cout << "Error: Space already occupied. Please try again." << endl;
                } else {
                    validInput = true; // Valid input received
                }
            } else {
                cout << "Error: Invalid orientation. Please enter 'h' or 'v'." << endl;
            }
        } else {
            cout << "Error: Invalid coordinates. Please enter values within the board range." << endl;
        }
    }
}

bool spaceOccupied(const PlayerBoard &playerBoard, int row, int col, char orientation, int shipSize) {
    if (orientation == 'h') {
        // Check horizontal placement
        for (int i = 0; i < shipSize; i++) {
            if (col + i >= BOARD_SIZE || playerBoard.board[row][col + i] != ' ') {
                return true; // Space is occupied or out of bounds
            }
        }
    } else if (orientation == 'v') {
        // Check vertical placement
        for (int i = 0; i < shipSize; i++) {
            if (row + i >= BOARD_SIZE || playerBoard.board[row + i][col] != ' ') {
                return true; // Space is occupied or out of bounds
            }
        }
    }
    return false;
}

void playerTurn(PlayerBoard &player, PlayerBoard &computer) {
    int row, col;
    char letter;
    cout << "Player's turn. Enter your shot (e.g., A 1): ";
    cin >> letter >> col;
    row = toupper(letter) - 'A'; // Convert letter to row index
    col -= 1; // Convert number to column index (0-based)

    // Check if the shot is valid
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
        if (computer.board[row][col] != ' ') {
            cout << "Hit!" << endl;
            computer.board[row][col] = 'H'; // Mark hit on the computer's board
            // check what ship was hit, and increment hit count for that ship
            computer.fleet->hitCount++;
        } else {
            cout << "Miss!" << endl;
            computer.board[row][col] = 'M'; // Mark miss on the computer's board
        }
    } else {
        cout << "Invalid shot. Please try again." << endl;
    }

    displayBoards(player.board, computer.board); // Show boards after the turn
}

//computer shoots randomly
void computerTurn(PlayerBoard &computer, PlayerBoard &player) {
    int row, col;
    bool validShot = false;

    // TODO: computer must run out of valid shots. infinite loop is making computer shoot forever
    while (!validShot) {
        row = rand() % BOARD_SIZE; // Random row
        col = rand() % BOARD_SIZE; // Random column

        // Check if the shot is valid (not already hit or missed)
        if (player.board[row][col] != 'H' && player.board[row][col] != 'M') {
            validShot = true; // Valid shot found
            if (player.board[row][col] != ' ') {
                cout << "Computer hit at " << static_cast<char>('A' + row) << " " << (col + 1) << "!" << endl;
                player.board[row][col] = 'H'; // Mark hit on the player's board
                /// check what ship was hit, and increment hit count for that ship
                player.fleet->hitCount++;
            } else {
                cout << "Computer missed at " << static_cast<char>('A' + row) << " " << (col + 1) << "!" << endl;
                player.board[row][col] = 'M'; // Mark miss on the player's board
            }
        }
    }

    displayBoards(player.board, computer.board); // Show boards after the turn
}

bool isGameOver(const PlayerBoard &player, const PlayerBoard &computer) {
    // Check if all ships are sunk for the computer
    bool computerShipsSunk = areAllShipsSunk(computer);

    // Check if all ships are sunk for the player
    bool playerShipsSunk = areAllShipsSunk(player);

    // Determine the game state
    if (computerShipsSunk) {
        cout << "Player wins!" << endl;
        return true; // All computer ships are sunk
    } else if (playerShipsSunk) {
        cout << "Computer wins!" << endl;
        return true; // All player ships are sunk
    }

    return false; // Game continues
}

bool areAllShipsSunk(const PlayerBoard &player) {
    // Assume all ships are sunk initially
    bool allSunk = true;

    // Loop through each ship in the player's fleet
    for (int i = 0; i < FLEET_SIZE; i++) {
        Ship currentShip = player.fleet[i]; // Get the current ship

        // Check if the ship is still afloat
        if (currentShip.hitCount < currentShip.size) {
            allSunk = false; // At least one ship is still afloat
            break; // No need to check further, we found a ship that is not sunk
        }
    }

    return allSunk; // Return whether all ships are sunk
}