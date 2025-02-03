#include <iostream>
#include <sstream>
#include <random>
#include "ships.h"
#include "Battlefield.h"

#define RANDOM_DEVICE     \
    std::random_device r; \
    std::default_random_engine r1(r());
#define SHIPS_INFO                                                             \
    std::cout << "________________________________________\n"                  \
              << getType() << " status: \n"                                    \
                              "Symbol: "                                       \
              << getSymbol() << "\n"                                           \
                                "Position: ("                                  \
              << getShipPositionY() << ", " << getShipPositionX() << ")\n"     \
                                                                     "Lives: " \
              << getLives() << "\n"                                            \
                               "Type: "                                        \
              << getType() << "\n"                                             \
                              "ships destroyed: "                              \
              << SHIPSDESTROYED << "| ";                                       \
    destroyedShips.forwardPrint();                                             \
    std::cout << "________________________________________\n";

Ship::Ship(char shipSymbol, std::string type, char teamSymbol) : shipSymbol(shipSymbol),
                                                                 type(type), teamSymbol(teamSymbol) {}
Ship &Ship::operator=(const Ship &other)
{
    if (this != &other)
    {
        lives = other.lives;
        shipSymbol = other.shipSymbol;
        shipPositionX = other.shipPositionX;
        shipPositionY = other.shipPositionY;
        projectilePosX = other.projectilePosX;
        projectilePosY = other.projectilePosY;
        type = other.type;
        teamSymbol = other.teamSymbol;
        intel = other.intel;
        isInDeathQueue = other.isInDeathQueue;
    }
    return *this;
}

Ship::Ship(const Ship &other)
    : lives(other.lives), shipSymbol(other.shipSymbol),
      shipPositionX(other.shipPositionX),
      shipPositionY(other.shipPositionY),
      projectilePosX(other.projectilePosX),
      projectilePosY(other.projectilePosY),
      type(other.type), teamSymbol(other.teamSymbol),
      intel(other.intel), isInDeathQueue(other.isInDeathQueue) {}
Ship &Ship::operator=(Ship &&other) noexcept
{
    if (this != &other)
    {
        // Transfer resources
        lives = other.lives;
        shipPositionX = other.shipPositionX;
        shipPositionY = other.shipPositionY;
        projectilePosX = other.projectilePosX;
        projectilePosY = other.projectilePosY;
        type = std::move(other.type);
        shipSymbol = other.shipSymbol;
        teamSymbol = other.teamSymbol;
        intel = other.intel;
        isInDeathQueue = other.isInDeathQueue;

        // Reset the source
        other.lives = 0;
        other.shipPositionX = 0;
        other.shipPositionY = 0;
        other.projectilePosX = 0;
        other.projectilePosY = 0;
        other.type.clear();
        other.shipSymbol = '-';
        other.teamSymbol = '\0';
        other.isInDeathQueue = false;
    }
    return *this;
}

Ship::Ship(Ship &&other) noexcept
    : lives(other.lives),
      shipPositionX(other.shipPositionX),
      shipPositionY(other.shipPositionY),
      projectilePosX(other.projectilePosX),
      projectilePosY(other.projectilePosY),
      type(std::move(other.type)),
      shipSymbol(other.shipSymbol),
      teamSymbol(other.teamSymbol),
      intel(other.intel),
      isInDeathQueue(other.isInDeathQueue)
{
    // Reset the source
    other.lives = 0;
    other.shipPositionX = 0;
    other.shipPositionY = 0;
    other.projectilePosX = 0;
    other.projectilePosY = 0;
    other.type.clear();
    other.shipSymbol = '-';
    other.teamSymbol = '\0';
    other.isInDeathQueue = false;
}
void Ship::reduceLives(Battlefield &battlefield)
{
    if (!isDestroyed())
    {
        lives--;
        std::cout << "Ship hit! Lives remaining: " << lives << "\n";
        if (isDestroyed())
        {
            std::cout << "Ship destroyed and added to graveyard!\n";
        }
        else if (!isInDeathQueue)
        {
            battlefield.shipGraveYard.push_back(this);
            isInDeathQueue = true;
            std::cout << "Ship added to graveyard for repairs...\n";
        }
    }
}
// getters
char Ship::getSymbol() const
{
    return shipSymbol;
}

bool Ship::getWasOnIsland() const
{
    return wasOnIsland ;
}
char Ship::getTeamSymbol() const { return teamSymbol; }
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

bool Ship::isDestroyed() const
{
    return lives < 1;
}

int Ship::getLives() const { return lives; }

std::string Ship::getType() const { return type; }

