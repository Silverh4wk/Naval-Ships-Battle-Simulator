#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "game.h"
#include <random>

int main()
{
    game g;
    BattleShip *ship = new BattleShip('*', "battleship");
    BattleShip *ship3 = new BattleShip('+', "battleship");
    BattleShip *ship4 = new BattleShip('+', "battleship");
    BattleShip *ship2 = new BattleShip('+', "battleship2");
    g.addShipToGame(ship);
    g.addShipToGame(ship2);
    g.addShipToGame(ship3);
    g.addShipToGame(ship4);
    g.displayBattleField();
    ship->actions(g.battlefield->getGrid(), g.battlefield->getWidth(), g.battlefield->getHeight());
    g.displayBattleField();
    delete ship;
    delete ship2;
    delete ship3;
    delete ship4;
    
    return EXIT_SUCCESS;
}
