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
#include "Ships.h"
#include "Destroyer.h"
#include "SuperShip.h" 
#include "Cruiser.h"
#include "BattleShip.h"
#include "Battlefield.h"
#include "Macros.h"

// REMINDER TO NOT TOUCH THIS FILE AGAIN EVER
/*
--------------------------------------------------------------------
 Destroyer --:
 it can move it can shoot it can ram it can look
 if kill = 3, upgrades to supership
 functions and how they operate:
 
 Look: inherited the looking functionality from BattleShip
 Move: inherited the movement functionality from BattleShip
 Shoot: inherited the shooting functionality from BattleShip
 ram : inherited the ramming functionality from Cruiser 

 it upgrades to SuperShip if it kills 3 or more

 --------------------------------------------------------------------
*/

Destroyer::Destroyer(char shipSymbol, std::string type, char teamSymbol)
    : Ship(shipSymbol, type, teamSymbol),
    BattleShip(shipSymbol, type, teamSymbol),
    Cruiser(shipSymbol, type, teamSymbol)
{

}
    Destroyer::~Destroyer() {
    std::cout <<  "Destroyer was deleted\n";
}
Destroyer::Destroyer(Destroyer&& other) noexcept
    : Ship(other.getSymbol(), other.getType(), other.getTeamSymbol()),
    BattleShip(std::move(other)),
    Cruiser(std::move(other)) 
{

}

Destroyer& Destroyer::operator=(Destroyer&& other) noexcept {
    if (this != &other) {
        Ship::operator=(std::move(other));
        BattleShip::operator=(std::move(other));
        Cruiser::operator=(std::move(other));
    }
    return *this;
}


// Conversion from BattleShip
Destroyer::Destroyer(BattleShip&& base) noexcept
        : Ship(base.getSymbol(), "Destroyer", base.getTeamSymbol()),  
        BattleShip(base.getSymbol(), "Destroyer", base.getTeamSymbol()),
        Cruiser(base.getSymbol(), "Destroyer", base.getTeamSymbol())
    {
        setLives(3);
        setTeamSymbol(base.getTeamSymbol());
        setShipPosition(base.getShipPositionX(), base.getShipPositionY());
        shipsDestroyed = 0;
    }

// Conversion from Cruiser
Destroyer::Destroyer(Cruiser&& base) noexcept
    : Ship(base.getSymbol(), "Destroyer", base.getTeamSymbol()),
    BattleShip(base.getTeamSymbol(), "Destroyer", base.getTeamSymbol()),
    Cruiser(base.getSymbol(), "Destroyer", base.getTeamSymbol())
{
        setLives(3);
        setTeamSymbol(base.getTeamSymbol());
        setShipPosition(base.getShipPositionX(), base.getShipPositionY());
        shipsDestroyed = 0;
}

//deprecated
// // factory function cuz i didnt know how to properly use movesemantics and im tired for now
// //Destroyer* Destroyer::createFrom(Ship* source)
// //{
// //    Destroyer* dest = new Destroyer('D', "Destroyer", source->getTeamSymbol());
// //    dest->setShipPosition(source->getShipPositionX(), source->getShipPositionY());
// //    dest->setLives(source->getLives());
// //    dest->setType("Destroyer");
// //    dest->setSymbol('$');
// //    return dest;
// //}






void Destroyer::actions(char** gr, int rows, int cols, Battlefield& battlefield,game&gameManager)
{
    if (!isInDeathQueue)
    {
        SHIPS_INFO;
        look(gr, rows, cols);
        move(gr, rows, cols, battlefield);
       ram(gr, rows, cols, battlefield,gameManager);
        shoot(gr, rows, cols, battlefield,gameManager);
        if (shipsDestroyed >= 3) {
           std::cout  <<getType()<< " upgraded to SuperShip!\n";
           SuperShip* newSuperShip = new SuperShip(std::move(*this));
           battlefield.replaceShip(this, newSuperShip, gameManager);
           return;
       }
    }
    else
        std::cout << getSymbol() << " is waiting to respawn\n";
}
