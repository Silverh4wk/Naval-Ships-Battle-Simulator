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
#include "Corvette.h"
#include "Battlefield.h"
#include <iostream>
#include <random>
#include "Macros.h"

corvette::corvette(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol)
,ShootingShip(shipSymbol,type,teamSymbol){}

void corvette::shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    int directions[8][2] = { {0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1} };
    RANDOM_DEVICE
        std::uniform_int_distribution<int> uniform_dist(0, 7);
    int chance = uniform_dist(r1);
    int targetX = 0;
    int targetY = 0;
    // 1 in 8 chance to shoot in a random direction

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
                    enemyShip = nullptr; // set the dead ship to null
                    std::cout << "Ship destroyed! Total ships destroyed: " << shipsDestroyed << "\n";
                }
            }
            else
            {
                std::cout << "Team member found! skip shooting at (" << targetY << ", " << targetX << "). Rotating...\n";
            }
        }
        return;  // End turn after shooting
    }
    else
    {
        std::cout << "Target out of bounds!!(" << targetY << ", " << targetX << "). Rotating...\n";
        return;  // End turn after shooting
    }
}


void corvette::actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        shoot(gr, rows, cols, battlefield,gameManager);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}

corvette* corvette::createFrom(Ship* source)
{
    corvette* corv = new corvette('C', "Corvette", source->getTeamSymbol());
    corv->setShipPosition(source->getShipPositionX(), source->getShipPositionY());
    corv->setLives(source->getLives());
    corv->setType("Corvette");
    corv->setSymbol('C');
    return corv;
}