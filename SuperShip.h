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
#ifndef SUPERSHIP_H
#define SUPERSHIP_H

#include "Cruiser.h"
#include "Amphibious.h"
#include "Destroyer.h"
/*
--------------------------------------------------------------------
 SuperShip --:
 it can do everything
 it move like a cruiser, killing everything in its way
 shoots randomly at 3 locations in the same turn
--------------------------------------------------------------------
*/
class SuperShip : public Cruiser, public ShootingShip { 
private:
    int shipsDestroyed = 0;
    list<char> destroyedShips;

public:
    SuperShip(char shipSymbol, std::string type, char teamSymbol);
    SuperShip(Amphibious&& base) noexcept;
    SuperShip(Destroyer&& base) noexcept;
    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    //static SuperShip* createFrom(Ship* source);
    void upgradeToSuperShip();

};

#endif // SUPERSHIP_H
