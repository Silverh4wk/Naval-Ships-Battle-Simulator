/**********|**********|**********|
Program: Cruiser.cpp / Cruiser.h
Course: Object Oriented Programming
Trimester: 2430
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#ifndef CRUISER_H
#define CRUISER_H

#include "Ships.h"
class Destroyer;

/*
--------------------------------------------------------------------
Functionality Overview for Cruiser --:

1. ram:
    - Scans its surrounding 3x3 window centered at the Cruiser's current position.
    - If an enemy ship (a ship that is not an empty cell and not from the same team) is found:
      • Reduces the enemy ship’s lives.
      • Moves to the enemy's position, effectively "ramming" and eliminating it.
      • Increments an internal counter (shipsDestroyed) for each enemy ship destroyed.
    - If no enemy is found:
      • Tries several attempts to move randomly into an empty nearby cell.
      • If no valid move is determined, the Cruiser remains in its current position.

2. actions:
    - Serves as the main behavior routine executed each turn.
    - Calls the ram function to execute its ramming (or random) movement.
    - Checks if it has destroyed at least 3 enemy ships:
      • If so, it upgrades to a Destroyer by transferring its state and replacing itself on the battlefield.
    - If the Cruiser is in a temporary disabled state (flagged by isInDeathQueue), it skips actions and notes that it is waiting to respawn.

    --------------------------------------------------------------------
*/

class Cruiser : public RamShip
{
private:
public:
    Cruiser(char shipSymbol, std::string type, char teamSymbol);

    Cruiser(Cruiser&& other) noexcept;
    Cruiser& operator=(Cruiser&& other) noexcept;

    ~Cruiser();
    virtual void ram(char** gr, int rows, int cols, Battlefield& battlefield,game&gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};
#endif
