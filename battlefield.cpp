#include <iostream>
#include "ships.h"

class Battlefield {
private:
    int width, height;
    char **grid;

    void initializeGrid() {
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                grid[i][j] = '0';
    }

public:
    Battlefield(char g,int w, int h) : width(w), height(h) {
        grid = new char *[height];
        for (int i = 0; i < height; ++i)
            grid[i] = new char[width];
        **grid = g;
        initializeGrid();
    }

    ~Battlefield() {
        for (int i = 0; i < height; ++i)
            delete[] grid[i];
        delete[] grid;
    }

    // To do, figure out how to place ships randmonly using random  x = rand() % height; y = rand() % width;
    void placeShip(Ship &ship) {

    }

    void display() const {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j)
                std::cout << grid[i][j] << ' ';
            std::cout << std::endl;
        }
    }
};