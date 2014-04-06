# California Micromouse
This repo contains the code powering Cal Poly SLO IEEE's micromouse.

The microcontroller we are using is the MSP430 and the A\* algorithm.

# Spec
Here contains informatoin regarding our implementation to building up the
micromouse maze and proceeding to run through it.

## Sensors
* sensors values for each dir
* use gyro (I^2 * C)
* gyro will provide the amount of distance traveled
* always traversing 16x16 maze:
* 0 -> 255 potential `nodes`

## Runs
* all parts of the maze can be accessed by the micromouse

#### Run 1 - Safe run
* Build up entirety of maze and store it

#### Run 2 - Optimize
* Find the fastest route
* Delete unneeded `nodes`

#### Run 3 - Score run
* mouse goes to the destination and back to the starting point
* end point will always be a 4x4 node in the center of the wave
    * points: (9,8), (9, 9), (8, 8), (8, 9)
* construct a linked list of nodes using the A\* algorithm
  * walk it
  * reverse it
  * walk it again


```C
struct node {
  struct point point;
  enum WALLS walls;
  int distance_to_dest; // manhattan distance
  int heurisitc; // weight
}
```

### Heuristic Algorithm
How do we favor a node?

* penalize a node for turning (straight turns are **always** favored)
* left turn == right turn in terms of weight
* staircase/diagonal turn < left turn

### Misc.
#### Intended Algorithms
* dead end algo
* building a node automatically (based off gyro-derived distance)
