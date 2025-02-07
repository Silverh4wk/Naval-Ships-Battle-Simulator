/**********|**********|**********|
Program: Battleship.cpp / Battleship.h
Course: Object Oriented Programming
Trimester: 2430
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Ships.h"

/*
--------------------------------------------------------------------
 battleship --:
 it can shoot, it can move, it can see
 looks at its current pos then decide to move
 move once then shoot twice at random positions, x+y is 5 blocks
 cant move to a location that contain another Ship
 if shoot hit = 4 ---> upgrade to destroyer
--------------------------------------------------------------------
*/
class BattleShip : public MovingShip, public ShootingShip, public SeeingRobot
{
public:
    BattleShip(char shipSymbol, std::string type, char teamSymbol);
    ~BattleShip();
    BattleShip(BattleShip&&) noexcept;
    BattleShip& operator=(BattleShip&& other) noexcept;


    virtual void move(char** gr, int rows, int cols, Battlefield& battlefield) override;

    virtual void look(char** gr, int rows, int cols) override;

    virtual void shoot(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;

    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;

        
};

#endif 
