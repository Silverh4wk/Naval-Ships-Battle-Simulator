




 


/**********|**********|**********|
Program: game.cpp / game.h
Course: Object Oriented Programming
Trimester: 2430
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#include <iostream>
#include "Game.h"
#include "Ships.h"
#include "Amphibious.h"
#include "BattleShip.h"
#include "Corvette.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Frigate.h"
#include "SuperShip.h"
#include "Suicidal.h"
#include "Battlefield.h"
#include <fstream>
#include <sstream>
#include <random>

// Initializes the game by reading configuration parameters from "game.txt",
// setting up the battlefield and teams, and displaying the initial state of the battlefield.
game::game()
{
    gameInit("game.txt");

    std::cout << std::endl;
    battlefield->display();
    std::cout << std::endl;
};
//  Deallocates dynamically allocated memory including the grid, battlefield,
//  teams, and ship objects. Ensures proper cleanup to prevent memory leaks.
game::~game()
{
    std::cout << "game is ending.. \n";

    if (grid)
    {
        for (int i = 0; i < Height; ++i)
        {
            delete[] grid[i];
        }
        delete[] grid;
        grid = nullptr;
    }
    delete battlefield;
    battlefield = nullptr;

    while (A->ships.getSize() > 0)
    {
        Ship* ship = A->ships.getNode(0);
        A->ships.deleteNodeAtIndex(0);
        delete ship; 
    }

    while (B->ships.getSize() > 0)
    {
        Ship* ship = B->ships.getNode(0);
        B->ships.deleteNodeAtIndex(0);
        delete ship;
    }
    delete A;
    delete B;

    std::cout << "game ended\n";
};


 // Reads configuration data (iterations, grid width, and height) and populates the grid.
 //first it opens the file, get the data of the gird, close it and then reopen to get the rest of the data
 // Processes the file to initialize teams and ship counts, places ships on the battlefield,
 // and enqueues them for action processing.
 //  filename: The name of the file to read the game configuration from.
 // return  true if the file was successfully processed and the game initialized; false otherwise.
 
bool game::gameInit(std::string &&filename)
{

    std::ifstream file{filename};
    std::string line;

    if (!file.is_open())
    {
        std::cout << "File couldn't open\n";
        return false;
    }

    if (grid)
    {
        for (int i = 0; i < Height; ++i)
        {
            delete[] grid[i];
        }
        delete[] grid;
        grid = nullptr;
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
    }
    battlefield = new Battlefield(grid, Width, Height);

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
                        ship = new Cruiser(symbol, "Cruiser", 'A');
                        A->CruiserSymbol = symbol;
                        A->NumberOfCruiser++;
                    }
                    else if (shipType == "Destroyer")
                    {
                        ship = new Destroyer(symbol, "Destroyer", 'A');
                        A->DestroyerSymbol = symbol;
                        A->NumberOfDestroyer++;
                    }
                    else if (shipType == "Frigate")
                    {
                        ship = new Frigate(symbol, "Frigate", 'A');
                        A->FrigateSymbol = symbol;
                        A->NumberOfFrigate++;
                    }
                    else if (shipType == "Corvette")
                    {
                        ship = new Corvette(symbol, "Corvette", 'A');
                        A->CorvetteSymbol = symbol;
                        A->NumberOfCorvette++;
                    }
                    else if (shipType == "Amphibious")
                    {
                        ship = new Amphibious(symbol, "Amphibious", 'A');
                        A->AmphibiousSymbol = symbol;
                        A->NumberOfAmphibious++;
                    }
                    else if (shipType == "SuperShip")
                    {
                        ship = new SuperShip(symbol, "SuperShip", 'A');
                        A->SuperShipSymbol = symbol;
                        A->NumberOfSuperShip++;
                    }
                    else if (shipType == "Suicidal")
                    {
                        ship = new Suicidal(symbol, "Suicidal", 'A');
                        A->SuicidalSymbol = symbol;
                        A->NumberOfSuicidal++;
                    }
                    if (ship)
                    {
                        A->ships.push_back(ship);
                        addShipToGame(ship);
                        queue.enqueue(ship);
                    }
                    else
                        std::cout << "cant place " << shipType << " " << symbol << " " << count << "\n";
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
                        ship = new Cruiser(symbol, "Cruiser", 'B');
                        B->CruiserSymbol = symbol;
                        B->NumberOfCruiser++;
                    }
                    else if (shipType == "Destroyer")
                    {
                        ship = new Destroyer(symbol, "Destroyer", 'B');

                        B->DestroyerSymbol = symbol;
                        B->NumberOfDestroyer++;
                    }
                    else if (shipType == "Frigate")
                    {
                        ship = new Frigate(symbol, "Frigate", 'B');
                        B->FrigateSymbol = symbol;
                        B->NumberOfFrigate++;
                    }
                    else if (shipType == "Corvette")
                    {
                        ship = new Corvette(symbol, "Corvette", 'B');
                        B->CorvetteSymbol = symbol;
                        B->NumberOfCorvette++;
                    }
                    else if (shipType == "Amphibious")
                    {
                        ship = new Amphibious(symbol, "Amphibious", 'B');
                        B->AmphibiousSymbol = symbol;
                        B->NumberOfAmphibious++;
                    }
                    else if (shipType == "SuperShip")
                    {
                        ship = new SuperShip(symbol, "SuperShip", 'B');
                        B->SuperShipSymbol = symbol;
                        B->NumberOfSuperShip++;
                    }
                    else if (shipType == "Suicidal")
                    {
                        ship = new Suicidal(symbol, "Suicidal", 'B');
                        B->SuicidalSymbol = symbol;
                        B->NumberOfSuicidal++;
                    }

                    if (ship)
                    {
                        B->ships.push_back(ship);
                        addShipToGame(ship);
                        queue.enqueue(ship);
                    }
                    else
                        std::cout << "cant place " << shipType << " " << symbol << " " << count << "\n";
                }
                std::cout << shipType << " " << symbol << " " << count << "\n";
            }
        }
    }

    file.close();
    std::cout << "Game initialized from the file: " << filename << std::endl;
    return true;
}
// 
//  Adds a ship to the game.
//  Validates the ship pointer and the battlefield before placing the ship on the battlefield .
//  Outputs the ship's type and symbol as confirmation of placement.
//   ship Pointer to the Ship object to be added.
void game::addShipToGame(Ship *ship)
{
    if (ship == nullptr)
    {
        std::cerr << "Error: Ship pointer is null." << std::endl;
        return;
    }
    if (battlefield == nullptr)
    {
        std::cerr << "Error: Battlefield is not initialized." << std::endl;
        return;
    }

    std::cout << "Adding ship to game: " << ship->getType()
              << " with symbol " << ship->getSymbol() << std::endl;

    battlefield->placeShip(ship);
}


// 
//   Adds a ship to the game at specific coordinates.
//   Places the given ship directly on the battlefield at the position specified
//   by (x, y) without further processing or random placement.
//  was specifically used for testing

void game::hardaddShipToGame(Ship *ship, int x, int y)
{
    battlefield->hardPlaceShip(ship, x, y);
}

//    Displays the battlefield.
//   Outputs the current grid state of the battlefield to the provided output stream.
//   If the battlefield is not initialized, prints an appropriate message.
//   os is The output stream where the battlefield will be displayed.

void game::displayBattleField(std::ostream &os) const
{
    if (battlefield)
    {
        battlefield->display(os);
    }
    else
    {
        os << "Battlefield is not initialized.\n";
    }
}




//   Checks whether both teams' ship lists are empty.
//   return true if both Team A and Team B have no ships remaining; false otherwise.

bool game::shipListEmpty() const
{
    if (A->ships.getSize() == 0 && B->ships.getSize() == 0)
    {
        return true;
    }
    return false;
}

//   Checks Team A ship lists if its empty.
//   return true if Team A have no ships remaining; false otherwise.
bool game::teamAEmpty() const
{
    return A->ships.getSize() < 1;
}

//   Checks Team B ship lists if its empty.
//   return true if Team B have no ships remaining; false otherwise.
bool game::teamBEmpty() const
{
    return B->ships.getSize() < 1;
}



//   Processes the action queue for all ships.
//   Iterates over each ship in the action queue. For each ship that is not marked as destroyed,
//   executes its actions (e.g., movement, attack) and updates the battlefield after the action.
//   If an exception occurs during processing, it is caught and logged.

void game::actionQueue() {
    while (queue.getSize() > 0) {
        try {
            Ship *ship = queue.front();
            if (ship != nullptr && !ship->isDestroyed()) {
                ship->actions(grid, Width, Height, *battlefield, *this);
                battlefield->display();
            }
            queue.dequeue();
        }
        catch (const std::exception &e) {
            std::cerr << "Exception in actionQueue: " << e.what() << std::endl;
            break;
        }
    }

    std::cout << "Action queue processing complete. Remaining queue size: " << queue.getSize() << "\n";
}

// get the remaining alive ships from the battlefield and fill the  queue  
void game::fillQueue() {
    queue.clearList();
    for (int i = 0; i < battlefield->getShips().getSize(); ++i) {
        Ship *ship = battlefield->getShips().getNode(i);
        if (!ship->isDestroyed() && ship != nullptr ) {
            queue.enqueue(ship);
        }
    }
}


//   Attempts to respawn ships from the graveyard.
//   Uses random positioning to find an empty cell in the grid to respawn ships that are in the graveyard.
//   Up to a maximum of 2 (can be changed if needed) ships are respawned per call. If a ship cannot be respawned due to occupied cells,
//   a message is output and the ship is skipped.
void game::respawn()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, Width - 1);
    std::uniform_int_distribution<> disY(0, Height - 1);

    std::cout << "deathQueue size = "
        << battlefield->shipGraveYard.getSize() << "\n";

    int shipsRespawned = 0; 
    const int maxShipsToRespawn = 2;

    while (shipsRespawned < maxShipsToRespawn && !battlefield->shipGraveYard.empty())
    {
        try
        {
            Ship* ship = battlefield->shipGraveYard.front();

            if (ship->isDestroyed())
            {
                std::cout << "Ship " << ship->getSymbol()
                    << " is destroyed and cannot be respawned.\n";
                battlefield->shipGraveYard.dequeue();
                continue;
            }

          
            int x, y;
            int attempts = 0;
            const int maxAttempts = 100; 

           
            while (attempts < maxAttempts)
            {
                x = disX(gen);
                y = disY(gen);
                if (grid[y][x] == '0') 
                {
                    break;
                }
                attempts++;
            }

            if (attempts >= maxAttempts)
            {
                std::cout << "Failed to find an empty cell for respawning ship "
                    << ship->getSymbol() << ".\n";
              
                battlefield->shipGraveYard.dequeue();
                continue;
            }

            ship->setShipPosition(x, y);
            grid[y][x] = ship->getSymbol();
            ship->isInDeathQueue = false; 

            std::cout << "Ship " << ship->getSymbol()
                << " respawned at (" << y << ", " << x << ").\n";
            battlefield->shipGraveYard.dequeue();
            shipsRespawned++;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception in respawn: " << e.what() << "\n";
            break;
        }
    }

    if (shipsRespawned > 0)
    {
        std::cout << shipsRespawned << " ship(s) respawned successfully.\n";
    }
    else
    {
        std::cout << "No valid ships were available to respawn.\n";
    }
}




//   Removes dead ships from both teams.
//   Iterates backwards through each team's ship list, removing and deallocating any ship
//   that is either already deleted (nullptr) or marked as destroyed. Also outputs logs indicating
//   which ships have been removed and provides updated counts for each team

void game::removeDeadShipFromTeam()
{
    // Process Team A ships.
    for (int i = A->ships.getSize() - 1; i >= 0; --i)
    {
        Ship* ship = A->ships.getNode(i);
        if (ship == nullptr || ship->isDestroyed())
        {
            if (ship != nullptr)
            {
                std::cout << ship->getType() << " " << ship->getSymbol()
                    << " is getting removed from the game.." << "\n";
            }
            A->ships.deleteNodeAtIndex(i);
            delete ship;
            ship = nullptr; 
        }
    }

    // Process Team B ships.
    for (int i = B->ships.getSize() - 1; i >= 0; --i)
    {
        Ship* ship = B->ships.getNode(i);
        if (ship == nullptr || ship->isDestroyed())
        {
            if (ship != nullptr)
            {
                std::cout << ship->getType() << " " << ship->getSymbol()
                    << " is getting removed from the game.." << "\n";
            }
            B->ships.deleteNodeAtIndex(i);
            delete ship;
            ship = nullptr;
        }
    }

    std::cout << "Team A size: " << A->ships.getSize() << "\n";
    std::cout << "Team B size: " << B->ships.getSize() << "\n";
}



//   Retrieves the team associated with a given symbol.
//   Returns a pointer to Team A or Team B depending on the uppercase version of the provided team symbol.
//   If an invalid symbol is provided, outputs an error message and returns nullptr.
Team *game::getTeam(char teamSymbol) const
{
    switch (toupper(teamSymbol))
    {
    case 'A':
        return A;
    case 'B':
        return B;
    default:
        std::cerr << "Invalid team symbol: " << teamSymbol << "\n";
        return nullptr;
    }
}

//   Overloads the stream insertion operator for the game.

//   Outputs the game state including current iterations, and displays the battlefield.
//   Provides a standardized way to output game state information using standard I/O streams.
//    os: The output stream to write the game state to.
//    g: The const reference to the game object.
//   returns a reference to the output stream that was used.
//  

std::ostream &operator<<(std::ostream &os, const game &g)
{
    os << "Game state:\n";
    os << "Iterations left: " << g.iterations << "\n";
    g.displayBattleField();
    return os;
}

// used in testing, just to remove a ship from all queues in the game if it exits there


void game::removeFromQueues(Ship *ship)
{
    for (int i = 0; i < A->ships.getSize(); ++i)
    {
        if (A->ships.getNode(i) == ship)
        {
            std::cout << "Ship of type " << A->ships.getNode(i)->getType() << " is getting removed from all queues game.." << "\n";
            A->ships.deleteNodeAtIndex(i);
        }
    }

    for (int i = 0; i < B->ships.getSize(); ++i)
    {
        if (A->ships.getNode(i) == ship)
        {
            std::cout << "Ship of type " << B->ships.getNode(i)->getType() << " is getting removed from all queues game.." << "\n";
            B->ships.deleteNodeAtIndex(i);
        }
    }

    for (int i = 0; i < battlefield->getShips().getSize(); ++i)
    {
        if (battlefield->getShips().getNode(i) == ship)
        {
            std::cout << "Ship of type " << battlefield->getShips().getNode(i)->getType() << " is getting removed from all queues game.." << "\n";
            battlefield->getShips().deleteNodeAtIndex(i);
        }
    }

    for (int i = 0; i < queue.getSize(); ++i)
    {
        if (queue.getNode(i) == ship)
        {
            std::cout << "Ship of type " << queue.getNode(i)->getType() << " is getting removed from all queues game.." << "\n";
            battlefield->getShips().deleteNodeAtIndex(i);
        }
    }
}