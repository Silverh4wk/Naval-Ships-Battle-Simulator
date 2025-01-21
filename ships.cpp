#include <iostream>
#include <sstream>
#include <random>
#include "ships.h"
#include "Battlefield.h"
Ship::Ship(char shipSymbol, std::string type) : shipSymbol(shipSymbol),
                                                type(type)
{
}

void Ship::reduceLives()
{
    if (lives > 0)
    {
        lives--;
        std::cout << "Ship hit! Lives remaining: " << lives << "\n";
    }
    if (lives == 0)
    {
        std::cout << "Ship destroyed!\n";
    }
}
// getters
char Ship::getSymbol() const
{
    if (lives < 1)
    {
        return destroyedSymbol;
    }
    return shipSymbol;
}

int Ship::getShipPositionX() const { return shipPositionX; }

int Ship::getShipPositionY() const { return shipPositionY; }

int Ship::getProjPositionX() const { return projectilePosX; }

int Ship::getProjPositionY() const { return projectilePosY; }
void Ship::getNeighbourCells() const
{
    std::cout << "\nNeighbouring cells for ship : " << getSymbol() << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << intel.neighbourCells[i][j] << " ";
        }
        std::endl(std::cout);
    }
    std::endl(std::cout);
}

bool Ship::getlives() const { return lives < 1; }

std::string Ship::getType() const { return type; }

// setters
void Ship::setShipPosition(int x, int y)
{
    shipPositionX += x;
    shipPositionY += y;
}
void Ship::setProjectilePos(int x, int y)
{
    projectilePosX = shipPositionX + x;
    projectilePosY = shipPositionY + y;
}
void Ship::setEnemyShipPos(int x, int y)
{
    intel.enemyShipX = x;
    intel.enemyShipY = y;
}

void Ship::setNeighbourCells(char neighbourCell, int i, int j)
{
    // Map [-1, 1] to [0, 2]
    int rows = i + 1;
    int cols = j + 1;

    if (rows >= 0 && rows < 3 && cols >= 0 && cols < 3)
    {
        intel.neighbourCells[rows][cols] = neighbourCell;
    }
}

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

BattleShip::BattleShip(char shipSymbol, std::string type) : Ship(shipSymbol, type) {}

void BattleShip::move(char **gr, int rows, int cols)
{
    int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::string directionNames[4] = {"up", "right", "down", "left"};
    std::random_device r;
    std::default_random_engine r1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 3);
    int chance = uniform_dist(r1);
    int newX = 0;
    int newY = 0;
    // 1 in 4 chance to move in a random direction
    switch (chance)
    {
    case 0:
        newX = getShipPositionX() + directions[0][0];
        newY = getShipPositionY() + directions[0][1];
        break;
    case 1:
        newX = getShipPositionX() + directions[1][0];
        newY = getShipPositionY() + directions[1][1];
        break;
    case 2:
        newX = getShipPositionX() + directions[2][0];
        newY = getShipPositionY() + directions[2][1];
        break;
    case 3:
        newX = getShipPositionX() + directions[3][0];
        newY = getShipPositionY() + directions[3][1];
        break;
    }
    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && gr[newY][newX] == '0')
    {
        // Valid move found
        // clear current position
        // update position
        // update grid
        gr[getShipPositionY()][getShipPositionX()] = '0';
        setShipPosition(newX, newY);
        gr[newY][newX] = getSymbol();
        std::cout << "battleship " << getSymbol() << " moving " << directionNames[chance] << "\n";
        return;
    }
    else
    {
        std::cout << "battleship " << getSymbol() << " can't move " << directionNames[chance] << "\n";
    }
}

void BattleShip::look(char **gr, int rows, int cols)
{
    int nx = 0;
    int ny = 0;
    char cell;
    // look at 3x3 window and check for enemy ships/out of bounds
    std::cout << "\n"
              << getSymbol() << " is looking around\n";
    std::cout << "________________________________________\n";
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {

            nx = getShipPositionX() + j; // (Y,0) + neighbor cell position
            ny = getShipPositionY() + i; // (0,X) + neighbor cell position
            // if function to check if the cell is within the grid
            // if an enemy ship is detected, print the location of that ship
            // fix anomaly tomorrow- woo fixed- nvm still need to fix

            if (cell != '0' && cell != '1' && cell != this->getSymbol() && cell != '\0')
            {
                std::cout << "\nEnemy ship detected at (" << ny << ", " << nx << ")!\n";
                setEnemyShipPos(nx, ny);
            }
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows)
            {
                cell = gr[ny][nx];
                setNeighbourCells(cell, i, j);
            }
            else
            {
                setNeighbourCells('?', i, j);
            }
        }
        std::cout << "\n";
    }
}

void BattleShip::shoot(char **gr, int rows, int cols, Battlefield &battlefield)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> chanceX(0, cols - 1);
    std::uniform_int_distribution<int> chanceY(0, rows - 1);

    for (int i = 0; i < 2; ++i) 
    {
        int targetX = chanceX(gen);
        int targetY = chanceY(gen);
        std::cout << "target coordinates: (" << targetY << ", " << targetX << ")\n";
        // Check if the target is within the city block distance of 5
        // SO MANY ISSUES HERE FIX SOON, also need to understand the city block distance constraint
        std::cout << "city block distance: " << getShipPositionX << "-" << targetX << std::abs(getShipPositionX() - targetX) + std::abs(getShipPositionY() - targetY) << "\n";
        if (std::abs(getShipPositionX() - targetX) + std::abs(getShipPositionY() - targetY) <= 5)
        {
            char targetCell = gr[targetY][targetX];
            if (targetCell != '0' && targetCell != getSymbol()) // If it's an enemy ship
            {
                std::cout << "Shooting at enemy ship at (" << targetY << ", " << targetX << ")\n";
                Ship *enemyShip = battlefield.getShipAt(targetX, targetY); // Get the target ship
                std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "lives = " << enemyShip->getlives() << "\n";
                if (enemyShip)
                {
                    enemyShip->reduceLives();  // Deal damage to the target ship
                    if (enemyShip->getlives()) // If the ship is destroyed
                    {
                        SHIPSDESTROYED++;
                        std::cout << "Ship destroyed! Total ships destroyed: " << SHIPSDESTROYED << "\n";
                        if (SHIPSDESTROYED >= 4)
                        {
                            canDestroy = true; // Upgrade to destroyer
                            std::cout << "Battleship upgraded to Destroyer!\n";
                        }
                    }
                }
            }
        }
        else
        {
            std::cout << "Target out of range due to city block distance constraint.\n";
        }
    }
}
void BattleShip::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    look(gr, rows, cols);
    move(gr, rows, cols);
    shoot(gr, rows, cols, battlefield);
}
BattleShip::~BattleShip() { std::cout << "destroyed battleship\n"; }
