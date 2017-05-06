# Cellular-Automaton

A program showing the behavior of a cellular automaton, based on simple rules :

- each pixel is a fighter that have a certain ammount of health points and force points
- 2 teams of cells (red and yellow) are generated randomly (same number of fighters but the force and the health of each fighter is random)
- each frame, each fighter picks one pixel at random among the 8 surrounding him
- if the pixel chosen is empty, then he divides himself in the empty cell but both new cells have half the health and half the force of the original cell.
- if the pixel chosen is a fighter from the opposing team, each cell will deal the difference of their respective force to the ennemy (so the best cell will stay intact)
- if one cell dies, the other one that won the fight divide itself in this cell with half its original power.
- the cells that are still alive and that fought this round are rewarded with some health and some extra force
- all the cells are ageing so they lose force as well as health points.

Depending on the coefficients: maxHealth, maxForce, healthReward, forceReward, splitFactor and ageFactor, we can obeserve pretty cool behaviors.
There are two teams : red and yellow : the darker the color is, the fewer health the pixel has.
