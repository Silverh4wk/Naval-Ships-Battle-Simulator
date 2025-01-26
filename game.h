#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <sstream>

#include "helpers.h"
class Ship;
class Battlefield;
struct Team
{
public:
    int NumberOfShips = 0;
    list<Ship *> ships;
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
    int Width{0}, Height{0};
    char **grid;
    list<Ship *> queue;
    Team *A, *B;
public:
    int iterations{0};
    Battlefield *battlefield;
    game();
    ~game();
    void addShipToGame(Ship *ship);
    void displayBattleField() const;
    void hardaddShipToGame(Ship *ship, int x, int y);
    bool shipListEmpty()const ;
    bool teamAEmpty()const;
    bool teamBEmpty()const;
    bool gameInit(std::string &&filename);
    void actionQueue();
    void fillQueue();
    void respawn();
    void removeDeadShipFromTeam(list<Ship*>& teamShips, Ship* deadShip);// need more working and fixes
};
#endif