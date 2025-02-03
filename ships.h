#ifndef SHIP_H
#define SHIP_H

#include "helpers.h"

// add a destroyed function that will be called when the ship is destroyed
// Abstract base object for Ships

class Battlefield;
class Ship
{
private:
    int lives = 3;
    int shipPositionX = 0;
    int shipPositionY = 0;
    int projectilePosX = 0;
    int projectilePosY = 0;
    std::string type = "Ship";
    char teamSymbol = '0';
    char shipSymbol = '-';
    struct intelligence
    {
        char neighbourCells[3][3] = {{'0'}};
    };
    intelligence intel;

public:
    bool wasOnIsland = false; // Store last known position of island
    virtual bool getWasOnIsland() const;
   
    bool isInDeathQueue = false;

    Ship(char shipSymbol, std::string type, char teamSymbol);

    Ship(const Ship &other);

    Ship &operator=(const Ship &other);

    Ship(Ship &&other) noexcept;

    Ship &operator=(Ship &&other) noexcept;

    virtual void actions(char **gr, int rows, int cols, Battlefield &battlefield) = 0;

    void reduceLives(Battlefield &battlefield);
    // getters
    char getSymbol() const;

    int getShipPositionX() const;

    int getShipPositionY() const;

    int getProjPositionX() const;

    int getProjPositionY() const;
    void getNeighbourCells() const;
    int getLives() const;
    char getTeamSymbol() const;
    std::string getType() const;


    // setters
    void setShipPosition(int x, int y);
    void setProjectilePos(int x, int y);
    void setNeighbourCells(char neighbourCell, int i, int j);
    void setType(std::string type);
    void setLives(int lives);
    void setSymbol(char c) ;
    bool isDestroyed() const;
    virtual ~Ship() = default;
};

// cant move to a location that contains another battleship
class MovingShip : virtual public Ship
{
private:
public:
    virtual void move(char **gr, int rows, int cols, Battlefield &battlefield) = 0;
};

class ShootingShip : virtual public Ship
{
private:
    Ship *target;

public:
    virtual void shoot(char **gr, int rows, int cols, Battlefield &battlefield) = 0;
};

class SeeingRobot : virtual public Ship
{
private:
    Ship *acquiredTarget;

public:
    virtual void look(char **gr, int rows, int cols) = 0;
};

class RamShip : virtual public Ship
{
public:
    virtual void ram(char **gr, int rows, int cols, Battlefield &battlefield) = 0;
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
class BattleShip : public MovingShip, public ShootingShip, public SeeingRobot
{
private:
    int SHIPSDESTROYED = 0;
    list<char> destroyedShips;

public:
    BattleShip(char shipSymbol, std::string type, char teamSymbol);

    virtual void move(char **gr, int rows, int cols, Battlefield &battlefield) override;

    virtual void look(char **gr, int rows, int cols) override;

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

class cruiser : public RamShip
{
private:
    int SHIPSDESTROYED = 0;
    list<char> destroyedShips;

public:
    cruiser(char shipSymbol, std::string type, char teamSymbol);
    void ram(char **gr, int rows, int cols, Battlefield &battlefield) override;
    void actions(char **gr, int rows, int cols, Battlefield &battlefield) override;
};

/*
--------------------------------------------------------------------
 Destroyer --:
 it can move it can shoot it can ram it can look
 if kill = 3, upgrades to supership
 --------------------------------------------------------------------
*/
class Destroyer : public BattleShip, public cruiser
{
private:
    int SHIPSDESTROYED = 0;
    list<char> destroyedShips;

public:
    Destroyer(char shipSymbol, std::string type, char teamSymbol);

    static Destroyer* createFrom(Ship* source);

    void actions(char **gr, int rows, int cols, Battlefield &battlefield) override;
};
/*
--------------------------------------------------------------------
 Frigate --:
 it can shoot at neighbouring cells 1x1
 and when it shoots it clock wise direction
 if kill = 3, upgrades to corvette
--------------------------------------------------------------------
*/
class Frigate : public ShootingShip
{
private:
    int SHIPSDESTROYED = 0;
    list<char> destroyedShips;
    int clock = 0; 
public:
    Frigate(char shipSymbol, std::string type, char teamSymbol);

    void shoot(char **gr, int rows, int cols, Battlefield &battlefield) override;

    void actions(char **gr, int rows, int cols, Battlefield &battlefield) override;
    
};

/*
--------------------------------------------------------------------
Corvette --:
cant move, shoot at random neighbour cells
--------------------------------------------------------------------
*/
class corvette : public ShootingShip
{
private:
    int SHIPSDESTROYED = 0;
    int clock = 0; 
    list<char> destroyedShips;
public:
    corvette(char shipSymbol, std::string type, char teamSymbol);

    void shoot(char **gr, int rows, int cols, Battlefield &battlefield) override;

    static corvette* createFrom(Ship* source);

    void actions(char **gr, int rows, int cols, Battlefield &battlefield) override;
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
    list<char> destroyedShips;
public:
    Amphibious(char shipSymbol, std::string type, char teamSymbol);

    void move(char **gr, int rows, int cols, Battlefield &battlefield) override;

    void shoot(char **gr, int rows, int cols, Battlefield &battlefield) override;
    void actions(char **gr, int rows, int cols, Battlefield &battlefield)override; 
   
};
/*
--------------------------------------------------------------------
SuperShip --:
it can do everything
 it move like a cruiser, killing everything in its way
shoots randomly at 3 locations in the same turn
--------------------------------------------------------------------
*/
class SuperShip : public cruiser, public ShootingShip
{
private:
    int SHIPSDESTROYED = 0;
    list<char> destroyedShips;
public:
    SuperShip(char shipSymbol, std::string type, char teamSymbol);

    void shoot(char **gr, int rows, int cols, Battlefield &battlefield) override;

    void actions(char **gr, int rows, int cols, Battlefield &battlefield)override; 

    static SuperShip* createFrom(Ship* source);
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

#endif