/**********|**********|**********|
Program: Corvette.cpp / Corvette.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
**********|**********|**********/
#ifndef CORVETTE_H
#define CORVETTE_H

#include "Ships.h"
#include "Frigate.h"
/*
--------------------------------------------------------------------
Corvette --:
 cant move, shoot at random neighbour cells
--------------------------------------------------------------------
*/
class corvette : public ShootingShip
{
private:
    int clock = 0;
    list<char> destroyedShips;
public:
    corvette(char shipSymbol, std::string type, char teamSymbol);
    corvette(Frigate&& base) noexcept;
    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};

#endif 
