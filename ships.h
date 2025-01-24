#pragma once
#include "helpers.h"

// add a destroyed function that will be called when the ship is destroyed
// Abstract base object for Ships


class Battlefield;
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
    char teamSymbol = '0';
    struct intelligence
    {
        char neighbourCells[3][3] = {{'0'}};
    };
    intelligence intel;

public:
    Ship(char shipSymbol, std::string type, char teamSymbol);

    virtual void actions(char **gr, int rows, int cols, Battlefield &battlefield) = 0;
    virtual void move(char **gr, int rows, int cols) = 0;

    void reduceLives();
    // getters
    char getSymbol() const;

    int getShipPositionX() const;

    int getShipPositionY() const;

    int getProjPositionX() const;

    int getProjPositionY() const;
    void getNeighbourCells() const;
    int getLives() const;
    bool isDestroyed() const;

    std::string getType() const;

    // setters
    void setShipPosition(int x, int y);
    void setProjectilePos(int x, int y);
    void setEnemyShipPos(int x, int y);
    char getTeamSymbol() const;
    void setNeighbourCells(char neighbourCell, int i, int j);

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
    virtual void shoot(char **gr, int rows, int cols, Battlefield &battlefield) = 0;
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
    list <char> destroyedShips;
    bool canDestroy = false;

public:
    BattleShip(char shipSymbol, std::string type, char teamSymbol);

    void move(char **gr, int rows, int cols) override;

    void look(char **gr, int rows, int cols) override;

    void shoot(char **gr, int rows, int cols, Battlefield &battlefield) override;
    void actions(char **gr, int rows, int cols, Battlefield &battlefield) override;
    ~BattleShip();
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

class cruiser : public MovingShip, public RamShip, public SeeingrRobot
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
class Destroyer : public BattleShip
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
