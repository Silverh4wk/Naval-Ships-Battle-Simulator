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
    BattleShip *ship7 = new BattleShip('+', "battleship");
    BattleShip *ship8 = new BattleShip('+', "battleship");
    BattleShip *ship9 = new BattleShip('+', "battleship");
    g.hardaddShipToGame(ship, 3, 6);
    g.hardaddShipToGame(ship2, 3, 7);
    g.addShipToGame(ship3);
    g.addShipToGame(ship4);
    g.addShipToGame(ship5);
    g.addShipToGame(ship6);
    g.addShipToGame(ship7);
    g.addShipToGame(ship8);
    g.addShipToGame(ship9);
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
    delete ship7;
    delete ship8;
    delete ship9;
    g.battlefield->getShipAt(3, 6);

    return EXIT_SUCCESS;
}
