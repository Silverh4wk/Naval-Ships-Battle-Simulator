/**********|**********|**********|
Program: Frigate.cpp / Frigate.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
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
    list<char> destroyedShips;
    int clock = 0;

public:
    Frigate(char shipSymbol, std::string type, char teamSymbol);
    Frigate(Frigate &&) noexcept;
    Frigate &operator=(Frigate &&other) noexcept;
    virtual void shoot(char **gr, int rows, int cols, Battlefield &battlefield, game &gameManager) override;

    virtual void actions(char **gr, int rows, int cols, Battlefield &battlefield, game &gameManager) override;
};

#endif // FRIGATE_H
