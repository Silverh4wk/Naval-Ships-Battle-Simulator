#include <iostream>
#include <sstream>
#include <random>




// Abstract base object for Ships 
class Ship
{
protected:
     int ShipPositionX = 0;
     int ShipPositionY = 0;
private:
    int LIVES = 3;
    char SYMBOL =  '-';
    std::string TYPE = "Ship";

public:
    virtual void actions() const = 0;
    //getters
    char getSymbol()const {return SYMBOL;}
    
    int getShipPositionX()const {return ShipPositionX;}
    
    int getShipPositionY()const {return ShipPositionY;}
    
    bool getLives()const { return LIVES <1 ;}
    
    std::string getType()const {return TYPE;}

     virtual ~Ship() = default;
};


//cant move to a location that contains another battleship
class MovingShip : public Ship
{
private:
    
public:
    virtual void move(int X, int Y)  = 0;
};


class ShootignShip : public Ship
{
private:
    /* data */
public:
    virtual void fire(int X, int Y) = 0;
};

class SeeingrRobot: public Ship
{
private:
    /* data */
public:
      virtual void look(int X, int Y)  = 0;
};



class RamShip: public Ship
{
private:
    
public:
    virtual void ram(int x, int y) = 0;
};



/*
--------------------------------------------------------------------
 
 battleship --: 
 it can shoot, it can move, it can see
 looks at its current pos then decide to move
  move once then shoot twice at random positions, x+y is 5 blocks 
 cant move to a location that contain another Ship
 if shoot hit >4 ---> upgrade to destroyer 

--------------------------------------------------------------------
*/
class BattleShip:
                 public MovingShip,public ShootignShip,public SeeingrRobot // public seeingrobot : public movingship :public shootignship
{
private:
int SHIPSDESTROYED = 0;   
public:
    BattleShip(/* args */);
    void upgrade();

};

/*
--------------------------------------------------------------------
 Cruiser --:
 it can look it can move and it can ram
 will not shoot at all and will terminate ships at its path
 in each turn it looks at 3x3 window, it will move to one of them
 if the cruiser kills 3 of them, cruiser ---> upgrade to destroyer 

 --------------------------------------------------------------------
*/

class cruiser:
             public MovingShip,public RamShip
{
private:
    int SHIPSDESTROYED;
public:
    cruiser(/* args */);

};

/*
--------------------------------------------------------------------
 Destroyer --:
 it can move it can shoot it can ram it can look 
 if kill = 3, upgrades to supership
 --------------------------------------------------------------------
*/
class Destroyer:
     public MovingShip,public ShootignShip,public SeeingrRobot,public RamShip
{
private:
    /* data */
public:
    Destroyer(/* args */);

};
/*
--------------------------------------------------------------------                                                           
 Frigate --:
 it can shoot at neighbouring cells 1x1
 and when it shoots it clock wise direction 
 if kill = 3, upgrades to corvette
--------------------------------------------------------------------
*/
class Frigate: 
    public ShootignShip
{
private:
    /* data */
public:
    Frigate(/* args */);

};

/*
--------------------------------------------------------------------
Corvette --:
cant move, shoot at random neighbour cells
--------------------------------------------------------------------
*/
class corvette:
    public ShootignShip
{
private:
    /* data */
public:
    corvette(/* args */);
   
};

/*
--------------------------------------------------------------------
Amphibious --:
land and water
battleship behaviour
 if kill =4, upgrades to SUPERSHIP 
 -------------------------------------------------------------------
*/
class Amphibious :public BattleShip
{
private:
    int SHIPSDESTROYED = 0;
public:
    Amphibious (/* args */);
  
};
/*
--------------------------------------------------------------------
SuperShip --:
it can do everything 
 it move like a cruiser, killing everything in its way
shoots randomly at 3 locations in the same turn
--------------------------------------------------------------------
*/
class SuperShip
{
private:
    /* data */
public:
    SuperShip(/* args */);
    ~SuperShip();
};


