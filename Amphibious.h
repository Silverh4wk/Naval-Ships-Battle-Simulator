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
#ifndef AMPHIBIOUS_H
#define AMPHIBIOUS_H

#include "BattleShip.h"

/*
--------------------------------------------------------------------
 Amphibious --:
 land and water
 battleship behaviour
 if kill =4, upgrades to SUPERSHIP
--------------------------------------------------------------------
*/
class Amphibious : public BattleShip
{
private:
    int shipsDestroyed = 0;
    list<char> destroyedShips;
public:
    Amphibious(char shipSymbol, std::string type, char teamSymbol);
    Amphibious(Amphibious&&) noexcept = default;
    Amphibious& operator=(Amphibious&& other) noexcept;
    void moveTo(Ship& target);
    virtual void move(char** gr, int rows, int cols, Battlefield& battlefield) override;

    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};

#endif // AMPHIBIOUS_H
