/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
Course: Object Oriented Programming
Trimester: 2410??
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
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
    list<Ship*> ships;
    int NumberOfBattleShip = 0;
    char BattleShipSymbol;
    int NumberOfCruiser = 0;
    char CruiserSymbol ;
    int NumberOfDestroyer = 0;
    char DestroyerSymbol ;
    int NumberOfFrigate = 0;
    char FrigateSymbol ;
    int NumberOfCorvette = 0;
    char CorvetteSymbol ;
    int NumberOfAmphibious = 0;
    char AmphibiousSymbol ;
    int NumberOfSuperShip = 0;
    char SuperShipSymbol ;
};

class game
{
private:
    int Width{ 0 }, Height{ 0 };
    char** grid ;
    list<Ship*> queue;
    Team* A, * B;
public:
    int iterations{ 0 };
    Battlefield* battlefield;
    game();
    ~game();
    void addShipToGame(Ship* ship);
    void displayBattleField(std::ostream& os = std::cout) const;
    void hardaddShipToGame(Ship* ship, int x, int y);
    bool shipListEmpty()const;
    bool teamAEmpty()const;
    bool teamBEmpty()const;
    bool gameInit(std::string&& filename);
    void actionQueue();
    void fillQueue();
    void respawn();
    void removeDeadShipFromTeam();// need more working and fixes, fixed.
    Team* getTeam(char teamSymbol) const;
    void removeFromQueues(Ship* ship);
    friend std::ostream& operator<<(std::ostream& os, const game& g);

};

#endif