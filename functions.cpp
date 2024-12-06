#include "header.h"
#include <iostream>
#include <iomanip>
using namespace std;

//TODO: INTRODUCE INPUT.TXT FOR DIFFERENT TESTS IN A QUICK WAY
//TODO: SWAP PLAYER 1 AND PLAYER 2 BOARD TO HIDE AND SHOW.
/**
 * Displays the game boards for both players in a Battleship game.
 * The function prints the column headers, row headers, and the contents of each cell
 * for both player boards, with a space between the two boards.
 *
 * @param board1 The game board for the first player.
 * @param board2 The game board for the second player.
 */
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
            // Show everything on player's board (board1)
            if (board1[row - 'A'][col] == ' ') {
                cout << "   |"; // Print empty space
            } else {
                cout << " " << board1[row - 'A'][col] << " |"; // Print board1
            }
        }
        cout << "          " << row << " |"; // Row header for board2
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Only show hits and misses on opponent's board (board2)
            if (board2[row - 'A'][col] == 'H' || board2[row - 'A'][col] == 'M') {
                cout << " " << board2[row - 'A'][col] << " |";
            } else {
                cout << "   |"; // Hide ships, show empty space
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
/**
 * Initializes the player's fleet of ships on the game board.
 *
 * This function sets up the player's game board by:
 * 1. Initializing the board to empty spaces.
 * 2. Defining the ships in the player's fleet with their names, sizes, and position vectors.
 *
 * @param playerBoard Reference to the player's game board.
 */
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

/**
 * Sets up the game boards for both players by initializing their fleets and placing their ships.
 *
 * This function performs the following steps:
 * 1. Initializes the fleets for both player1 and player2 using the `initFleet` function.
 * 2. Prompts player1 to set their board by placing their ships using the `placeShip` function.
 * 3. Prompts player2 to set their board by placing their ships using the `placeShip` function.
 * 4. Displays the final boards for both players after the setup is complete.
 *
 * @param player1 Reference to the first player's game board.
 * @param player2 Reference to the second player's game board.
 */
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

/**
 * Sets up the game boards for a player vs. computer game by initializing the player's and computer's fleets and placing their ships.
 *
 * This function performs the following steps:
 * 1. Initializes the fleets for both the player and the computer using the `initFleet` function.
 * 2. Prompts the player to set their board by placing their ships using the `placeShip` function.
 * 3. Randomly places the computer's ships on its board.
 * 4. Displays the final boards for both the player and the computer after the setup is complete.
 *
 * @param player1 Reference to the player's game board.
 * @param computer Reference to the computer's game board.
 */
void boardSetupPVE(PlayerBoard &player1, PlayerBoard &computer) {
    // Initialize the fleets for both players
    initFleet(player1);
    initFleet(computer);

    // Place ships for player 1
    cout << "Player 1, set your board." << endl;
    for (int i = 0; i < FLEET_SIZE; i++) {
        displayBoards(player1.board, computer.board); // Display boards before placing the ship
        placeShip(player1, i); // Place each ship in the player's fleet
    }

    // Place ships randomly for computer
    cout << "Computer setting up board..." << endl;
    for (int i = 0; i < FLEET_SIZE; i++) {
        bool placed = false;
        while (!placed) {
            int row = rand() % BOARD_SIZE;
            int col = rand() % BOARD_SIZE;
            char orientation = (rand() % 2) ? 'h' : 'v';
            
            if (!spaceOccupied(computer, row, col, orientation, computer.fleet[i].size)) {
                // Place the ship
                if (orientation == 'h') {
                    for (int j = 0; j < computer.fleet[i].size; j++) {
                        computer.board[row][col + j] = computer.fleet[i].name[0];
                        computer.fleet[i].positions.push_back({row, col + j});
                    }
                } else {
                    for (int j = 0; j < computer.fleet[i].size; j++) {
                        computer.board[row + j][col] = computer.fleet[i].name[0];
                        computer.fleet[i].positions.push_back({row + j, col});
                    }
                }
                placed = true;
            }
        }
    }

    // Final display of both boards after setup
    displayBoards(player1.board, computer.board);
}

/**
 * Places a ship on the player's game board.
 *
 * This function performs the following steps:
 * 1. Retrieves the ship information from the player's fleet using the provided `shipIndex`.
 * 2. Prompts the player to enter valid starting coordinates and orientation for the ship using the `getValidShipInfo` function.
 * 3. Places the ship on the player's game board based on the provided coordinates and orientation.
 * 4. Stores the positions of the ship on the board in the `positions` vector of the `Ship` struct.
 *
 * @param playerBoard Reference to the player's game board.
 * @param shipIndex Index of the ship in the player's fleet to be placed.
 */
void placeShip(PlayerBoard &playerBoard, int shipIndex) {
    Ship &ship = playerBoard.fleet[shipIndex];

    // Example coordinates and orientation (assumed valid)
    int row; // Row index (0-9)
    int col; // Column index (0-9)
    char orientation; // 'h' for horizontal, 'v' for vertical

    // get valid ship info
    getValidShipInfo(row, col, orientation, playerBoard, shipIndex);

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

/**
 * Prompts the player to enter valid starting coordinates and orientation for a ship, and places the ship on the player's game board.
 *
 * This function performs the following steps:
 * 1. Retrieves the ship information from the player's fleet using the provided `shipIndex`.
 * 2. Prompts the player to enter valid starting coordinates and orientation for the ship.
 * 3. Validates the input and checks if the specified location is available on the board.
 * 4. Places the ship on the player's game board based on the provided coordinates and orientation.
 * 5. Stores the positions of the ship on the board in the `positions` vector of the `Ship` struct.
 *
 * @param playerBoard Reference to the player's game board.
 * @param shipIndex Index of the ship in the player's fleet to be placed.
 */
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

/**
 * Checks if the specified space on the player's game board is already occupied by a ship.
 *
 * @param playerBoard Reference to the player's game board.
 * @param row The row index of the space to check.
 * @param col The column index of the space to check.
 * @param orientation The orientation of the ship being placed ('h' for horizontal, 'v' for vertical).
 * @param shipSize The size of the ship being placed.
 * @return True if the space is occupied, false otherwise.
 */
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

/**
 * Handles the player's turn in the Battleship game.
 * The function prompts the player to enter a shot, validates the input, and updates the computer's board accordingly.
 * It also checks if the shot hits or misses a ship, and updates the hit count for the corresponding ship.
 * Finally, it displays the updated boards after the turn.
 *
 * @param player The player's PlayerBoard object.
 * @param computer The computer's PlayerBoard object.
 */
void playerTurn(PlayerBoard &player, PlayerBoard &computer) {
    int row, col;
    char letter;
    bool validShot = false;

    while (!validShot) {
        cout << "Player's turn. Enter your shot (e.g., A 1): ";
        cin >> letter >> col;

        //emergency fix: if input fails, clear error and ignore
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999999999999999999, '\n');
            cout << "Invalid input. Please enter a valid shot (e.g., A 1)." << endl;
            continue;
        }

        row = toupper(letter) - 'A'; // Convert letter to row index
        col -= 1; // Convert number to column index (0-based)

        // Check if the shot is valid
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            if (computer.board[row][col] != 'H' && computer.board[row][col] != 'M') {
                validShot = true; // Valid shot found
                if (computer.board[row][col] != ' ') {
                    cout << "Hit!" << endl;
                    char shipSymbol = computer.board[row][col]; // get symbol of ship
                    computer.board[row][col] = 'H'; // Mark hit on the computer's board
                    
                    // Update hit count for the corresponding ship
                    for (int i = 0; i < FLEET_SIZE; i++) {
                        // Check if the hit position matches any ship's position
                        for (int j = 0; j < computer.fleet[i].positions.size(); j++) {
                            if (computer.fleet[i].positions[j].row == row && computer.fleet[i].positions[j].col == col) {
                                computer.fleet[i].hitCount++;
                                // Check if the ship is sunk
                                if (computer.fleet[i].hitCount >= computer.fleet[i].size) {
                                    cout << "You sunk the " << computer.fleet[i].name << "!" << endl;
                                }
                                break; // Break out of the inner loop once the ship is found
                            }
                        }
                    }

                } else {
                    cout << "Miss!" << endl;
                    computer.board[row][col] = 'M'; // Mark miss on the computer's board
                }
            } else {
                cout << "You have already shot at this location. Please try again." << endl;
            }
        } else {
            cout << "Invalid shot. Please try again." << endl;
        }
    }

    displayBoards(player.board, computer.board); // Show boards after the turn
}

