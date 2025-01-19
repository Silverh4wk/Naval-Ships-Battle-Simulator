#pragma once
#include "Ships.h"

class Battlefield
{
private:
    int width = 0, height = 0;
    char **grid;

    void initializeGrid();

public:
    Battlefield(char **gr, int w, int h);
    ~Battlefield();
    // To do, figure out how to place ships randmonly using random  x = rand() % height; y = rand() % width;

    void placeShip(Ship *ship);
    void hardPlaceShip(Ship *ship, int x, int y);

    int getWidth() const;
    int getHeight() const;
    char **getGrid() const;
    void display() const;
};