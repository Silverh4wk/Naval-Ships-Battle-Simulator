/**********|**********|**********|
Program: Frigate.cpp / Frigate.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
**********|**********|**********/

#include "Frigate.h"
#include "Battlefield.h"
#include <iostream>
#include <cmath>
#include "Macros.h"
#include"Corvette.h"


/*
--------------------------------------------------------------------
 Frigate --:
 it can shoot at neighbouring cells 1x1
 and when it shoots it clock wise direction
 if kill = 3, upgrades to corvette
--------------------------------------------------------------------
*/

Frigate::Frigate(char shipSymbol, std::string type, char teamSymbol) : 
Ship(shipSymbol, type, teamSymbol),
ShootingShip(shipSymbol, type, teamSymbol){}

Frigate::Frigate(Frigate&& other) noexcept
    : Ship(other.getSymbol(), other.getType(), other.getTeamSymbol()),
    ShootingShip(other.getSymbol(), other.getType(), other.getTeamSymbol())
{
    shipsDestroyed = other.shipsDestroyed;

}

Frigate& Frigate::operator=(Frigate&& other) noexcept {
    if (this != &other) {
        Ship::operator=(std::move(other));
        ShootingShip::operator=(std::move(other));
        shipsDestroyed = other.shipsDestroyed;

    }
    return *this;
}

void Frigate::shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    int shipX = getShipPositionX();
    int shipY = getShipPositionY();

    // Clockwise movement order
    int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

    for (int i = 0; i < 8; ++i) // move only in 8 directions clockwise
    {
        int targetX = shipX + dx[clock];
        int targetY = shipY + dy[clock];

        // checks if its out of bounds 
        if (targetX >= 0 && targetX < cols && targetY >= 0 && targetY < rows)
        {
            char targetCell = gr[targetY][targetX];
            // if it's just water or an island or the ship itself
            if (targetCell == '0' || targetCell == '1')
            {
                std::cout << "Nothing to shoot at (" << targetY << ", " << targetX << "). Rotating...\n";
            }
            else
            {
                std::cout << "Shooting at (" << targetY << ", " << targetX << ")\n";
                Ship* enemyShip = battlefield.getShipAt(targetX, targetY);

                if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol())
                {
                    std::cout << "Shooting at enemy ship at (" << targetY << ", " << targetX << ")\n";
                    enemyShip->reduceLives(battlefield);
                    gr[targetY][targetX] = battlefield.getTerrainAt(targetY, targetX); // Clear the grid
                    std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";

                    if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                    {
                        shipsDestroyed++;
                        destroyedShips.push_back(enemyShip->getSymbol());
                        std::cout << enemyShip->getSymbol() << " destroyed\n";
                        enemyShip = nullptr;
                        std::cout << "Ship destroyed! Total ships destroyed: " << shipsDestroyed << "\n";
                    }
                   
                }
                else
                {
                    std::cout << "Team member found! skip shooting at (" << targetY << ", " << targetX << "). Rotating...\n";
                }
            }
            clock = (clock + 1) % 8;
            return;  // End turn after shooting
        }
        else
        {
            std::cout << "Target out of bounds!!(" << targetY << ", " << targetX << "). Rotating...\n";
        }
        clock = (clock + 1) % 8;
        return;  // End turn after shooting
    }
}



void Frigate::actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        shoot(gr, rows, cols, battlefield,gameManager);
    }
       if (shipsDestroyed >= 3) {
           std::cout  <<getType()<< " upgraded to SuperShip!\n";
           corvette* newcorvette = new corvette(std::move(*this));
           battlefield.replaceShip(this, newcorvette, gameManager);
           return;
       }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}

