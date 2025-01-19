#include <iostream>
#include <sstream>
#include <random>

// Abstract base object for Ships
class Ship
{
private:
    int lives = 3;
    char shipSymbol = '-';
    char destroyedSymbol = 'X';
    int shipPositionX = 0;
    int shipPositionY = 0;
    int projectilePosX = 0;
    int projectilePosY = 0;
    std::string type = "Ship";
    struct intelligence
    {
        int enemyShipX = -1;
        int enemyShipY = -1;
        char neighbourCells[3][3] = {{'0'}};
    };
    intelligence intel;

public:
    Ship(char shipSymbol, std::string type) : shipSymbol(shipSymbol),
                                              type(type)
    {
    }

    virtual void actions(char **gr, int rows, int cols) = 0;
    virtual void move(char **gr, int rows, int cols) = 0;

    void reduceLives()
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
    char getSymbol() const
    {
        if (lives < 1)
        {
            return destroyedSymbol;
        }
        return shipSymbol;
    }

    int getShipPositionX() const { return shipPositionX; }

    int getShipPositionY() const { return shipPositionY; }

    int getProjPositionX() const { return projectilePosX; }

    int getProjPositionY() const { return projectilePosY; }
    void getNeighbourCells() const
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

    bool getlives() const { return lives < 1; }

    std::string getType() const { return type; }

    // setters
    void setShipPosition(int x, int y)
    {
        shipPositionX += x;
        shipPositionY += y;
    }
    void setProjectilePos(int x, int y)
    {
        projectilePosX = shipPositionX + x;
        projectilePosY = shipPositionY + y;
    }
    void setEnemyShipPos(int x, int y)
    {
        intel.enemyShipX = x;
        intel.enemyShipY = y;
    }

    void setNeighbourCells(char neighbourCell, int i, int j)
    {
        // Map [-1, 1] to [0, 2]
        int rows = i + 1;
        int cols = j + 1;

        if (rows >= 0 && rows < 3 && cols >= 0 && cols < 3)
        {
            intel.neighbourCells[rows][cols] = neighbourCell;
        }
    }

    virtual ~Ship() = default;
};

// cant move to a location that contains another battleship
class MovingShip : virtual public Ship
{
private:
public:
    virtual void move(char **gr, int rows, int cols) = 0;
};

class ShootignShip : virtual public Ship
{
private:
    Ship *target;

public:
    virtual void shoot() = 0;
};

class SeeingrRobot : virtual public Ship
{
private:
    Ship *acquiredTarget;

public:
    virtual void look(char **gr, int rows, int cols) = 0;
};

class RamShip : virtual public Ship
{
public:
    virtual void ram(int x, int y) = 0;
};

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
class BattleShip : public MovingShip, public ShootignShip, public SeeingrRobot
{
private:
    int SHIPSDESTROYED = 0;

public:
    BattleShip(char shipSymbol, std::string type) : Ship(shipSymbol, type) {};

    void move(char **gr, int rows, int cols) override
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

    void look(char **gr, int rows, int cols) override
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

    void shoot() override
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> chanceX(-1, 1);
        std::uniform_int_distribution<int> chanceY(-1, 1);
        int x = chanceX(gen);
        int y = chanceY(gen);
        setProjectilePos(x, y);
    }
    void actions(char **gr, int rows, int cols) override
    {
        look(gr, rows, cols);
        move(gr, rows, cols);
        shoot();
    }
    ~BattleShip() { std::cout << "destroyed battleship\n"; };
};

/*
--------------------------------------------------------------------
 Cruiser --:
 it can look it can move and it can ram
 will not shoot at all and will terminate ships at its path
 in each turn it looks at 3x3 window, it will move to one of them
 if the cruiser kills 3 of them, cruiser ---> upgrade to destroyer

 --------------------------------------------------------------------
*/

class cruiser : public MovingShip, public RamShip
{
private:
    int SHIPSDESTROYED;

public:
    cruiser(/* args */);
};

/*
--------------------------------------------------------------------
 Destroyer --:
 it can move it can shoot it can ram it can look
 if kill = 3, upgrades to supership
 --------------------------------------------------------------------
*/
class Destroyer : public MovingShip, public ShootignShip, public SeeingrRobot, public RamShip
{
private:
    /* data */
public:
    Destroyer(/* args */);
};
/*
--------------------------------------------------------------------
 Frigate --:
 it can shoot at neighbouring cells 1x1
 and when it shoots it clock wise direction
 if kill = 3, upgrades to corvette
--------------------------------------------------------------------
*/
class Frigate : public ShootignShip
{
private:
    /* data */
public:
    Frigate(/* args */);
};

/*
--------------------------------------------------------------------
Corvette --:
cant move, shoot at random neighbour cells
--------------------------------------------------------------------
*/
class corvette : public ShootignShip
{
private:
    /* data */
public:
    corvette(/* args */);
};

/*
--------------------------------------------------------------------
Amphibious --:
land and water
battleship behaviour
 if kill =4, upgrades to SUPERSHIP
 -------------------------------------------------------------------
*/
class Amphibious : public BattleShip
{
private:
    int SHIPSDESTROYED = 0;

public:
    Amphibious(/* args */);
};
/*
--------------------------------------------------------------------
SuperShip --:
it can do everything
 it move like a cruiser, killing everything in its way
shoots randomly at 3 locations in the same turn
--------------------------------------------------------------------
*/
class SuperShip
{
private:
    /* data */
public:
    SuperShip(/* args */);
    ~SuperShip();
};

// extra marks
// Implementation of additional ship classes (have to be fundamentally
// different than the one provided)
class prototype
{
private:
    /* data */
public:
    prototype(/* args */);
    ~prototype();
};

/// blow  a 3x3 area and anything in that area will get cleared even islands
class Suicidal
{
private:
    /* data */
public:
    Suicidal(/* args */);
    ~Suicidal();
};