/**
 * Implements the computer's turn in a game of Battleship.
 * The computer can operate in two modes: "Hunt" mode to randomly select a target,
 * and "Target" mode to systematically target the surrounding cells of a hit.
 * The function updates the player's board and displays the results of the computer's turn.
 *
 * @param computer The computer's PlayerBoard object.
 * @param player The player's PlayerBoard object.
 */
void computerTurn(PlayerBoard &computer, PlayerBoard &player) {
    static bool inTargetMode = false; // Track if we are in target mode
    static vector<Point> targetStack; // Vector for potential targets
    int row, col;

    if (!inTargetMode) {
        // Hunt mode: Randomly select a target
        do {
            row = rand() % BOARD_SIZE; // Random row
            col = rand() % BOARD_SIZE; // Random column
        } while (player.board[row][col] == 'H' || player.board[row][col] == 'M'); // Ensure it's a valid shot

        // Check if the shot is valid
        if (player.board[row][col] != ' ') {
            cout << "Computer hit at " << static_cast<char>('A' + row) << " " << (col + 1) << "!" << endl;
            player.board[row][col] = 'H'; // Mark hit on the player's board
            inTargetMode = true; // Switch to target mode

            // Add surrounding cells to the target vector
            if (row > 0) targetStack.push_back({row - 1, col}); // Up
            if (row < BOARD_SIZE - 1) targetStack.push_back({row + 1, col}); // Down
            if (col > 0) targetStack.push_back({row, col - 1}); // Left
            if (col < BOARD_SIZE - 1) targetStack.push_back({row, col + 1}); // Right

            // Update hit count for the corresponding ship
            for (int i = 0; i < FLEET_SIZE; i++) {
                for (const auto &pos : player.fleet[i].positions) {
                    if (pos.row == row && pos.col == col) {
                        player.fleet[i].hitCount++;
                        if (player.fleet[i].hitCount >= player.fleet[i].size) {
                            cout << "The computer sunk your " << player.fleet[i].name << "!" << endl;
                        }
                        break;
                    }
                }
            }
        } 

        // computer missed, keep going
        else {
            cout << "Computer missed at " << static_cast<char>('A' + row) << " " << (col + 1) << "!" << endl;
            player.board[row][col] = 'M'; // Mark miss on the player's board
        }
    } 
    else if (inTargetMode || !targetStack.empty()) {
        cout << "Computer is targeting..." << endl;
        bool validShotTaken = false;
        
        // Try targets until we get a valid shot
        while (!targetStack.empty() && !validShotTaken) {
            Point target = targetStack.back();
            targetStack.pop_back();
            row = target.row;
            col = target.col;

            // If this target is valid, take the shot
            if (player.board[row][col] != 'H' && player.board[row][col] != 'M') {
                validShotTaken = true;  // Will exit loop after this shot
                if (player.board[row][col] != ' ') {
                    // Hit logic - keep existing code for hit processing
                    cout << "Computer hit at " << static_cast<char>('A' + row) << " " << (col + 1) << "!" << endl;
                    player.board[row][col] = 'H';
                    
                    // Add surrounding targets - keep existing code
                    if (row > 0) targetStack.push_back({row - 1, col});
                    if (row < BOARD_SIZE - 1) targetStack.push_back({row + 1, col});
                    if (col > 0) targetStack.push_back({row, col - 1});
                    if (col < BOARD_SIZE - 1) targetStack.push_back({row, col + 1});
                    
                    // Keep existing hit count and ship sinking logic
                    for (int i = 0; i < FLEET_SIZE; i++) {
                        for (const auto &pos : player.fleet[i].positions) {
                            if (pos.row == row && pos.col == col) {
                                player.fleet[i].hitCount++;
                                if (player.fleet[i].hitCount >= player.fleet[i].size) {
                                    cout << "The computer sunk your " << player.fleet[i].name << "!" << endl;
                                }   
                            }
                        }
                    }
                } else {
                    cout << "Computer missed at " << static_cast<char>('A' + row) << " " << (col + 1) << "!" << endl;
                    player.board[row][col] = 'M';
                }
            }
            // If invalid, loop will continue to next target
        }
        
        // If no valid shots were possible, return to hunt mode
        if (!validShotTaken) {
            inTargetMode = false;
        }
    }
    displayBoards(computer.board, player.board); // Show boards after the turn
}

/**
 * Checks if the game is over by determining if all ships for either the player or the computer have been sunk.
 *
 * @param player The player's board.
 * @param computer The computer's board.
 * @return `true` if the game is over, `false` otherwise.
 */
bool isGameOver(const PlayerBoard &player, const PlayerBoard &computer) {
    // Check if all ships are sunk for the computer
    bool computerShipsSunk = true;
    for (int i = 0; i < FLEET_SIZE; i++) {
        if (computer.fleet[i].hitCount < computer.fleet[i].size) {
            computerShipsSunk = false; // At least one ship is still afloat
            break;
        }
    }

    // Check if all ships are sunk for the player
    bool playerShipsSunk = true;
    for (int i = 0; i < FLEET_SIZE; i++) {
        if (player.fleet[i].hitCount < player.fleet[i].size) {
            playerShipsSunk = false; // At least one ship is still afloat
            break;
        }
    }

    // Determine the game state
    if (computerShipsSunk) {
        cout << "Player 1 wins!" << endl;
        return true; // All computer ships are sunk
    } else if (playerShipsSunk) {
        cout << "Player 1 looses!" << endl;
        return true; // All player ships are sunk
    }

    return false; // Game continues
}
