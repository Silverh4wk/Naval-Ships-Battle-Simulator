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
 The Corvette ship cannot move; it solely fires at random neighboring cells.
 This class uses an internal clock variable to manage its shooting timing:
      It is incremented every cycle in the actions function. Once it reaches a preset threshold,
      the Corvette triggers the shoot function to fire at one of its neighbors. 
Functions and their operations:
  - shoot:
        This function randomly selects one of the neighboring cells and fires at it.
        It verifies that the selected cell is within grid bounds and, if an enemy is present,
        applies damage. This random targeting embodies the Corvette's unpredictable behavior.
  - actions:
        As the Corvette cannot move, this function solely focus on shooting.
        It increments the clock on each cycle.
--------------------------------------------------------------------
*/
class Corvette : public ShootingShip
{
private:
    int clock = 0;
public:
    Corvette(char shipSymbol, std::string type, char teamSymbol);
    Corvette(Frigate&& base) noexcept;
    ~Corvette() {
        std::cout << "Corvette was deleted\n";
    }
    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};

#endif 
