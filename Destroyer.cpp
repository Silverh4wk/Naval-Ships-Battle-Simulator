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
#include "Ships.h"
#include "Destroyer.h"
#include "SuperShip.h" 
#include "Cruiser.h"
#include "BattleShip.h"
#include "Battlefield.h"
#include "Macros.h"

// REMINDER TO NOT TOUCH THIS FILE AGAIN 
/*
--------------------------------------------------------------------
 Destroyer --:
 it can move it can shoot it can ram it can look
 if kill = 3, upgrades to supership
 --------------------------------------------------------------------
*/

Destroyer::Destroyer(char shipSymbol, std::string type, char teamSymbol)
    : Ship(shipSymbol, type, teamSymbol),
    BattleShip(shipSymbol, type, teamSymbol),
    Cruiser(shipSymbol, type, teamSymbol)
{
    upgradeToDestroyer();

}

// Conversion from BattleShip
Destroyer::Destroyer(BattleShip&& base) noexcept
    : Ship(base.getSymbol(), "Destroyer", base.getTeamSymbol()),  // Extract values before move
    BattleShip(base.getSymbol(), "Destroyer", base.getTeamSymbol()),
    Cruiser(base.getTeamSymbol(), base.getType(), base.getTeamSymbol())

    
{
    upgradeToDestroyer();
 //double checking not gonna mess with it again, LOTS OF ISSUES FOR SOMEREASON 
    this->setShipPosition(base.getShipPositionX(), base.getShipPositionY());

}

// Conversion from Cruiser
Destroyer::Destroyer(Cruiser&& base) noexcept
    : Ship(base.getSymbol(), "Destroyer", base.getTeamSymbol()),
    BattleShip(base.getTeamSymbol(), "Destroyer", base.getTeamSymbol()),
    Cruiser(base.getSymbol(), "Destroyer", base.getTeamSymbol())
{
    upgradeToDestroyer();
    this->setShipPosition(base.getShipPositionX(), base.getShipPositionY());
    SHIPS_INFO;

}
// factory function cuz i didnt know how to properly use movesemantics and im tired for now
//Destroyer* Destroyer::createFrom(Ship* source)
//{
//    Destroyer* dest = new Destroyer('D', "Destroyer", source->getTeamSymbol());
//    dest->setShipPosition(source->getShipPositionX(), source->getShipPositionY());
//    dest->setLives(source->getLives());
//    dest->setType("Destroyer");
//    dest->setSymbol('$');
//    return dest;
//}
void Destroyer::upgradeToDestroyer() {
    //upgrade benefit
    setLives(getLives() + 2);
    setDestroyedShipsNumber(-6);
     
}

void Destroyer::shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    RANDOM_DEVICE
        std::uniform_int_distribution<int> chanceX(0, cols - 1);
    std::uniform_int_distribution<int> chanceY(0, rows - 1);
    // remember to return to this after testing
    for (int i = 0; i < 2; ++i)
    {
        std::cout << "shooting # " << i + 1 << "\n";
        int targetX = chanceX(r1);
        int targetY = chanceY(r1);

        std::cout << "target coordinates: (" << targetY << ", " << targetX << ")\n";
        // Check if the target is within the city block distance of 5
        // SO MANY ISSUES HERE FIX SOON, also need to understand the city block distance constraint
        std::cout << "city block distance: " << std::abs(getShipPositionY() - targetY) << " + " << std::abs(getShipPositionX() - targetX) << "\n";
        std::cout << "city block distance: " << std::abs(getShipPositionX() - targetX) + std::abs(getShipPositionY() - targetY) << "\n";
        if (std::abs(getShipPositionX() - targetX) + std::abs(getShipPositionY() - targetY) <= 5)
        {
            char targetCell = gr[targetY][targetX];
            std::cout << "target cell: " << targetCell << "\n";

            Ship* enemyShip = battlefield.getShipAt(targetX, targetY); // Get the target ship
            // check if its not on the same team before shooting at it
            if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol())
            {
                std::cout << "Shooting at enemy ship at (" << targetY << ", " << targetX << ")\n";
                enemyShip->reduceLives(battlefield);
                gr[targetY][targetX] = battlefield.getTerrainAt(targetY, targetX);  // Clear the grid
                shipsDestroyed++;
                if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                    //destroyedShips.push_back(enemyShip->getSymbol());
                std::cout << enemyShip->getSymbol() << " destroyed\n";
                {
                    enemyShip = nullptr;
                    std::cout << "Ship out of the game! Total ships taken out: " << shipsDestroyed << "\n";

                    if (shipsDestroyed >= 4)
                    {
                        // Upgrade Battleship to Destroyer
                        std::cout << "Battleship upgraded to Destroyer!\n";
                        gr[getShipPositionY()][getShipPositionX()] = '0';
                        Destroyer* newDestroyer = new Destroyer(std::move(*this));
                        battlefield.replaceShip(this, newDestroyer, gameManager);
                        return; // so program doesn't use the deleted pointer or big crash happen
                    }
                }
            }

            else
            {
                std::cout << "no enemy ship found to shoot at (" << targetY << ", " << targetX << ")\n";
            }
        }
        else
        {
            std::cout << "Target out of range due to city block distance constraint.\n";
        }
    }
}

void Destroyer::ram(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) {
    int nx = 0;
    int ny = 0;
    bool foundEnemy = false;

    std::cout << "\n" << getSymbol() << " is deciding \n";
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
                std::cout << "Enemy ship symbol: " << enemyShip->getSymbol()
                    << " is dead? = " << enemyShip->isDestroyed() << "\n";

                // Move cruiser to enemy's position
                int oldx = getShipPositionX();
                int oldy = getShipPositionY();
                gr[oldy][oldx] = battlefield.getTerrainAt(oldy, oldx); // Restore terrain
                gr[ny][nx] = this->getSymbol();                        // Update new position
                setShipPosition(nx, ny);

                // Check if enemy is destroyed
                if (enemyShip->isDestroyed()) {
                    shipsDestroyed++;
                    std::cout << "Ship destroyed! Total ships destroyed: " << shipsDestroyed << "\n";
                    //destroyedShips.push_back(enemyShip->getSymbol());
                    std::cout << enemyShip->getSymbol() << " destroyed\n";
                }
                //finally it checks for upgrade
                /*if (shipsDestroyed >= 3) {
                    std::cout << "Cruiser upgraded to Destroyer!\n";
                    Destroyer* newDestroyer = new Destroyer(std::move(*this));
                    battlefield.replaceShip(this, newDestroyer, gameManager);
                    return;
                }*/

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

void Destroyer::setDestroyedShipsNumber(int number) { shipsDestroyed = number; }

void Destroyer::actions(char** gr, int rows, int cols, Battlefield& battlefield,game&gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        std::cout << " is ramming now \n";
        ram(gr, rows, cols, battlefield,gameManager);

        std::cout << " is looking now \n";
        look(gr, rows, cols);
        std::cout << " is moving now \n";
        move(gr, rows, cols, battlefield);
        std::cout << " is shooting now \n";
        shoot(gr, rows, cols, battlefield,gameManager);
       
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}
