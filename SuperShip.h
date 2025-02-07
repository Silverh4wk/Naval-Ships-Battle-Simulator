/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
**********|**********|**********/
#ifndef SUPERSHIP_H
#define SUPERSHIP_H

#include "Cruiser.h"
#include "Amphibious.h"
#include "Destroyer.h"
#include "BattleShip.h"
/*
--------------------------------------------------------------------
 SuperShip --:
 it can do everything
 it move like a cruiser, killing everything in its way
 shoots randomly at 3 locations in the same turn
--------------------------------------------------------------------
*/
class SuperShip : public Destroyer { 
public:
    ~SuperShip() {
        std::cout << "SuperShip was deleted\n";
    }
    SuperShip(char shipSymbol, std::string type, char teamSymbol);
    SuperShip(Amphibious&& base) noexcept;
    SuperShip(Destroyer&& base) noexcept;
    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    //static SuperShip* createFrom(Ship* source);

};

#endif 
