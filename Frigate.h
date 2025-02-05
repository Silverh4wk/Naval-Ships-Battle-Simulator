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
#ifndef FRIGATE_H
#define FRIGATE_H

#include "Ships.h"

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
    int shipsDestroyed = 0;
    list<char> destroyedShips;
    int clock = 0;
public:
    Frigate(char shipSymbol, std::string type, char teamSymbol);

    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield,game&gameManager) override;

    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};

#endif // FRIGATE_H
