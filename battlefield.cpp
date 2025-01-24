#include <iostream>
#include <random>
#include "Battlefield.h"
#include "Ships.h"
#include "helpers.h"

void Battlefield::initializeGrid()
{
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            grid[i][j] = '0';
}

// my thoughts just for tracking
// will set the grid in battelfield = to the grid from game
// then after copying everything, it will set gr(grid in game) to nullptr;
Battlefield::Battlefield(char **gr, int w, int h) : width(w), height(h)
{
    grid = gr;
    for (int i = 0; i < height; ++i)
        grid[i] = gr[i];
    **grid = **gr;
    gr = nullptr;
}

Battlefield::~Battlefield()
{
    for (int i = 0; i < height; ++i)
        delete[] grid[i];
    delete[] grid;
    std::cout << "battlefled deleted\n";
}

// To do, figure out how to place ships randmonly using random  x = rand() % height; y = rand() % width;
void Battlefield::placeShip(Ship *ship)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, width - 1);
    std::uniform_int_distribution<> disY(0, height - 1);
    
    int x, y;
    do
    {
        x = disX(gen);
        y = disY(gen);
    } while (grid[y][x] != '0');

    ship->setShipPosition(x, y);
    ships.push_back(ship);
    std::cout << "ship of type " << ship->getType() << " is placed at Y:X " << y << ":" << x << std::endl;
    grid[y][x] = ship->getSymbol();
}

void Battlefield::hardPlaceShip(Ship *ship, int x, int y)
{
    ship->setShipPosition(x, y);
    ships.push_back(ship);
    std::cout << "ship of type " << ship->getType() << " is placed at Y:X " << y << ":" << x << std::endl;
    grid[y][x] = ship->getSymbol();
}
void Battlefield::display() const
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
            std::cout << grid[i][j] << ' ';
        std::cout << std::endl;
    }
}

Ship *Battlefield::getShipAt(int x, int y)
{
    list<Ship*> *p = ships.prev;
    while (p != nullptr)
    {
        if (p->data->getShipPositionX() == x && p->data->getShipPositionY() == y)
        {
            return p->data;
        }
        p = p->next;
    }
    
    return nullptr;
}
int Battlefield::getWidth() const { return width; }
int Battlefield::getHeight() const { return height; }
char **Battlefield::getGrid() const { return grid; }