// setters
void Ship::setShipPosition(int x, int y)
{
    shipPositionX = x;
    shipPositionY = y;
}
void Ship::setProjectilePos(int x, int y)
{
    projectilePosX = shipPositionX + x;
    projectilePosY = shipPositionY + y;
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

void Ship::setType(std::string type) { type = type; }
void Ship::setLives(int lives) { lives = lives; }
void Ship::setSymbol(char c) {shipSymbol = c;} 
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

BattleShip::BattleShip(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol) {}

void BattleShip::move(char **gr, int rows, int cols,Battlefield &battlefield)
{
    int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::string directionNames[4] = {"up", "right", "down", "left"};
    RANDOM_DEVICE
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
                std::cout << "\nEnemy ship detected at (" << ny << ", " << nx - 1 << ")!\n";
            }
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows)
            {
                cell = gr[ny][nx];
                // setNeighbourCells(cell, i, j);
            }
            // else
            // {
            //     setNeighbourCells('?', i, j);
            // }
        }
        std::cout << "\n";
    }
}

void BattleShip::shoot(char **gr, int rows, int cols, Battlefield &battlefield)
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
        // Check if the target is within the city block distance of 5
        // SO MANY ISSUES HERE FIX SOON, also need to understand the city block distance constraint
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
                    gr[targetY][targetX] = '0'; // Clear the grid
                    std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";
                    if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                    {
                        destroyedShips.push_back(enemyShip->getSymbol());
                        std::cout << enemyShip->getSymbol() << " destroyed\n";
                        SHIPSDESTROYED++;
                        enemyShip = nullptr;
                        std::cout << "Ship destroyed! Total ships destroyed: " << SHIPSDESTROYED << "\n";

                        // if (SHIPSDESTROYED >= 4)
                        // {
                        //     gr[this->getShipPositionY()][this->getShipPositionX()] = '0';
                        //     std::cout << "Battleship upgraded to Destroyer!\n";
                        //     Destroyer *newDestroyer = Destroyer::createFrom(this);
                        //     battlefield.replaceShip(this, newDestroyer);
                        //     return; // so program dont use the deleted pointer or big crash happen
                        // }
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

void BattleShip::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        look(gr, rows, cols);
        move(gr, rows, cols, battlefield);
        shoot(gr, rows, cols, battlefield);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}
BattleShip::~BattleShip() { std::cout << "destroyed battleship\n"; }

/*
--------------------------------------------------------------------
 Cruiser --:
 it can look it can move and it can ram
 will not shoot at all and will terminate ships at its path
 in each turn it looks at 3x3 window, it will move to one of them
 if the cruiser kills 3 of them, cruiser ---> upgrade to destroyer

 --------------------------------------------------------------------
*/

cruiser::cruiser(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol) {}

void cruiser::ram(char **gr, int rows, int cols, Battlefield &battlefield)
{
    int nx = 0;
    int ny = 0;
    char cell = '0';
    bool foundEnemy = false;

    std::cout << "\n"
              << getSymbol() << " is deciding \n";
    std::cout << "________________________________________\n";

    // Check neighboring cells for enemy ships
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            nx = getShipPositionX() + j; // (Y,0) + neighbor cell position
            ny = getShipPositionY() + i; // (0,X) + neighbor cell position
            // Check if within the grid
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows)
            {
                cell = gr[ny][nx];

                if (cell != '0' && cell != '1' && cell != this->getSymbol())
                {
                    std::cout << "\nChecking ship at (" << ny << ", " << nx << ")!\n";
                    Ship *enemyShip = battlefield.getShipAt(nx, ny);
                    if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol())
                    {
                        enemyShip->reduceLives(battlefield);
                        gr[this->getShipPositionY()][this->getShipPositionX()] = '0'; // Set current ship position to 0
                        gr[ny][nx] = this->getSymbol();                               // Move cruiser to new position
                        this->setShipPosition(nx, ny);
                        std::cout << "Enemy ship symbol: " << enemyShip->getSymbol()
                                  << " is dead? = " << enemyShip->isDestroyed() << "\n";

                        if (enemyShip->isDestroyed())
                        {
                            destroyedShips.push_back(enemyShip->getSymbol());
                            std::cout << enemyShip->getSymbol() << " destroyed\n";
                            enemyShip = nullptr;
                            SHIPSDESTROYED++;
                            std::cout << "Ship destroyed! Total ships destroyed: "
                                      << SHIPSDESTROYED << "\n";

                            // if (SHIPSDESTROYED >= 3)
                            // {
                            //     std::cout << "Cruiser upgraded to Destroyer!\n";
                            //     Destroyer *newDestroyer = Destroyer::createFrom(this);
                            //     battlefield.replaceShip(this, newDestroyer);
                            //     return; // so program dont use the deleted pointer or big crash happen
                            // }
                        }
                        foundEnemy = true;
                        break;
                    }
                }
            }
        }
    }

    if (!foundEnemy)
    {
        RANDOM_DEVICE;
        std::uniform_int_distribution<int> uniform_dist(-1, 1); // 3x3 distance will ofc skip the current ship location

        // infinite loop that will check if the new position is not out of bound or if is valid
        do
        {
            ny = this->getShipPositionY() + uniform_dist(r1);
            nx = this->getShipPositionX() + uniform_dist(r1);

            // Check if the new position is within bounds
            if (ny >= 0 && ny < rows && nx >= 0 && nx < cols)
            {
                if (gr[ny][nx] == '0')
                {
                    gr[this->getShipPositionY()][this->getShipPositionX()] = '0';
                    gr[ny][nx] = this->getSymbol();
                    this->setShipPosition(nx, ny);
                    std::cout << "No enemy found. Moved to random position (" << ny << ", " << nx << ").\n";
                    break;
                }
            }
        } while (true);
    }
}

