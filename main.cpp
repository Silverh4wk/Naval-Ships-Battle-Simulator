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
    //game loop works now, u can just comment it out and test using other functions if u want 
         game g;
         std::cout << g.teamAEmpty();
        while (!g.shipListEmpty()  && g.iterations > 0 && !g.teamAEmpty()  && !g.teamBEmpty())
        {
        std::cout << "Rounds left: " << g.iterations << "\n";
         g.actionQueue();
         g.displayBattleField();
         g.fillQueue();
         g.iterations--;
         std::cout << g.iterations << "\n";
         std::cin.get();
        }
    
    return EXIT_SUCCESS;
}
