/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
**********|**********|**********/
#include "Suicidal.h" 
#include <iostream>
#include "Battlefield.h"
#include "Macros.h"


Suicidal::Suicidal(char shipSymbol, std::string type, char teamSymbol) : 
Ship(shipSymbol, type, teamSymbol),
BlowShip(shipSymbol, type, teamSymbol){}


void Suicidal::BlowUp(char** gr, int rows, int cols, Battlefield& battlefield)
{
    int shipX = getShipPositionX();
    int shipY = getShipPositionY();
    int square = 0;
    // 3x3 area
    int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    for (int square = 0; square < 8; ++square)
    {
        int targetX = shipX + dx[square];
        int targetY = shipY + dy[square];

        // checks if its out of bounds 
        if (targetX >= 0 && targetX < cols && targetY >= 0 && targetY < rows)
        {
            char targetCell = gr[targetY][targetX];
            Ship* enemyShip = battlefield.getShipAt(targetX, targetY);
            //check if its the same team
            if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol()&& enemyShip->isInDeathQueue==false)
            {
                std::cout << "Bombing (" << targetY << ", " << targetX << ")\n";
                enemyShip->reduceLives(battlefield);
                gr[targetY][targetX] = battlefield.getTerrainAt(targetY,targetX); // Clear the grid
                std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";
                shipsDestroyed++;
                std::cout << "Ship destroyed! Total ships destroyed: " << shipsDestroyed << "\n";
            }
        
        }
        else
        {
            std::cout << "Bomb out of bounds!!(" << targetY << ", " << targetX << ").\n";
        }
    }
    std::cout << "Bombing (" << this->getShipPositionY() << ", " <<this->getShipPositionX() << ")\n";
    if (!this->isDestroyed()) 
    {
        this->reduceLives(battlefield); // reduce its own lives
        gr[this->getShipPositionY()][this->getShipPositionX()] = battlefield.getTerrainAt(this->getShipPositionY(),this->getShipPositionX()); // Clear the grid
        std::cout << "Suicidal ship symbol: " << this->getSymbol() << " " << "is dead? = " << this->isDestroyed() << "\n";
    }
    if (this->isDestroyed() == true) // If the ship is destroyed
    {
        shipsDestroyed++;
      //  destroyedShips.push_back(this->getSymbol());
        std::cout << this->getSymbol() << " destroyed\n";
        std::cout << "Ship destroyed! Total ships destroyed: " << shipsDestroyed << "\n";
    }
}

void Suicidal::actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        std::cout<<"A Bomb is dropped on a 3x3 area\n";
        BlowUp(gr, rows, cols, battlefield);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}