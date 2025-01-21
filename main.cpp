#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "game.h"
#include "Ships.h"
#include "Battlefield.h"

int main()
{
    game g;
    BattleShip *ship = new BattleShip('*', "battleship");
    BattleShip *ship2 = new BattleShip('+', "battleship2");
    BattleShip *ship3 = new BattleShip('+', "battleship");
    BattleShip *ship4 = new BattleShip('+', "battleship");
    BattleShip *ship5 = new BattleShip('+', "battleship");
    BattleShip *ship6 = new BattleShip('+', "battleship");
    g.addShipToGame(ship);
    g.addShipToGame(ship2);
    g.addShipToGame(ship3);
    g.addShipToGame(ship4);
    g.addShipToGame(ship5);
    g.addShipToGame(ship6);
    std::endl(std::cout);
    g.displayBattleField();
    ship->actions(g.battlefield->getGrid(), g.battlefield->getWidth(), g.battlefield->getHeight(), *g.battlefield);
    g.displayBattleField();
    ship->getNeighbourCells();
    delete ship;
    delete ship2;
    delete ship3;
    delete ship4;
    delete ship5;
    delete ship6;

    return EXIT_SUCCESS;
}
