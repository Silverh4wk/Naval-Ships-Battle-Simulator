#include <iostream>
#include "game.h"
#include "Ships.h"
#include "Battlefield.h"
#include <fstream>
#include <sstream>

game::game()
{
    gameInit("game.txt");

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
        else if (isdigit(line[0]) || line[0] == '0')
        {
            break;
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
        battlefield = new Battlefield(grid, Width, Height);
    }

    file.close();
    file.open(filename);
    A = new Team;
    B = new Team;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        if (line.find("Team A") != std::string::npos)
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

                for (int j = 0; j < count; ++j)
                {
                    Ship *ship = nullptr;
                    if (shipType == "Battleship")
                    {
                        ship = new BattleShip(symbol, "Battleship", 'A');
                        A->BattleShipSymbol = symbol;
                        A->NumberOfBattleShip++;
                    }
                    else if (shipType == "Cruiser")
                    {
                        A->CruiserSymbol = symbol;
                        A->NumberOfCruiser++;
                    }
                    else if (shipType == "Destroyer")
                    {
                        A->DestroyerSymbol = symbol;
                        A->NumberOfDestroyer++;
                    }
                    else if (shipType == "Frigate")
                    {
                        A->FrigateSymbol = symbol;
                        A->NumberOfFrigate++;
                    }
                    else if (shipType == "Corvette")
                    {
                        A->CorvetteSymbol = symbol;
                        A->NumberOfCorvette++;
                    }
                    else if (shipType == "Amphibious")
                    {
                        A->AmphibiousSymbol = symbol;
                        A->NumberOfAmphibious++;
                    }
                    else if (shipType == "SuperShip")
                    {
                        A->SuperShipSymbol = symbol;
                        A->NumberOfSuperShip++;
                    }

                    if (ship)
                    {
                        A->ships.push_back(ship);
                        addShipToGame(ship);
                        queue.enqueue(ship);
                    }
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

                for (int j = 0; j < count; ++j)
                {
                    Ship *ship = nullptr;
                    if (shipType == "Battleship")
                    {
                        ship = new BattleShip(symbol, "Battleship", 'B');
                        B->BattleShipSymbol = symbol;
                        B->NumberOfBattleShip++;
                    }
                    else if (shipType == "Cruiser")
                    {
                        B->CruiserSymbol = symbol;
                        B->NumberOfCruiser++;
                    }
                    else if (shipType == "Destroyer")
                    {
                        B->DestroyerSymbol = symbol;
                        B->NumberOfDestroyer++;
                    }
                    else if (shipType == "Frigate")
                    {
                        B->FrigateSymbol = symbol;
                        B->NumberOfFrigate++;
                    }
                    else if (shipType == "Corvette")
                    {
                        B->CorvetteSymbol = symbol;
                        B->NumberOfCorvette++;
                    }
                    else if (shipType == "Amphibious")
                    {
                        B->AmphibiousSymbol = symbol;
                        B->NumberOfAmphibious++;
                    }
                    else if (shipType == "SuperShip")
                    {
                        B->SuperShipSymbol = symbol;
                        B->NumberOfSuperShip++;
                    }

                    if (ship)
                    {
                        B->ships.push_back(ship);
                        addShipToGame(ship);
                        queue.enqueue(ship);
                    }
                }
                std::cout << shipType << " " << symbol << " " << count << "\n";
            }
        }
    }

    file.close();
    std::cout << "Game initialized from the file: " << filename << std::endl;
    return true;
}

void game::addShipToGame(Ship *ship)
{
    if (ship == nullptr)
    {
        std::cerr << "Error: Ship pointer is null." << std::endl;
        return;
    }
    if (battlefield != nullptr)
    {
        battlefield->placeShip(ship);
        return;
    }
    std::cerr << "Error: Battlefield is not initialized." << std::endl;
    return;
}
void game::hardaddShipToGame(Ship *ship, int x, int y)
{
    battlefield->hardPlaceShip(ship, x, y);
}

void game::displayBattleField() const { battlefield->display(); }

bool game::shipListEmpty() const
{
    if (A->ships.getSize() == 0 && B->ships.getSize() == 0)
    {
        return true;
    }
    return false;
}

bool game::teamAEmpty() const
{
    return A->ships.getSize() < 1;
}

bool game::teamBEmpty() const
{
    return B->ships.getSize() < 1;
}


void game::actionQueue()
{
    while (queue.getSize() > 0) 
    {
        try
        {
            Ship *ship = queue.front();

            ship->actions(grid, Width, Height, *battlefield);
            battlefield->display();

            queue.dequeue();
            std::cin.get();
        }
        catch (const std::exception &e) 
        {
            std::cerr << "Error during queue processing: " << e.what() << "\n";
            break;
        }
    }

    std::cout << "Action queue processing complete. Remaining queue size: " << queue.getSize() << "\n";
}

void game::fillQueue()
{
    for (int i = 0; i < A->ships.getSize(); i++)
    {
        queue.enqueue(A->ships.getNode(i));
    }
    for (int i = 0; i < B->ships.getSize(); i++)
    {
        queue.enqueue(B->ships.getNode(i));
    }
    std::cout << queue.getSize() << "\n";
}
