/**********|**********|**********|
Program: Cruiser.cpp / Cruiser.h
Course: Object Oriented Programming
Trimester: 2430
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#ifndef CRUISER_H
#define CRUISER_H

#include "Ships.h"
class Destroyer;

/*
--------------------------------------------------------------------
 Cruiser --:
 it can look it can move and it can ram
 will not shoot at all and will terminate ships at its path
 in each turn it looks at 3x3 window, it will move to one of them
 if the cruiser kills 3 of them, cruiser ---> upgrade to destroyer
--------------------------------------------------------------------
*/
class Cruiser : public RamShip
{
private:
    list<char> destroyedShips;
public:
    Cruiser(char shipSymbol, std::string type, char teamSymbol);

    Cruiser(Cruiser&& other) noexcept;
    Cruiser& operator=(Cruiser&& other) noexcept;

    ~Cruiser();
    virtual void ram(char** gr, int rows, int cols, Battlefield& battlefield,game&gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};
#endif
