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
#include <iostream>
#include <random>
#include "Battlefield.h"
#include "ships.h"
#include "helpers.h"



// my thoughts just for tracking
// will set the grid in battelfield = to the grid from game
// then after copying everything, it will set gr(grid in game) to nullptr;
Battlefield::Battlefield(char** gr, int w, int h) : width(w), Height(h), grid(gr)
{
    terrain = new char* [Height];
    for (int i = 0; i < Height; ++i)
    {
        terrain[i] = new char[width];
        for (int j = 0; j < width; ++j)
            terrain[i][j] = gr[i][j];
    }
}
char Battlefield::getTerrainAt(int y, int x) const { return terrain[y][x]; }

Battlefield::~Battlefield()
{


    // Delete the terrain
   if (terrain) {
        std::cout << "terrain is getting deleted \n";
        for (int i = 0; i < Height; ++i) {
            delete[] terrain[i];
        }
        delete[] terrain;
        terrain = nullptr;
    }
        std::cout << "battlefield destrctor called\n";
}

// To do, figure out how to place ships randmonly using random  x = rand() % height; y = rand() % width;
void Battlefield::placeShip(Ship* ship)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, width - 1);
    std::uniform_int_distribution<> disY(0, Height - 1);

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

void Battlefield::hardPlaceShip(Ship* ship, int x, int y)
{
    ship->setShipPosition(x, y);
    ships.push_back(ship);
    std::cout << "ship of type " << ship->getType() << " is placed at Y:X " << y << ":" << x << std::endl;
    grid[y][x] = ship->getSymbol();
}
void Battlefield::display(std::ostream& os) const
{
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < width; ++j)
            os << grid[i][j] << ' ';
        os<< "\n";
    }
}

Ship* Battlefield::getShipAt(int x, int y)const
{
    list<Ship*>* p = ships.head;
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
int Battlefield::getHeight() const { return Height; }
char** Battlefield::getGrid() const { return grid; }

// upgrade system
//  Remove old ship from the battlefield
//  then set the new ship’s position
//  Replace it in the ship list
//  Add the new ship to the battlefield in place of the older one .... hope this works IT DOESNT
void Battlefield::replaceShip(Ship* oldShip, Ship* newShip, game& gameManager) {
    // 1. Get team from game manager
    Team* team = gameManager.getTeam(newShip->getTeamSymbol());

    // 2. Update the team roster
    if (team) {
        // Remove the old ship from team
        for (int i = 0; i < team->ships.getSize(); ++i) {
            if (team->ships.getNode(i) == oldShip) {
                std::cout << "old ship is getting removed \n";
                team->ships.deleteNodeAtIndex(i);
                break;
            }
        }

        // Add new ship to team
        team->ships.push_back(newShip);
        std::cout<<"added new ship to team" << newShip->getTeamSymbol() << " " << newShip->getType() << "\n";
    }

    // 3. Update the battlefield state
    int x = oldShip->getShipPositionX();
    int y = oldShip->getShipPositionY();
    grid[y][x] = newShip->getSymbol();

    // 4. Update global ship list
    for (int i = 0; i < ships.getSize(); ++i) {
        if (ships.getNode(i) == oldShip) {
            ships.deleteNodeAtIndex(i);
            delete oldShip;
            ships.insertNodeAtIndex(i, newShip);
            break;
        }
    }

    std::cout << "Ship upgraded in team " << newShip->getTeamSymbol() << "\n";

}