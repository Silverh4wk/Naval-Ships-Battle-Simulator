/**********|**********|**********|
Program: Amphibious.cpp / Amphibious.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
**********|**********|**********/
#include "Amphibious.h"
#include "Battlefield.h"
#include "SuperShip.h"
#include <iostream>
#include <random>
#include "Macros.h"

Amphibious::Amphibious(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol),
                                                                             BattleShip(shipSymbol, type, teamSymbol)
{
}

Amphibious &Amphibious::operator=(Amphibious &&other) noexcept
{
    if (this != &other)
    {

        Ship::operator=(std::move(other));
    }
    return *this;
}

void Amphibious::moveTo(Ship &target)
{
    if (auto *dest = dynamic_cast<Amphibious *>(&target))
    {
        *dest = std::move(*this);
    }
}

void Amphibious::move(char **gr, int rows, int cols, Battlefield &battlefield)
{
    int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::string directionNames[4] = {"up", "right", "down", "left"};
    RANDOM_DEVICE
    std::uniform_int_distribution<int> uniform_dist(0, 3);
    int chance = uniform_dist(r1);
    int newX = 0;
    int newY = 0;
    int oldX = getShipPositionX();
    int oldY = getShipPositionY();
    // 1 in 4 chance to move in a random direction

    newX = getShipPositionX() + directions[chance][0];
    newY = getShipPositionY() + directions[chance][1];

    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && (gr[newY][newX] == '0' || gr[newY][newX] == '1'))
    {

        setShipPosition(newX, newY);
        gr[newY][newX] = getSymbol();
        gr[oldY][oldX] = battlefield.getTerrainAt(oldY, oldX); // Clear the old position

        std::cout << "Amphibious " << getSymbol() << " moving " << directionNames[chance] << "\n";
    }
    else
    {
        std::cout << "Amphibious " << getSymbol() << " can't move " << directionNames[chance] << "\n";
    }
}

void Amphibious::shoot(char **gr, int rows, int cols, Battlefield &battlefield, game &gameManager)
{
    RANDOM_DEVICE
    std::uniform_int_distribution<int> chanceX(0, cols - 1);
    std::uniform_int_distribution<int> chanceY(0, rows - 1);
    // remember to return to  this after testing
    for (int i = 0; i < 2; ++i)
    {
        std::cout << "shooting # " << i + 1 << "\n";
        int targetX = chanceX(r1);
        int targetY = chanceY(r1);

        std::cout << "target coordinates: (" << targetY << ", " << targetX << ")\n";
        std::cout << "city block distance: " << getShipPositionX() << "-" << targetX << " " << std::abs(getShipPositionX() - targetX) + std::abs(getShipPositionY() - targetY) << "\n";
        if (std::abs(getShipPositionX() - targetX) + std::abs(getShipPositionY() - targetY) <= 5)
        {
            char targetCell = gr[targetY][targetX];
            std::cout << "target cell: " << targetCell << "\n";
            if (targetCell != '0' && targetCell != getSymbol()) // If it's a ship
            {
                Ship *enemyShip = battlefield.getShipAt(targetX, targetY); // Get the target ship
                // check if its not on the same team before shooting at it
                if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol())
                {
                    std::cout << "Shooting at enemy ship at (" << targetY << ", " << targetX << ")\n";
                    enemyShip->reduceLives(battlefield);
                    gr[targetY][targetX] = battlefield.getTerrainAt(targetY, targetX); // Clear the grid
                    std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";
                    if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                    {
                        shipsDestroyed++;
                       //gameEliminationTally.push_back(enemyShip->getSymbol());
                        std::cout << enemyShip->getSymbol() << " destroyed\n";
                        enemyShip = nullptr; // set the dead ship to null
                        std::cout << "Ship destroyed! Total ships destroyed: " << shipsDestroyed << "\n";
                    }
                }
            }
            else
                std::cout << "no enemy ship found to shoot at (" << targetY << ", " << targetX << ")\n";
        }
        else
        {
            std::cout << "Target out of range due to city block distance constraint.\n";
        }
    }
}

// bool Amphibious::getWasOnIsland() const { return wasOnIsland; }

void Amphibious::actions(char **gr, int rows, int cols, Battlefield &battlefield, game &gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        look(gr, rows, cols);
        move(gr, rows, cols, battlefield);
        shoot(gr, rows, cols, battlefield, gameManager);
        if (shipsDestroyed >= 4)
        {
            std::cout << getType() << " upgraded to SuperShip!\n";
            gr[getShipPositionY()][getShipPositionX()] = '0';
            SuperShip *newSuperShip = new SuperShip(std::move(*this));
            battlefield.replaceShip(this, newSuperShip, gameManager);
            return;
        }
    }
    else

        std::cout << getSymbol() << " is waiting to respawn\n";
}
