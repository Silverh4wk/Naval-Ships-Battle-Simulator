/**********|**********|**********|
Program: Supership.cpp / SuperShip.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
**********|**********|**********/

#include "SuperShip.h"
#include <iostream>
#include "Battlefield.h"
#include "Cruiser.h"
#include "Amphibious.h"
#include "Destroyer.h"
#include "Macros.h"

SuperShip::SuperShip(char shipSymbol, std::string type, char teamSymbol)
    : Ship(shipSymbol, type, teamSymbol),
      Destroyer(shipSymbol, type, teamSymbol)
{
}

// Conversion from Amphibious
SuperShip::SuperShip(Amphibious &&base) noexcept
    : Ship(base.getSymbol(), "SuperShip", base.getTeamSymbol()),
        Destroyer(std::move(base))
{
    setLives(3);
    setTeamSymbol(base.getTeamSymbol());
    setShipPosition(base.getShipPositionX(), base.getShipPositionY());
    shipsDestroyed = 0;
}
// Conversion from DestroyerShip

SuperShip::SuperShip(Destroyer &&base) noexcept
    : Ship(base.getSymbol(), "SuperShip", base.getTeamSymbol()),
      Destroyer(std::move(base))
{
    setLives(3);
    setTeamSymbol(base.getTeamSymbol());
    setShipPosition(base.getShipPositionX(), base.getShipPositionY());
    shipsDestroyed = 0;
}
// The shoot here is amended to shoot 3 times in random directions in the same turn
void SuperShip::shoot(char **gr, int rows, int cols, Battlefield &battlefield, game &gameManager)
{
    for (int i = 0; i < 3; ++i)
    {
        int directions[8][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
        RANDOM_DEVICE
        std::uniform_int_distribution<int> uniform_dist(0, 7);
        int chance = uniform_dist(r1);
        int targetX = 0;
        int targetY = 0;
        // 1 in 8 chance to shoot 3 times in a random direction

        std::cout << "shooting # " << i + 1 << "\n";
        targetX = getShipPositionX() + directions[chance][0];
        targetY = getShipPositionY() + directions[chance][1];

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
                Ship *enemyShip = battlefield.getShipAt(targetX, targetY);

                if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol())
                {
                    std::cout << "Shooting at enemy ship at (" << targetY << ", " << targetX << ")\n";
                    enemyShip->reduceLives(battlefield);
                    gr[targetY][targetX] = battlefield.getTerrainAt(targetY, targetX); // Clear the grid
                    std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";
                    shipsDestroyed++;
                }
                else
                {
                    std::cout << "Team member found! skip shooting at (" << targetY << ", " << targetX << "). Rotating...\n";
                }
            }
        }
        else
        {
            std::cout << "Target out of bounds!!(" << targetY << ", " << targetX << "). Rotating...\n";
        }
    }
}
//supership inherits all the actions from destroyer and adds the shoot function

void SuperShip::actions(char **gr, int rows, int cols, Battlefield &battlefield, game &gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        std::cout << " is ramming now \n";
        ram(gr, rows, cols, battlefield, gameManager);

        shoot(gr, rows, cols, battlefield, gameManager);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}
