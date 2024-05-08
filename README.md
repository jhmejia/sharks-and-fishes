# Shark and Fish Simulation

## Description:

This program simulates a grid of fish and sharks. The fish and sharks move around the grid and breed and die based on certain rules. The program reads in a configuration file and a grid file and simulates the grid for a certain number of generations. The program can also be run in verbose mode to see the grid at each generation.

## Usage: 

### For OpenMP version:

`make`

./simulation <config> [-v]

- config: The configuration file that contains the parameters for the simulation
- -v: Optional flag to run the simulation in verbose mode (will output the grid at each generation to stdout and to a file)
Example: `./simulation config.txt -v`

### For MPI version:

`make mpi`

`mpiexec -np <num_processes> ./mpi_simulation <config> [-v]`
OR `./run_mpi.sh <num_processes> <config> [-v]`


## Clean:

`make clean`

(This will remove both the OpenMP and MPI executables and object files)


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

### Notes:

- This doesn't support much higher than a 100x100 grid due to the memory constraints of the stack (segmentation fault)

- The program will output the grid at each generation to a file called `output.txt` if the verbose flag is used

