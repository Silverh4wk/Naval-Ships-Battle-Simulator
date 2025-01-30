#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
class Ship;
#include "helpers.h"

class Battlefield
{
private:
    int width = 0, height = 0;
    char **grid;
    void initializeGrid();
    list<Ship *> ships;

public:
    list<Ship *> &getShips()
    {
        return ships; 
    }
    list<Ship *> shipGraveYard;
    Battlefield(char **gr, int w, int h);
    ~Battlefield();
    // To do, figure out how to place ships randmonly using random  x = rand() % height; y = rand() % width;

    void placeShip(Ship *ship);
    void hardPlaceShip(Ship *ship, int x, int y);
    void replaceShip(Ship* oldShip, Ship* newShip);


    int getWidth() const;
    int getHeight() const;
    char **getGrid() const;
    void display() const;
    Ship *getShipAt(int x, int y);
};

#endif