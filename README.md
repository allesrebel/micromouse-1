# California Micromouse
This repo contains the code powering Cal Poly SLO IEEE's micromouse.

The microcontroller we are using is the MSP430 and the A\* algorithm.

# Spec
Here contains informatoin regarding our implementation to building up the
micromouse maze and proceeding to run through it.

## Memory Limits
There is 16K for both runtime heap and storing code itself available.

A\* is will require a queue. The build phase of the maze will require a stack
for the last given position. The desired path for A\* will be built as a linked
list.

## Sensors
* 10 sensors for each dir
* use gyro (I^2 * C)
* gyro will provide the amount of distance traveled
* always traversing 16x16 maze:
* 0 -> 255 potential `nodes`
Each `node` is a 18cm x 18cm square in the maze.

## Runs
* all parts of the maze can be accessed by the micromouse
* there's a build phase and a solve phase
The first two runs will be our build phase and our solve phase will be the
third run. The time it takes to build and solve the phase dictate your score
(with the build phase being lesser weight).

#### Run 1 - Safe run
* Build up entirety of maze and store it

#### Run 2 - Optimize
* Find the fastest route
* Delete unneeded `nodes`

#### Run 3 - Score run
* mouse goes to the destination and back to the starting point
* end point will always be a 4x4 node in the center of the wave
    * points: (9, 8), (9, 9), (8, 8), (8, 9)
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
* detect dead end
* building a node automatically (based off gyro-derived distance)
