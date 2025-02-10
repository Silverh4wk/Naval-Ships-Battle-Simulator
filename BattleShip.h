/**********|**********|**********|
Program: Battleship.cpp / Battleship.h
Course: Object Oriented Programming
Trimester: 2430
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Ships.h"

/*
--------------------------------------------------------------------

Functionality Overview for BattleShip --:

it can shoot, it can move, it can see
 looks at its current pos then decide to move
 move once then shoot twice at random positions, x+y is 5 blocks
 cant move to a location that contain another Ship
 if shoot hit = 4 ---> upgrade to destroyer

Functions and their operations:

1. move:
    - Randomly selects one of four directions (up, right, down, left).
    - Checks if the new position is within grid boundaries and unoccupied.
    - If valid, updates the ship’s grid position and logs the movement.
    - If not, logs that the move in the chosen direction is not possible.

2. look:
    - Scans all adjacent cells (including diagonal neighbors) around the ship.
    - Reports any detected enemy ships that are not on the same team.
    - Alerts about cells that are out-of-bounds.

3. shoot:
    - Fires two shots at random target positions on the grid.
    - Validates that each target is within a city block distance of 5 from the ship.
    - Checks if an enemy ship occupies the target cell.
    - If an enemy is hit, reduces its lives, updates the grid, and increases the hit counter.
    - Otherwise, logs that no enemy ship was found at the target.

4. actions:
    - If the ship is active (i.e., not queued for death):
         - Displays current ship information.
         - Executes look, move, and shoot operations in sequence.
         - If the ship accumulates four successful hits, it upgrades to a Destroyer.
    - If the ship is marked for respawn, it delays further actions.
*/


class BattleShip : public MovingShip, public ShootingShip, public SeeingRobot
{
public:
    BattleShip(char shipSymbol, std::string type, char teamSymbol);
    ~BattleShip();
    BattleShip(BattleShip&&) noexcept;
    BattleShip& operator=(BattleShip&& other) noexcept;


    virtual void move(char** gr, int rows, int cols, Battlefield& battlefield) override;

    virtual void look(char** gr, int rows, int cols) override;

    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;

    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;

        
};

#endif 
