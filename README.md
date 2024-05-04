# Shark Cellular Automata Project

Instructions: 

Sharks and Fishes
Another simple fun example of cellular automata is “Sharks and Fishes” in the sea, each with
different behavioral rules. An ocean could be modeled as a three-dimensional array of cells. Each
cell can hold one fish or one shark (but not both). Fish might move around according to these rules:

If there is one empty adjacent cell, the fish moves to this cell.
If there is more than one empty adjacent cell, the fish moves to one cell chosen at random.
If there are no empty adjacent cells, the fish stays where it is.
If the fish moves and has reached its breeding age, it gives birth to a baby fish, is left in the vacated cell.
Fish die after x generations. The sharks are governed by the following rules:
If one adjacent cell is occupied by a fish, the shark moves to this cell and eats the fish.
If more than one adjacent cell is occupied by the fish, the shark chooses one fish at random, moves to the cell occupied by the fish, and eats the fish.
If there are no fish in adjacent cells, the shark chooses an unoccupied adjacent cell to move to in the same way that fish move.
If the shark moves and has reached its breeding age, it gives birth to a baby shark, which is left in the vacated cell.
If a shark has not eaten for y generations, it dies.
Sharks die after z generations. (y < z and x < z) Write parallel programs to simulate the actions of the sharks and fish as described above. The parameters that are input are the size of the ocean, number of fish, number of sharks, their initial placement in the ocean, breeding ages, and shark starvation time. Adjacent cells do not include diagonally adjacent cells. Therefore, there are six adjacent cells, except for the edges. For every generation, the fishes’ and sharks’ ages are incremented by 1. Your simulation should also take into account currents in the water. Suggested tools are MPI, OpenMP, and CUDA (pick two).