void cruiser::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        std::cout << " is ramming now \n";
        ram(gr, rows, cols, battlefield);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}

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
      cruiser(shipSymbol, type, teamSymbol) {}

// factory function cuz i didnt know how to properly use movesemantics and im tired for now
Destroyer *Destroyer::createFrom(Ship *source)
{
    Destroyer *dest = new Destroyer('D', "Destroyer", source->getTeamSymbol());
    dest->setShipPosition(source->getShipPositionX(), source->getShipPositionY());
    dest->setLives(source->getLives());
    dest->setType("Destroyer");
    dest->setSymbol('$') ;
    return dest;
}

void Destroyer::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        std::cout << " is ramming now \n";
        ram(gr, rows, cols, battlefield);

        std::cout << " is looking now \n";
        look(gr, rows, cols);
        std::cout << " is moving now \n";
        move(gr, rows, cols,battlefield);
        std::cout << " is shooting now \n";
        shoot(gr, rows, cols, battlefield);
        // if (SHIPSDESTROYED >= 3)
        // {
        //     gr[this->getShipPositionY()][this->getShipPositionX()] = '0';
        //     std::cout << "Destroyer upgrading to SuperShip!\n";
        //     SuperShip *newsupership = SuperShip::createFrom(this);
        //     battlefield.replaceShip(this, newsupership);
        //     return; // so program dont use the deleted pointer or big crash happen
        // }
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}

Frigate::Frigate(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol) {}

void Frigate::shoot(char **gr, int rows, int cols, Battlefield &battlefield)
{
    int shipX = getShipPositionX();
    int shipY = getShipPositionY();
    
    // Clockwise movement order
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

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
                Ship *enemyShip = battlefield.getShipAt(targetX, targetY);
                
                if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol())
                {
                    std::cout << "Shooting at enemy ship at (" << targetY << ", " << targetX << ")\n";
                    enemyShip->reduceLives(battlefield);
                    gr[targetY][targetX] = battlefield.getTerrainAt(targetY,targetX); // Clear the grid
                    std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";
                
                    if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                    {
                        SHIPSDESTROYED++;
                        destroyedShips.push_back(enemyShip->getSymbol());
                        std::cout << enemyShip->getSymbol() << " destroyed\n";
                        enemyShip = nullptr;
                        std::cout << "Ship destroyed! Total ships destroyed: " << SHIPSDESTROYED << "\n";
                    }
                    // if (SHIPSDESTROYED >= 3)
                    // {
                    //     gr[this->getShipPositionY()][this->getShipPositionX()] = '0';
                    //     std::cout << "Frigate upgraded to Corvette!\n";
                    //     corvette *newcorvette = corvette::createFrom(this);
                    //     battlefield.replaceShip(this, newcorvette);
                    //     return; // so program dont use the deleted pointer or big crash happen
                    // }
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



void Frigate::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        shoot(gr, rows, cols, battlefield);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}


corvette::corvette(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol) {}

