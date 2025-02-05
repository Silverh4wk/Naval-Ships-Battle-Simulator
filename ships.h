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
#ifndef SHIP_H
#define SHIP_H
#include <string>
#include "helpers.h"  
#include "Game.h"

// Forward declaration for Battlefield
class Battlefield;

// Abstract base object for Ships
class Ship
{
protected:
    int lives = 3;
    int shipPositionX = 0;
    int shipPositionY = 0;
    std::string type = "Ship";
    char teamSymbol = '0';
    char shipSymbol = '+';
   
public:
    // bool wasOnIsland = false; // Store last known position of island
    // virtual bool getWasOnIsland() const;

    bool isInDeathQueue = false;

    Ship(char shipSymbol, std::string type, char teamSymbol);

    Ship(const Ship& other);

    Ship& operator=(const Ship& other);
    Ship(Ship&& other) noexcept;
    Ship& operator=(Ship&& other) noexcept;

    // Pure virtual function that must be implemented by concrete ship types.
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) = 0;
    void reduceLives(Battlefield& battlefield);

    // getters
    char getSymbol() const;

    int getShipPositionX() const;

    int getShipPositionY() const;


    int getLives() const;
    char getTeamSymbol() const;
    std::string getType() const;


    // setters
    void setShipPosition(int x, int y);
    void setType(std::string type);
    void setLives(int lives);
    void setSymbol(char c);
    bool isDestroyed() const;
    //
    virtual ~Ship() = default;
};

// cant move to a location that contains another battleship
// Interface for ships that can move
class MovingShip : virtual public Ship
{
public:
    MovingShip(char shipSymbol, std::string type, char teamSymbol)
        : Ship(shipSymbol, type, teamSymbol) {
    }
    virtual void move(char** gr, int rows, int cols, Battlefield& battlefield) = 0;
};

// Interface for ships that can shoot
class ShootingShip : virtual public Ship
{
public:
    ShootingShip(char shipSymbol, std::string type, char teamSymbol)
        : Ship(shipSymbol, type, teamSymbol) {
    }
    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) = 0;
};

// Interface for ships that can see
class SeeingRobot : virtual public Ship
{
public:
    SeeingRobot(char shipSymbol, std::string type, char teamSymbol)
        : Ship(shipSymbol, type, teamSymbol) {
    }
    virtual void look(char** gr, int rows, int cols) = 0;
};

// Interface for ships that can ram
class RamShip : virtual public Ship
{
public:
    RamShip(char shipSymbol, std::string type, char teamSymbol)
        : Ship(shipSymbol, type, teamSymbol) {
    }
    virtual void ram(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) = 0;
};

#endif  
