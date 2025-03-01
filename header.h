#ifndef BATTLESHIP_HEADER_H
#define BATTLESHIP_HEADER_H

#include <vector>
#include <string>
using namespace std;

// Constants
const int BOARD_SIZE = 10;
const int FLEET_SIZE = 5;

// Ship sizes
const int CARRIER_SIZE = 5;
const int BATTLESHIP_SIZE = 4;
const int CRUISER_SIZE = 3;
const int SUBMARINE_SIZE = 3;
const int DESTROYER_SIZE = 2;

struct Point {
    int row;
    int col;
};

struct Ship {
    string name;
    int size;
    int hitCount;
    vector<Point> positions;
};

struct PlayerBoard {
    char board[BOARD_SIZE][BOARD_SIZE];
    Ship fleet[FLEET_SIZE];
};

// Function declarations
void displayBoards(char board1[][BOARD_SIZE], char board2[][BOARD_SIZE]);
void initFleet(PlayerBoard &playerBoard);
void boardSetup(PlayerBoard &player1, PlayerBoard &player2);
void placeShip(PlayerBoard &playerBoard, int shipIndex);
void getValidShipInfo(int &row, int &col, char &orientation, PlayerBoard &playerBoard, int shipIndex);
bool spaceOccupied(const PlayerBoard &playerBoard, int row, int col, char orientation, int shipSize);
void playerTurn(PlayerBoard &player, PlayerBoard &computer);
void computerTurn(PlayerBoard &computer, PlayerBoard &player);
bool isGameOver(const PlayerBoard &player, const PlayerBoard &computer);
void boardSetupPVE(PlayerBoard &player1, PlayerBoard &computer);
ifstream& getInputFile();

#endif // BATTLESHIP_HEADER_H