/**********|**********|**********|
Program: Battlefield.cpp / Battlefield.h
Course: Object Oriented Programming
Trimester: 2430
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


/**********|********** Commented Function Descriptions |**********|**********
 
this file handles the Battlefield of this game,
its used for initiating the game grid, and keeping a copy of it 
for changes that may happen to the grid later on during the game


functions:
- Battlefield Constructor:
    • Copies an external grid (gr) into its own allocated 'terrain'.
    • Stores dimensions 'width' and 'Height' for later use.
    
- getTerrainAt:
    • Returns the terrain character at the given (y, x) coordinate.
    
- Destructor:
    • Frees the allocated memory for the terrain grid.
    • Outputs debug messages indicating deletion.
    
- placeShip:
    • Randomly selects an empty location (where grid element is '0') to place a ship.
    • Updates ship's position and grid symbol.
    • Adds the ship to the internal ship list.
    
- hardPlaceShip:
    • Places a ship at a user-specified (x, y) coordinate.
    • Updates ship's position and grid symbol.
    • Adds the ship to the ship list.
    
- display:
    • Outputs the current state of the grid to the provided ostream.
    
- getShipAt:
    • Searches the ship list to find a ship whose position matches (x, y).
    • Returns a pointer to the ship if found; otherwise, returns nullptr.
    
- getWidth & getHeight:
    • Provide access to grid dimensions.
    
- getGrid:
    • Returns the raw grid pointer.
    
- replaceShip:
    • Upgrades a ship by replacing an old ship with a new ship.
    • Updates the corresponding team roster within the game manager.
    • Replaces the symbol in the grid and updates the internal ship list.
***************************************************************/

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