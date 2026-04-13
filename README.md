# Naval Ships Battle Simulator

A naval battle simulator, inspired by the old battleship board game. This project simulates ship-to-ship engagements on a grid, based on the input given in the simulation txt file

--- 
## configuration
---
```
iterations 100
width 10
height 10
Team A 4
Amphibious  *  1
Cruiser  $   4
Destroyer  #   4
Frigate  @    3
Team B 2
Battleship  <  2
Cruiser  >   3
```
### Map Layout
```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 1 0
0 0 0 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 1 1 0 0
0 0 0 0 0 0 0 1 0 0
```
- `0` = Water  
- `1` = Island
  
### Features
- Grid-based naval battle simulation
- Multiple ship types with different stats 
- Text-based output for visualization
- configurable r*eal-time simulation modes 
- Save the simulation onto a txt file for later review if needed

---

## Simulation Rules

The simulation stops when any of the following conditions are met:

1. The number of iterations reaches zero  
2. Only one team remains  
3. Both teams are completely annihilated  

---

## Customization

All parameters in the `game.txt` file are configurable:

- **Ship Symbols**  
  Replace special characters (`*`, `$`, `#`, etc.) to customize ship representations  

- **Ship Counts**  
  Modify the numbers on the right to adjust how many units of each type are deployed  

- **Map Design**  
  - `0` represents open water  
  - `1` represents islands (obstacles)  

---

## Notes

- The Simulation rules can be found inside the simulation for more information on the ships and what they do. 

