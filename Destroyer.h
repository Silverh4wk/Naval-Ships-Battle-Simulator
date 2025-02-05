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
#ifndef DESTROYER_H
#define DESTROYER_H
#include "BattleShip.h"
#include "Cruiser.h"  


// Destroyer inherits from both BattleShip and cruiser

/*
--------------------------------------------------------------------
 Destroyer --:
 it can move it can shoot it can ram it can look
 if kill = 3, upgrades to supership
--------------------------------------------------------------------
*/
class Destroyer :public BattleShip, public Cruiser
{
private:
    int shipsDestroyed = 0;

public:
    Destroyer(char shipSymbol, std::string type, char teamSymbol);
    //static Destroyer* createFrom(Ship* source);

    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;

    Destroyer(Cruiser&& base) noexcept;
    Destroyer(BattleShip&& base) noexcept;
    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    virtual void ram(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
    void setDestroyedShipsNumber(int number);
    void upgradeToDestroyer();
};

#endif // DESTROYER_H
