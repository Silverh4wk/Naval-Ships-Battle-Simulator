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
#include <random>
#include "Destroyer.h"
#include "Battlefield.h"
#include <iostream>
#include "BattleShip.h"
#include "Macros.h"

/*
--------------------------------------------------------------------

 battleship --:
 it can shoot, it can move, it can see
 looks at its current pos then decide to move
 move once then shoot twice at random positions, x+y is 5 blocks
 cant move to a location that contain another Ship
 if shoot hit = 4 ---> upgrade to destroyer

--------------------------------------------------------------------
*/

BattleShip::BattleShip(char shipSymbol, std::string type, char teamSymbol)
    : Ship(shipSymbol, type, teamSymbol),
    MovingShip(shipSymbol, type, teamSymbol),
    ShootingShip(shipSymbol, type, teamSymbol),
    SeeingRobot(shipSymbol, type, teamSymbol)
{
}

BattleShip::BattleShip(BattleShip&& other) noexcept
    : Ship(other.getSymbol(), other.getType(), other.getTeamSymbol()),
    MovingShip(std::move(other)),
    ShootingShip(std::move(other)),
    SeeingRobot(std::move(other)) 
{

}

BattleShip& BattleShip::operator=(BattleShip&& other) noexcept {
    if (this != &other) {
        Ship::operator=(std::move(other));
        MovingShip::operator=(std::move(other));
        ShootingShip::operator=(std::move(other));
        SeeingRobot::operator=(std::move(other));
    }
    return *this;
}



BattleShip::~BattleShip() {
    std::cout << getType() << " was deleted\n";
}

void BattleShip::move(char** gr, int rows, int cols, Battlefield& battlefield)
{
    std::cout << "\n" << getSymbol() << " is deciding where to Move\n";
    std::cout << "________________________________________\n";

    // Direction vectors: up, right, down, left
    int directions[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
    std::string directionNames[4] = { "up", "right", "down", "left" };

    RANDOM_DEVICE
        std::uniform_int_distribution<int> uniform_dist(0, 3);
    int chance = uniform_dist(r1);

    // Calculate new coordinates using the random direction
    int newX = getShipPositionX() + directions[chance][0];
    int newY = getShipPositionY() + directions[chance][1];

    // 1 in 4 chance to move in a random direction
    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && gr[newY][newX] == '0')
    {
        // Valid move found
        // clear current position
        // update position
        // update grid
        int oldX = getShipPositionX();
        int oldY = getShipPositionY();
        gr[oldY][oldX] = battlefield.getTerrainAt(oldY, oldX);
        setShipPosition(newX, newY);
        gr[newY][newX] = getSymbol();
        std::cout << getType() << " "<< getSymbol() << " moving " << directionNames[chance] << "\n";
        return;
    }
    else
    {
        std::cout << getSymbol() << " can't move " << directionNames[chance] << "\n";
    }
}

void BattleShip::look(char** gr, int rows, int cols)
{
    std::cout << "\n" << getSymbol() << " is looking around\n";
    std::cout << "________________________________________\n";

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            int nx = getShipPositionX() + j;
            int ny = getShipPositionY() + i;
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows)
            {
                char cell = gr[ny][nx];
                // Check if the cell holds an enemy ship and is not a blank terrain
                if (cell != '0' && cell != '1' &&
                    cell != getSymbol() && cell != '\0')
                {
                    std::cout << "Ship detected at ("
                        << ny << ", " << nx << ")!\n";
                }
            }
            else
            {
                std::cout << "Cell (" << ny << ", " << nx
                    << ") is out-of-bounds.\n";
            }
        }
        std::cout << "\n";
    }
}

void BattleShip::shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    std::cout << "\n" << getSymbol() << " is deciding where to Shoot\n";
    std::cout << "________________________________________\n";
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
        std::cout << "city block distance: " << std::abs(getShipPositionY() - targetY)
            << " + " << std::abs(getShipPositionX() - targetX) << "\n";
        std::cout << "city block distance: "
            << std::abs(getShipPositionX() - targetX) + std::abs(getShipPositionY() - targetY) << "\n";

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
                shipsDestroyed++;  // Record the hit
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


void BattleShip::actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    if (!isInDeathQueue )
    {
        SHIPS_INFO;
        look(gr, rows, cols);
        move(gr, rows, cols, battlefield);
        shoot(gr, rows, cols, battlefield, gameManager);
        if (shipsDestroyed >= 4)
        {
            std::cout  <<getType()<< " upgraded to Destroyer!\n";
            gr[getShipPositionY()][getShipPositionX()] = '0';
            Destroyer* newDestroyer = new Destroyer(std::move(*this));
            battlefield.replaceShip(this, newDestroyer, gameManager);
            return; // Exit to prevent further use of the replaced ship or big crash happens
        }
    }
    else
    {
        std::cout << getSymbol() << " is waiting to respawn\n";
    }
}