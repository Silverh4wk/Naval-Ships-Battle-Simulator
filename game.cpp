#include <iostream>
#include "battlefield.h"
#include "game.h"
#include <fstream>
#include <sstream>

game::game()
{
    gameInit("game.txt");
    battlefield = new Battlefield(grid, Width, Height);
    std::cout << std::endl;
    battlefield->display();
    std::cout << std::endl;
};

game::~game()
{
    delete A;
    delete B;
    delete battlefield;
    
    std::cout << "game ended\n";
};
bool game::gameInit(std::string &&filename)
{
    A = new Team;
    B = new Team;

    std::ifstream file{filename};
    std::string line;

    if (!file.is_open())
    {
        std::cout << "File couldn't open\n";
        return false;
    }

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        if (line.find("iterations") != std::string::npos)
        {
            ss.ignore(line.find(' ') + 1);
            ss >> iterations;
            std::cout << "Iterations = " << iterations << std::endl;
        }
        else if (line.find("width") != std::string::npos)
        {
            ss.ignore(line.find(' ') + 1);
            ss >> Width;
            std::cout << "Width = " << Width << std::endl;
        }
        else if (line.find("height") != std::string::npos)
        {
            ss.ignore(line.find(' ') + 1);
            ss >> Height;
            std::cout << "Height = " << Height << std::endl;
        }
        else if (line.find("Team A") != std::string::npos)
        {
            ss.ignore(7);
            ss >> A->NumberOfShips;
            std::cout << "Number of ships assigned to Team A is: " << A->NumberOfShips << "\n";

            for (int i = 0; i < A->NumberOfShips; ++i)
            {
                std::getline(file, line);
                std::istringstream shipStream(line);
                std::string shipType;
                char symbol;
                int count;

                shipStream >> shipType >> symbol >> count;
                if (shipType == "Battleship")
                {
                    A->BattleShipSymbol = symbol;
                    A->NumberOfBattleShip = count;
                }
                else if (shipType == "Cruiser")
                {
                    A->CruiserSymbol = symbol;
                    A->NumberOfCruiser = count;
                }
                else if (shipType == "Destroyer")
                {
                    A->DestroyerSymbol = symbol;
                    A->NumberOfDestroyer = count;
                }
                else if (shipType == "Frigate")
                {
                    A->FrigateSymbol = symbol;
                    A->NumberOfFrigate = count;
                }
                else if (shipType == "Corvette")
                {
                    A->CorvetteSymbol = symbol;
                    A->NumberOfCorvette = count;
                }
                else if (shipType == "Amphibious")
                {
                    A->AmphibiousSymbol = symbol;
                    A->NumberOfAmphibious = count;
                }
                else if (shipType == "SuperShip")
                {
                    A->SuperShipSymbol = symbol;
                    A->NumberOfSuperShip = count;
                }
                std::cout << shipType << " " << symbol << " " << count << "\n";
            }
        }
        else if (line.find("Team B") != std::string::npos)
        {
            ss.ignore(7);
            ss >> B->NumberOfShips;
            std::cout << "Number of ships assigned to Team B is: " << B->NumberOfShips << "\n";

            for (int i = 0; i < B->NumberOfShips; ++i)
            {
                std::getline(file, line);
                std::istringstream shipStream(line);
                std::string shipType;
                char symbol;
                int count;

                shipStream >> shipType >> symbol >> count;
                if (shipType == "Battleship")
                {
                    B->BattleShipSymbol = symbol;
                    B->NumberOfBattleShip = count;
                }
                else if (shipType == "Cruiser")
                {
                    B->CruiserSymbol = symbol;
                    B->NumberOfCruiser = count;
                }
                else if (shipType == "Destroyer")
                {
                    B->DestroyerSymbol = symbol;
                    B->NumberOfDestroyer = count;
                }
                else if (shipType == "Frigate")
                {
                    B->FrigateSymbol = symbol;
                    B->NumberOfFrigate = count;
                }
                else if (shipType == "Corvette")
                {
                    B->CorvetteSymbol = symbol;
                    B->NumberOfCorvette = count;
                }
                else if (shipType == "Amphibious")
                {
                    B->AmphibiousSymbol = symbol;
                    B->NumberOfAmphibious = count;
                }
                else if (shipType == "SuperShip")
                {
                    B->SuperShipSymbol = symbol;
                    B->NumberOfSuperShip = count;
                }
                std::cout << shipType << " " << symbol << " " << count << "\n";
            }
        }
        else if (isdigit(line[0]) || line[0] == '0')
        {
            break; // This marks the start of the grid/map
        }
    }

    grid = new char *[Height];
    for (int i = 0; i < Height; i++)
    {
        grid[i] = new char[Width];
    }

    for (auto i = 0; i < Height; i++)
    {
        std::istringstream gridstream(line);
        for (auto j = 0; j < Width; j++)
        {
            gridstream >> grid[i][j];
        }
        if (i < Height - 1)
        {
            std::getline(file, line);
        }
    }

    file.close();
    std::cout << "Game initialized from the file: " << filename << std::endl;
    return true;
}

void game::addShipToGame(Ship *ship)
{
    battlefield->placeShip(ship);
}
void game::hardaddShipToGame(Ship *ship,int x, int y)
{
    battlefield->hardPlaceShip(ship,x,y);
}


void game::displayBattleField()const {battlefield->display();}