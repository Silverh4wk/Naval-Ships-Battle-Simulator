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
#include <iostream>
#include"Ships.h"
#include <random>
#include "Destroyer.h"
#include "Battlefield.h"
#include "Cruiser.h"
#include "Macros.h"


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
*/


Cruiser::Cruiser(char shipSymbol = 'c', std::string type="Cruiser", char teamSymbol='T')
    : Ship(shipSymbol, type, teamSymbol),   
    RamShip(shipSymbol, type, teamSymbol)
{}

Cruiser::Cruiser(Cruiser&& other) noexcept
    : Ship(std::move(other)),  
    RamShip(std::move(other))  
{}

Cruiser& Cruiser::operator=(Cruiser&& other) noexcept {
    if (this != &other) {
        Ship::operator=(std::move(other));
        RamShip::operator=(std::move(other));
    }
    return *this;
}

Cruiser::~Cruiser() {std::cout<< getType() << " was deleted\n"; }

//will check its neighbouring positions and decide if its gonna ram or move to a random positin other wise 

void Cruiser::ram(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) {
    int nx = 0;
    int ny = 0;
    bool foundEnemy = false;

    std::cout << "\n" << getSymbol() << " is deciding where to Ram\n";
    std::cout << "________________________________________\n";

    for (int i = -1; i <= 1 && !foundEnemy; ++i) {
        for (int j = -1; j <= 1 && !foundEnemy; ++j) {
            nx = getShipPositionX() + j;
            ny = getShipPositionY() + i;

            //  Check if the new position is within bounds
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) continue;

            char cell = gr[ny][nx];
            if (cell == '0' || cell == '1' || cell == this->getSymbol()) continue;

            Ship* enemyShip = battlefield.getShipAt(nx, ny);
            if (enemyShip && enemyShip->getTeamSymbol() != this->getTeamSymbol()) {

                enemyShip->reduceLives(battlefield);

                // Move cruiser to enemy's position
                int oldx = getShipPositionX();
                int oldy = getShipPositionY();
                gr[oldy][oldx] = battlefield.getTerrainAt(oldy, oldx); // Restore terrain
                gr[ny][nx] = this->getSymbol();                        // Update new position
                setShipPosition(nx, ny);
                shipsDestroyed++;
                foundEnemy = true;
            }
        }
    }

    
//   If no enemy ship is detected in the neighboring cells, the function proceeds to randomly select 
//   an adjacent cell (up to 10 attempts) to move the Cruiser. This random move is only performed if the 
//   selected cell is within bounds and unoccupied (i.e., marked by '0'). If a valid random move is found, 
//   the Cruiser's position is updated accordingly; otherwise, the Cruiser remains in its current location.
    if (!foundEnemy)
    {
        RANDOM_DEVICE;
        std::uniform_int_distribution<int> uniform_dist(-1, 1); 

        int maxAttempts = 10;  
      
        do
        {
            ny = this->getShipPositionY() + uniform_dist(r1);
            nx = this->getShipPositionX() + uniform_dist(r1);
            int oldx = this->getShipPositionX();
            int oldy = this->getShipPositionY();

            if (ny >= 0 && ny < rows && nx >= 0 && nx < cols)
            {
                if (gr[ny][nx] == '0')
                {
                    gr[oldy][oldx] = battlefield.getTerrainAt(oldy, oldx); 
                    gr[ny][nx] = this->getSymbol();
                    this->setShipPosition(nx, ny);
                    std::cout << "No enemy found. Moved to random position (" << ny << ", " << nx << ").\n";
                    break;
                }
            }
        } while (--maxAttempts > 0);

        if (maxAttempts == 0) {
            std::cout << "No valid move found. Staying in place.\n"; 
        }
    }
}



void Cruiser::actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
       ram(gr, rows, cols, battlefield,gameManager);
       //finally it checks for upgrade
       if (shipsDestroyed >= 3) {
           std::cout << "Cruiser upgraded to Destroyer!\n";
           Destroyer* newDestroyer = new Destroyer(std::move(*this));
           battlefield.replaceShip(this, newDestroyer, gameManager);
           return;
       }
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}