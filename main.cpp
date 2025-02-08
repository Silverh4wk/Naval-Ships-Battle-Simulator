/**********|**********|**********|
Program: main.cpp / main.h
Course: Object Oriented Programming
Trimester: 2430
Name: Hazim Elamin Mohamed Ali musa
Name: RIME HAMZA MOHAMMED
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "game.h"
#include "ships.h"
#include "Battlefield.h"
#include <crtdbg.h>
#include <cstdlib>
class TeeBuf;
void runSimulation();
void printRules();
void AboutShips();
void printCredits();

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int choice = 0;
    do {
        std::cout << "***WarShip Simulation*** \n";
        std::cout << "==== Main Menu ====\n";
        std::cout << "1. Start Simulation\n";
        std::cout << "2. Rules\n";
        std::cout << "3. About Ships\n";
        std::cout << "4. Creduts\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            runSimulation();
            break;
        case 2:
            printRules();
            break;
        case 3:
           AboutShips();
            break;
        case 4:
            printCredits();
            break;
        case 5:
            std::cout << "Exiting the game. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        std::cin.ignore();
    } while (choice != 5);
    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

// Custom stream buffer that writes to two stream buffers 
class TeeBuf : public std::streambuf {
    public:
        TeeBuf(std::streambuf* sb1, std::streambuf* sb2)
            : sb1(sb1), sb2(sb2) {
        }
    
    protected:
        virtual int overflow(int c) override {
            if (c == EOF)
                return !EOF;
            else {
                int const r1 = sb1->sputc(c);
                int const r2 = sb2->sputc(c);
                return (r1 == EOF || r2 == EOF) ? EOF : c;
            }
        }
    
        virtual int sync() override {
            int const r1 = sb1->pubsync();
            int const r2 = sb2->pubsync();
            return (r1 == 0 && r2 == 0) ? 0 : -1;
        }
    
    private:
        std::streambuf* sb1;
        std::streambuf* sb2;
    };
    
    void runSimulation() {
        std::ofstream outFile("game_output.txt");
        if (!outFile) {
            std::cerr << "Unable to open file for writing\n";
            return;
        }
    
        std::streambuf* origCoutBuf = std::cout.rdbuf();
    
        TeeBuf tee(origCoutBuf, outFile.rdbuf());
        std::cout.rdbuf(&tee);
    
        game g;
        std::cout << "\n SIMULATION BEGIN , ROUNDS =  " << g.iterations << "\n\n";
        while (!g.shipListEmpty() && g.iterations > 0 && !g.teamAEmpty() && !g.teamBEmpty()) {
            std::cout << "Rounds left: " << g.iterations << "\n";
            g.removeDeadShipFromTeam();
            g.respawn();
            g.displayBattleField();
            g.actionQueue();
            g.removeDeadShipFromTeam();
            g.fillQueue();
            g.displayBattleField();
            g.iterations--;
            //std::cin.get(); if a pause between rounds is needed but i would adive against it unless the simulation is small
            // as one run may take thousands of lines
        }
    
        if ( g.getTeam('B')->ships.getSize()>g.getTeam('A')->ships.getSize()) {
            std::cout << "Game Over! Team B Wins!\n";
        }
        else if (g.getTeam('A')->ships.getSize()>g.getTeam('B')->ships.getSize()) {
            std::cout << "Game Over! Team A Wins!\n";
        }
        else {
            std::cout << "Game Over! It's a draw!\n";
        }
    
        std::cout.rdbuf(origCoutBuf);
    
        outFile.close();
    }
    
    void printRules() {
        std::cout << "\n==== Rules ====\n";
        std::cout << "1. Each ship has 3 lives." << std::endl;
        std::cout << "2. When a ship is destroyed, it is placed in a queue and may re-enter the battlefield up to 3 times." << std::endl;
        std::cout << "3. In each turn, 2 ships are allowed to re-enter at random locations on the battlefield." << std::endl;
        std::cout << "4. The battlefield is represented by a grid where '0' denotes water and '1' denotes an island." << std::endl;
        std::cout << "5. Ships can only spawn and move on water, except for specialized ships such as the Amphibious." << std::endl;
        std::cout << "6. A team wins when the opposing team is completely annihilated." << std::endl;
        std::cout << "7. If the iterations reach zero, the team with a larger number of ships remaining is declared the winner." << std::endl;
        std::cout << "================================\n" << std::endl;
    }
    
    void printCredits() {
        std::cout << "\n==== Credits ====\n";
        std::cout << "Game Simulation by:\n Hazim Elamin Mohamed Ali 241UC2400P\n";
        std::cout << " Mohamed Rime Hamza 241UC240Y\n";
        std::cout << "================================" << std::endl;
    }
    
    void AboutShips() {
        std::cout << "\n==== Ships ====\n";
    
        // Battleship
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: Battleship" << std::endl;
        std::cout << "Behavior: In each turn, the Battleship evaluates its current position and decides on a move." << std::endl;
        std::cout << "          It then moves once and fires 2 shots at random positions." << std::endl;
        std::cout << "Firing:   The maximum city block distance for any shot is 5 (i.e. for any fire(x,y), x+y <= 5)." << std::endl;
        std::cout << "Movement: Cannot move to a location occupied by another ship or is out of bounds." << std::endl;
        std::cout << "Upgrade:  After shooting a total of 4 enemy ships, it is upgraded so that it can move to" << std::endl;
        std::cout << "          a cell occupied by an enemy ship, destroying that ship, effectively upgraded to a Destroyer. " << std::endl;
    
        // Cruiser
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: Cruiser" << std::endl;
        std::cout << "Behavior: Each turn, the Cruiser inspects its immediate 3x3 neighbourhood" << std::endl;
        std::cout << "          (centered at its current position) and moves to one of the neighbouring cells." << std::endl;
        std::cout << "Combat:   It does not fire; instead, it destroys (Rams) any enemy ship encountered  on its path," << std::endl;
        std::cout << "          preferring cells that contain enemy ships." << std::endl;
        std::cout << "Upgrade:  After eliminating 3 enemy ships, the Cruiser gains firing capabilities similar to" << std::endl;
        std::cout << "          the Battleship and is upgraded to a Destroyer." << std::endl;
    
        // Destroyer
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: Destroyer" << std::endl;
        std::cout << "Description: A Destroyer combines the functionality of both the BattleShip and Cruiser." << std::endl;
        std::cout << "             It can both shoot (like the Battleship) and destroy enemy ships on contact" << std::endl;
        std::cout << "             (like the Cruiser)." << std::endl;
        std::cout << "Upgrade:     After killing 3 enemy ships, a Destroyer is upgraded to a SuperShip." << std::endl;
    
        // Frigate
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: Frigate" << std::endl;
        std::cout << "Behavior: Does not move or scan its surroundings. It remains stationary." << std::endl;
        std::cout << "Firing:   Shoots at one immediate neighbouring cell per turn. The target cell is" << std::endl;
        std::cout << "          chosen according to a fixed sequence: starting from the cell directly above" << std::endl;
        std::cout << "          and then proceeding clockwise with each subsequent turn." << std::endl;
        std::cout << "Upgrade:  After shooting a total of 3 enemy ships, the Frigate is upgraded to a Corvette." << std::endl;
    
        // Corvette
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: Corvette" << std::endl;
        std::cout << "Behavior: A stationary ship that does not move." << std::endl;
        std::cout << "Firing:   Shoots at one immediate neighbouring cell per turn, but the target is selected" << std::endl;
        std::cout << "          at random." << std::endl;
    
        // Amphibious
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: Amphibious" << std::endl;
        std::cout << "Behavior: Can traverse both sea and island terrains. Its movement and firing pattern" << std::endl;
        std::cout << "          is similar to that of the Battleship." << std::endl;
        std::cout << "Upgrade:  After terminating 4 enemy ships, it is upgraded to a SuperShip." << std::endl;
    
        // SuperShip
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: SuperShip" << std::endl;
        std::cout << "Behavior: Moves like the Cruiser, destroying any enemy ship encountered on its path." << std::endl;
        std::cout << "Firing:   In addition, it fires randomly at 3 locations on the battlefield each turn." << std::endl;
      
        // Suicidal
        std::cout << "_________________________________" << std::endl;
        std::cout << "Ship Type: Suicidal" << std::endl;
        std::cout << "Behavior: Blows and clears its surroundings(3x3), destroying any enemy ship caught in the explosion and itself." << std::endl;
        std::cout << "================================" << std::endl;
    }