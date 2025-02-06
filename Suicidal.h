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
#ifndef SUICIDAL_H
#define SUICIDAL_H
#include "ships.h"

/// blow  a 3x3 area and anything in that area will get cleared even islands
class Suicidal : public BlowShip
{
private:
    int shipsDestroyed = 0;
    list<char> destroyedShips;
public:
    Suicidal(char shipSymbol, std::string type, char teamSymbol);
    void BlowUp(char** gr, int rows, int cols, Battlefield& battlefield) override;
    virtual void actions(char** gr, int rows, int cols, Battlefield& battlefield, game& gameManager) override;
};

#endif // SUICIDAL_H
