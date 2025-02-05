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

#include <iostream>
#include <sstream>
#include <random>
#include "ships.h"
#include "Battlefield.h"


Ship::Ship(char shipSymbol, std::string type, char teamSymbol) : shipSymbol(shipSymbol),
type(type), teamSymbol(teamSymbol) {
}

Ship& Ship::operator=(const Ship& other)
{
    if (this != &other)
    {
        lives = other.lives;
        shipSymbol = other.shipSymbol;
        shipPositionX = other.shipPositionX;
        shipPositionY = other.shipPositionY;
        type = other.type;
        teamSymbol = other.teamSymbol;
        isInDeathQueue = other.isInDeathQueue;
    }
    return *this;
}

Ship::Ship(const Ship& other)
    : lives(other.lives), shipSymbol(other.shipSymbol),
    shipPositionX(other.shipPositionX),
    shipPositionY(other.shipPositionY),
    type(other.type), teamSymbol(other.teamSymbol),
     isInDeathQueue(other.isInDeathQueue) {
}

Ship::Ship(Ship&& other) noexcept
    : lives(other.lives),
    shipPositionX(other.shipPositionX),
    shipPositionY(other.shipPositionY),
    type(std::move(other.type)), 
    teamSymbol(other.teamSymbol),
    shipSymbol(other.shipSymbol)
{
    other.teamSymbol = '0';  
    other.shipSymbol = '+';
}

Ship& Ship::operator=(Ship&& other) noexcept {
    if (this != &other) {
        std::swap(lives, other.lives);
        std::swap(shipPositionX, other.shipPositionX);
        std::swap(shipPositionY, other.shipPositionY);
        std::swap(type, other.type); 
        std::swap(teamSymbol, other.teamSymbol);
        std::swap(shipSymbol, other.shipSymbol);
    }
    return *this;
}



void Ship::reduceLives(Battlefield& battlefield)
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

// bool Ship::getWasOnIsland() const
// {
//     return wasOnIsland ;
// }
char Ship::getTeamSymbol() const { return teamSymbol; }
int Ship::getShipPositionX() const { return shipPositionX; }

int Ship::getShipPositionY() const { return shipPositionY; }



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


void Ship::setType(std::string type) { this->type = type; }
void Ship::setLives(int lives) { this->lives = lives; }
void Ship::setSymbol(char c) { this->shipSymbol = c; }