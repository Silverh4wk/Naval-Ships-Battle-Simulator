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
 Cruiser --:
 it can look it can move and it can ram
 will not shoot at all and will terminate ships at its path
 in each turn it looks at 3x3 window, it will move to one of them
 if the cruiser kills 3 of them, cruiser ---> upgrade to destroyer

 --------------------------------------------------------------------
*/

Cruiser::Cruiser(char shipSymbol = 'c', std::string type="Cruiser", char teamSymbol='T')
    : Ship(shipSymbol, type, teamSymbol),   
    RamShip(shipSymbol, type, teamSymbol)
{}

Cruiser::Cruiser(Cruiser&& other) noexcept
    : Ship(std::move(other)),  
    RamShip(std::move(other))  
{
    shipsDestroyed = other.shipsDestroyed;
    destroyedShips = std::move(other.destroyedShips);
}

Cruiser& Cruiser::operator=(Cruiser&& other) noexcept {
    if (this != &other) {
        Ship::operator=(std::move(other));
        RamShip::operator=(std::move(other));
        shipsDestroyed = other.shipsDestroyed;
        destroyedShips = std::move(other.destroyedShips);
    }
    return *this;
}

Cruiser::~Cruiser() {std::cout<< getType() << " was deleted\n"; }


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
                shipsDestroyed++;

                // Move cruiser to enemy's position
                int oldx = getShipPositionX();
                int oldy = getShipPositionY();
                gr[oldy][oldx] = battlefield.getTerrainAt(oldy, oldx); // Restore terrain
                gr[ny][nx] = this->getSymbol();                        // Update new position
                setShipPosition(nx, ny);

                // Check if enemy is destroyed
                if (enemyShip->isDestroyed()) {
                    std::cout << "Ship destroyed! Total ships destroyed: " << shipsDestroyed << "\n";
                    //destroyedShips.push_back(enemyShip->getSymbol());
                    std::cout << enemyShip->getSymbol() << " destroyed\n";
                }
                foundEnemy = true;
            }
        }
    }


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
       //ram(gr, rows, cols, battlefield,gameManager);
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