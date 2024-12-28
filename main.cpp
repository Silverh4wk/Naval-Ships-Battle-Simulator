#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


bool Config(std::string&& filename)
{

struct team 
{
public:
int NumberOfShips = 0;
int NumberOfBattleShip = 0;   char BattleShipSymbol ;
int NumberOfCruiser = 0;      char CruiserSymbol;
int NumberOfDestroyer = 0;    char DestroyerSymbol;  
int NumberOfFrigate = 0;      char FrigateSymbol;  
int NumberOfCorvette = 0;     char CorvetteSymbol;  
int NumberOfAmphibious = 0;   char AmphibiousSymbol;  
int NumberOfSuperShip = 0;    char SuperShipSymbol;  
};




    team A,B;
    int iterations{0} ,
    Height{0}, Width{0};
    



 std::ifstream file{filename, file.in |file.out}; 
 std::string line;
if (!file.is_open())
{
    std::cout << "file couldnt open";
    return false;
}
else
{
  while (std::getline(file,line))
  {
    std::istringstream ss(line); 
    if (line.find("iterations") != std::string::npos)
            {
            ss.ignore(line.find(' ') + 1);
            ss >> iterations;
            std::cout << "Iterations = "<< iterations<< std::endl;
            }
    else if (line.find("width") != std::string::npos)
            {
            ss.ignore(line.find(' ') + 1);
            ss >> Width;
            std::cout <<"Width = "<< Width<< std::endl;
            }
    else if (line.find("height") != std::string::npos)
            {
            ss.ignore(line.find(' ') + 1);
            ss >> Height;
            std::cout << "Height = "<<  Height << std::endl;
            }
    else if(line.find("Team A") != std::string::npos)
    {   
      ss.ignore(7) ;
      int number;
      ss>> number;
      A.NumberOfShips = number;
     std::cout <<"Number of ships assigned to Team A is: "<< A.NumberOfShips << "\n";
    }
    else if(line.find("Team B") != std::string::npos)
    {
       ss.ignore(7) ;
      int number;
      ss>> number;
      A.NumberOfShips = number;
     std::cout <<"Number of ships assigned to Team A is: "<< A.NumberOfShips << "\n";
     std::getline(file,line);
      if (line.find("Battleship") != std::string::npos)
    {
        std::istringstream ss(line);  
        std::string shipType;

        ss >> shipType >> B.BattleShipSymbol >> B.NumberOfBattleShip;  
        std::cout << "Battleship " << B.BattleShipSymbol<< " " << B.NumberOfBattleShip << std::endl;
    }
     
    }    
    else if (isdigit(line[0]) || line[0] == '0') {
            break; // This marks the start of the grid/map
    }
    }

  }

   char** grid = new char*[Height];
    for (int i = 0; i < Height; i++) 
    {
        grid[i] = new char[Width];
    }

    for (auto i = 0; i < Height; i++)
    {
        std::istringstream gridstream(line);
        for (auto j = 0; j < Width; j++)
        {
            gridstream>> grid[i][j];
        }
        if (i<Height)
        {
            std::getline(file,line);
        }  
    }
    file.close();
for (auto i = 0; i < Height; i++)
{
    for (auto j = 0; j<  Width; j++)
    {
        std::cout << grid[i][j] << " ";
    }
    std::cout << "\n";
}

for (int i = 0; i < Height; ++i) {
    delete[] grid[i]; 
}
delete[] grid;
return true; 
}

int main ()
{
    Config("game.txt");
    return EXIT_SUCCESS;
}