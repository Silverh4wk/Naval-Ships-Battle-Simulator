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

// Custom stream buffer that writes to two stream buffers (found online, ask if ok to use).
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
    g.displayBattleField();

    while (!g.shipListEmpty() && g.iterations > 0 && !g.teamAEmpty() && !g.teamBEmpty()) {
        std::cout << "Rounds left: " << g.iterations << "\n";
        g.actionQueue();
        g.displayBattleField();
        g.fillQueue();
        g.respawn();
        g.displayBattleField();
        g.iterations--;
        g.removeDeadShipFromTeam();
    }

    if (g.teamAEmpty() && !g.teamBEmpty()) {
        std::cout << "Game Over! Team B Wins!\n";
    }
    else if (g.teamBEmpty() && !g.teamAEmpty()) {
        std::cout << "Game Over! Team A Wins!\n";
    }
    else {
        std::cout << "Game Over! It's a draw!\n";
    }

    std::cout.rdbuf(origCoutBuf);

    outFile.close();
}

void printRules() {
    std::cout << "\n==== Rules/About Ships ====\n";
    std::cout << "add later";
    std::cout << "================================\n\n";
}

void printCredits() {
    std::cout << "\n==== Credits ====\n";
    std::cout << "Game Simulation by:\n Hazim Elamin Mohamed Ali 241UC2400P\n";
    std::cout << "Mohamed Rime Hamza 241UC240Y\n";
    std::cout << "================================" << std::endl;
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int choice = 0;
    do {
        std::cout << "==== Main Menu ====\n";
        std::cout << "1. Start Simulation\n";
        std::cout << "2. Rules/About Ships\n";
        std::cout << "3. Credits\n";
        std::cout << "4. Ships\n";
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
            std::cout << "Ships function add later\n";
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
