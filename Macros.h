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
#ifndef MACROS_H
#define MACROS_H

#include <iostream>
#include <random>

#define RANDOM_DEVICE     \
    std::random_device r; \
    std::default_random_engine r1(r());

#define SHIPS_INFO                                                             \
    std::cout << "________________________________________\n"                  \
              << getType() << " status: \n"                                    \
              << "Symbol: " << getSymbol() << "\n"                             \
              << "Position: (" << getShipPositionY() << ", " << getShipPositionX() << ")\n"     \
              << "Lives: " << getLives() << "\n"                               \
              << "Type: " << getType() << "\n"      ;                           \
                                                          \
    std::cout << "________________________________________\n";

#endif // MACROS_H