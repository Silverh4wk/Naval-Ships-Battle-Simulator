#include <iostream>

#include "Battlefield.h"



  void Battlefield::initializeGrid()
    {
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                grid[i][j] = '0';
    }

    // my thoughts just for tracking
    // will set the grid in battelfield = to the grid from game 
    // then after copying everything, it will set gr(grid in game) to nullptr;
    Battlefield::Battlefield(char**gr, int w, int h):width(w), height(h)
    {
        grid = gr;
        for (int i = 0; i < height; ++i)
            grid[i] = gr[i];
        **grid = **gr;
        gr = nullptr;
        }

    Battlefield::~Battlefield()
    {
        for (int i = 0; i < height; ++i)
            delete[] grid[i];
        delete[] grid;
        std::cout << "battlefled deleted\n";
    }

    // To do, figure out how to place ships randmonly using random  x = rand() % height; y = rand() % width;
    // void placeShip(Ship &ship)
    // {
    // }

    void Battlefield::display() const
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
                std::cout << grid[i][j] << ' ';
            std::cout << std::endl;
        }
    }
