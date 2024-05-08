# Shark and Fish Simulation

## Description:

This program simulates a grid of fish and sharks. The fish and sharks move around the grid and breed and die based on certain rules. The program reads in a configuration file and a grid file and simulates the grid for a certain number of generations. The program can also be run in verbose mode to see the grid at each generation.

## Usage: 

`make`

./simulation <config> [-v]

- config: The configuration file that contains the parameters for the simulation
- -v: Optional flag to run the simulation in verbose mode (will output the grid at each generation to stdout and to a file)
Example: `./simulation config.txt -v`

## Clean:

`make clean`


## Example Config File
```
8 # Grid size
2 # Shark Breed Age
1 # Shark Starve Generations
12 # Shark Max Age
4 # Fish Breed Age
8 # Fish Max Age
2 # Number of Generations to simulate
10 # number of fish to start with
10 # number of sharks to start with
1 # Current direction (0-6)
1 # Current strength (0-100)
```

## Example Grid File
```
5

0 1 0 0 2
1 0 1 0 0
0 0 2 1 0
0 1 0 0 1
2 0 0 1 0

0 1 0 0 2
1 0 1 0 0
0 0 2 1 0
0 1 0 0 1
2 0 0 1 0

0 1 0 0 2
1 0 1 0 0
0 0 2 1 0
0 1 0 0 1
2 0 0 1 0

0 1 0 0 2
1 0 1 0 0
0 0 2 1 0
0 1 0 0 1
2 0 0 1 0

0 1 0 0 2
1 0 1 0 0
0 0 2 1 0
0 1 0 0 1
2 0 0 1 0
```


