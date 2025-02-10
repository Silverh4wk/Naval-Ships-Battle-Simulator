/**********|**********|**********|
Program: Amphibious.cpp / Amphibious.h
Course: Object Oriented Programming
Trimester: 2430
Name: RIME HAMZA MOHAMMED
ID: 241UC240Y8
Lecture Section: TC2L
Tutorial Section: TT7L
Email: mohammed.rime.hamza@student.mmu.edu.my
Phone: +60-108-220-891
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
public:
    Amphibious(char shipSymbol, std::string type, char teamSymbol);
    Amphibious(Amphibious&&) noexcept = default;
    ~Amphibious() {
        std::cout << "Amphibious was deleted\n";
    }
    Amphibious& operator=(Amphibious&& other) noexcept;
    virtual void move(char** gr, int rows, int cols, Battlefield& battlefield) override;
    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};

#endif 
