#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "game.h"
#include "Ships.h"
#include "Battlefield.h"
// changed the number of iterations to 15 just for testing 

int main()
{
    // game loop works now, u can just comment it out and test using other functions(hardaddship and actions manually) if u want
    game g;
    g.displayBattleField();
    while (!g.shipListEmpty() && g.iterations > 0 && !g.teamAEmpty() && !g.teamBEmpty())
    {
        std::cout << "Rounds left: " << g.iterations << "\n";
        g.actionQueue();
        g.displayBattleField();
        g.fillQueue();
        g.respawn();
        g.displayBattleField();
        g.iterations--;
        // pause between rounds if needed
        std::cin.get();
    }
    return EXIT_SUCCESS;
}