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
    // ask abt return type after death
public:
    virtual void actions() const = 0;
    virtual void look(int X, int Y)  = 0;;
    virtual void move(int X, int Y)  = 0;;
    virtual void shoot(int X, int Y) = 0;

    //getters
    char getSYMBOL()const {return SYMBOL;}
    
    int getShipPositionX()const {return ShipPositionX;}
    
    int getShipPositionY()const {return ShipPositionY;}
    
    bool getLIVES()const 
    { 
    {
        return LIVES <1 ? false:true;
    }
    }
    
    std::string getTYPE()const {return TYPE;}
};


//cant move to a location that contains another battleship
class movingship : public Ship
{
private:
    
public:
    movingship(/* args */);
    ~movingship();
};


class shootignship : public Ship
{
private:
    /* data */
public:
    shootignship(/* args */);
    ~shootignship();
};

class seeingrobot: public Ship
{
private:
    /* data */
public:
    seeingrobot(/* args */);
    ~seeingrobot();
};



class ramship: public Ship
{
private:
    /* data */
public:
    ramship(/* args */);
    ~ramship();
};




// battleship 
// it can shoot, it can move, it can see
// looks at its current pos then decide to move
//  move once then shoot twice at random positions, max is 5 blocks 
// cant move to a location that contain another Ship
// if shoot hit >4 ---> upgrade to destroyer 


class BattleShip // public seeingrobot : public movingship :public shootignship
{
private:
int SHIPSDESTROYED;   
public:
    BattleShip(/* args */);
    ~BattleShip();
    void upgrade();

};

// it can look it can move and it can ram
// will not shoot at all and will terminate ships at its path
// in each turn it looks at 3x3 window, it will move to one of them
// if the cruiser kills 3 of them, cruiser ---> upgrade to destroyer 

class cruiser
{
private:
    /* data */
public:
    cruiser(/* args */);
    ~cruiser();
};

// it can move it can shoot it can ram it can look 
// if kill = 3, upgrades to supership

class Destroyer
{
private:
    /* data */
public:
    Destroyer(/* args */);
    ~Destroyer();
};
                                                           
// it can shoot at neighbouring cells 1x1
// and when it shoots it clock wise direction 
//if kill = 3, upgrades to corvette

class Frigate
{
private:
    /* data */
public:
    Frigate(/* args */);
    ~Frigate();
};

//cant move, shoot at random neighbour cells

class corvette
{
private:
    /* data */
public:
    corvette(/* args */);
    ~corvette();
};


//land and water
//battleship behaviour
// if kill =4, upgrades to SUPERSHIP 

class Amphibious 
{
private:
    /* data */
public:
    Amphibious (/* args */);
    ~Amphibious ();
};

//it can do everything 
// it move like a cruiser, killing everything in its way
//shoots randomly at 3 locations in the same turn

class SuperShip
{
private:
    /* data */
public:
    SuperShip(/* args */);
    ~SuperShip();
};