void corvette::shoot(char **gr, int rows, int cols, Battlefield &battlefield)
{
    int directions[8][2] = {{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
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
            Ship *enemyShip = battlefield.getShipAt(targetX, targetY);
            if (enemyShip != nullptr && enemyShip->getTeamSymbol() != this->getTeamSymbol())
            {
                
                std::cout << "Shooting at enemy ship at (" << targetY << ", " << targetX << ")\n";
                enemyShip->reduceLives(battlefield);
                gr[targetY][targetX] = battlefield.getTerrainAt(targetY,targetX); // Clear the grid
                std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";
                if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                {
                    SHIPSDESTROYED++;
                    destroyedShips.push_back(enemyShip->getSymbol());
                    std::cout << enemyShip->getSymbol() << " destroyed\n";
                    enemyShip = nullptr; // set the dead ship to null
                    std::cout << "Ship destroyed! Total ships destroyed: " << SHIPSDESTROYED << "\n";
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


void corvette::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        shoot(gr, rows, cols, battlefield);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}

corvette *corvette::createFrom(Ship *source)
{
    corvette *corv = new corvette('C', "Corvette", source->getTeamSymbol());
    corv->setShipPosition(source->getShipPositionX(), source->getShipPositionY());
    corv->setLives(source->getLives());
    corv->setType("Corvette");
    corv->setSymbol('C') ;
    return corv;
}




Amphibious::Amphibious(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol),
      BattleShip(shipSymbol, type, teamSymbol){}

void Amphibious::move(char **gr, int rows, int cols, Battlefield &battlefield)
{
    int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::string directionNames[4] = {"up", "right", "down", "left"};
    RANDOM_DEVICE
    std::uniform_int_distribution<int> uniform_dist(0, 3);
    int chance = uniform_dist(r1);
    int newX = 0;
    int newY = 0;
    // 1 in 4 chance to move in a random direction
    
    newX = getShipPositionX() + directions[chance][0];
    newY = getShipPositionY() + directions[chance][1];

    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && (gr[newY][newX] == '0' || gr[newY][newX] == '1'))
    {

        setShipPosition(newX, newY);
        gr[newY][newX] = getSymbol();
        gr[getShipPositionY()][getShipPositionX()] = battlefield.getTerrainAt(getShipPositionY(),getShipPositionX()); // Clear the old position
   
        std::cout << "Amphibious " << getSymbol() << " moving " << directionNames[chance] << "\n";
    }
    else
    {
        std::cout << "Amphibious " << getSymbol() << " can't move " << directionNames[chance] << "\n";
    }
}

void Amphibious::shoot(char **gr, int rows, int cols, Battlefield &battlefield)
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
        // Check if the target is within the city block distance of 5
        // SO MANY ISSUES HERE FIX SOON, also need to understand the city block distance constraint
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
                    gr[targetY][targetX] = battlefield.getTerrainAt(targetY,targetX) ; // Clear the grid
                    std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";  
                    if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                    {
                        SHIPSDESTROYED++;
                        destroyedShips.push_back(enemyShip->getSymbol());
                        std::cout << enemyShip->getSymbol() << " destroyed\n";
                        enemyShip = nullptr; // set the dead ship to null
                        std::cout << "Ship destroyed! Total ships destroyed: " << SHIPSDESTROYED << "\n";
                    }
                    // if (SHIPSDESTROYED >= 4)
                    // {
                    //     gr[this->getShipPositionY()][this->getShipPositionX()] = '0';
                    //     std::cout << "Amphibious upgraded to SuperShip!\n";
                    //     SuperShip *newsupership = SuperShip::createFrom(this);
                    //     battlefield.replaceShip(this, newsupership);
                    //     return; // so program dont use the deleted pointer or big crash happen
                    // }
                    
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

void Amphibious::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        look(gr, rows, cols);
        move(gr, rows, cols, battlefield);
        shoot(gr, rows, cols, battlefield);
    }
    else

        std::cout << getSymbol() << " is waiting to respawn\n";
}


SuperShip::SuperShip(char shipSymbol, std::string type, char teamSymbol) : Ship(shipSymbol, type, teamSymbol),
      cruiser(shipSymbol, type, teamSymbol){}

void SuperShip::shoot(char **gr, int rows, int cols, Battlefield &battlefield)
{
    for (int i = 0; i < 3; ++i)
    {
        int directions[8][2] = {{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
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
                    gr[targetY][targetX] = battlefield.getTerrainAt(targetY,targetX) ; // Clear the grid
                    std::cout << "Enemy ship symbol: " << enemyShip->getSymbol() << " " << "is dead? = " << enemyShip->isDestroyed() << "\n";
                    if (enemyShip->isDestroyed() == true) // If the ship is destroyed
                    {
                        SHIPSDESTROYED++;
                        destroyedShips.push_back(enemyShip->getSymbol());
                        std::cout << enemyShip->getSymbol() << " destroyed\n";
                        enemyShip = nullptr; // set the dead ship to null
                        std::cout << "Ship destroyed! Total ships destroyed: " << SHIPSDESTROYED << "\n";
                    }
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


void SuperShip::actions(char **gr, int rows, int cols, Battlefield &battlefield)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        std::cout << " is ramming now \n";
        ram(gr, rows, cols, battlefield);

        shoot(gr, rows, cols, battlefield);
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}    


SuperShip *SuperShip::createFrom(Ship *source)
{
    SuperShip *super = new SuperShip('S', "SuperShip", source->getTeamSymbol());
    super->setShipPosition(source->getShipPositionX(), source->getShipPositionY());
    super->setLives(source->getLives());
    super->setType("SuperShip");
    super->setSymbol('S') ;
    return super;
}








    
