#include <iostream>
#include "battlefield.h"
// #include "ships.h"
#include <fstream>
#include <sstream>

struct Team
{
public:
    int NumberOfShips = 0;

    int NumberOfBattleShip = 0;
    char BattleShipSymbol;
    int NumberOfCruiser = 0;
    char CruiserSymbol;
    int NumberOfDestroyer = 0;
    char DestroyerSymbol;
    int NumberOfFrigate = 0;
    char FrigateSymbol;
    int NumberOfCorvette = 0;
    char CorvetteSymbol;
    int NumberOfAmphibious = 0;
    char AmphibiousSymbol;
    int NumberOfSuperShip = 0;
    char SuperShipSymbol;
};

class game
{
private:
    int iterations{0},
        Width{0}, Height{0};
    Team *A, *B;
    // Ship *ships;
    char **grid;

public:
    Battlefield *battlefield;
    game();
    ~game();
    void addShipToGame(Ship *ship);
    void displayBattleField() const;
    void hardaddShipToGame(Ship *ship, int x, int y);

        bool gameInit(std::string &&filename);
};
