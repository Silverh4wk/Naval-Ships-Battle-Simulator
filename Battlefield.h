/**********|**********|**********|
Program: Battlefield.cpp / Battlefield.h
Course: Object Oriented Programming
Trimester: 2410??
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
class Ship;
#include "helpers.h"
#include "game.h"

class Battlefield
{
private:
    int width = 0, Height = 0;
    char** grid=nullptr;
    list<Ship*> ships;
    char** terrain = nullptr;
public:
    list<Ship*>& getShips()
    {
        return ships;
    }
    list<Ship*> shipGraveYard;
    Battlefield(char** gr, int w, int h);
    ~Battlefield();
    // To do, figure out how to place ships randmonly using random  x = rand() % height; y = rand() % width;

    void placeShip(Ship* ship);
    void hardPlaceShip(Ship* ship, int x, int y);
    void replaceShip(Ship* oldShip, Ship* newShip, game& gameManager);
    char getTerrainAt(int y, int x) const;

    int getWidth() const;
    int getHeight() const;
    char** getGrid() const;
    void display(std::ostream& os = std::cout) const;
    Ship* getShipAt(int x, int y)const;
};

#endif