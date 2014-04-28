#5.2.2 Algorithms

One of the best maze solving algorithms I could find during my research was
the flood fill algorithm[FFILL].  I decided I would implement this algorithm for the
simulator software.

Basically, a flood fill is performed by stepping out a cell at a time from the
center of a maze, and giving each cell a number one greater than the cell
before.  Once this has been completed for the entire maze, the fastest path
can be followed from the start to the finish by simply going to any surrounding
cell that has a value lower than the value of your current cell.

So for the flood fill, I implemented this algorithm:

1. Set all cell values to an impossible value (e.g. -1).
2. Start at the Target cells.
3. Set the target cells to 0, and put 0 into a currentvalue variable.
4. Add any accessible cells to a stack
5. Increment the currentvalue variable
6. Step through the stack one cell at a time, for each:
1.  Set cell’s value to currentvalue.
2. Add any accessible cells with the value -1 to a second stack
7. Once stack is empty, replace with second stack
8. Repeat steps 5 – 8 until the second stack is empty.  This means there
are no more accessible cells with no value in the maze.

Once the maze has its floodfill values set, we can continue with working out
the shortest path through the maze:

1. Start at Starting cell
2. Check all accessible cells’ values
3. Move to accessible cell with lowest value
4. Repeat 2 – 4 until the target cell is reached

The only additional thing I needed during the implementation of this algorithm
was a method of choosing which cell to move to if two adjacent cells have
identical values.  In this algorithm, it makes no difference to the path length,
and either direction will be the same length, so I chose an arbitrary order,
preferring to move left then right then up and lastly down.
