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
#ifndef CORVETTE_H
#define CORVETTE_H

#include "Ships.h"

/*
--------------------------------------------------------------------
Corvette --:
 cant move, shoot at random neighbour cells
--------------------------------------------------------------------
*/
class corvette : public ShootingShip
{
private:
    int shipsDestroyed = 0;
    int clock = 0;
    list<char> destroyedShips;
public:
    corvette(char shipSymbol, std::string type, char teamSymbol);

    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;

    static corvette* createFrom(Ship* source);

    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};

#endif // CORVETTE_H
