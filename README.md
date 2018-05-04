## Introduction
A simple piece of code to simulate forest on a 2D map.
The initialization start with a tree and a lumberjack.

At each epoch, each tree chooses a random place in its 8-neighborhood, if that place does not already contains three trees, then it plants a seed.

At each epoch, each lumberjack move to one random adjacent position and if there is a tree with age>3, it cuts it and collect the ressources.

Next version will include:  The lumberjacks cut the oldest tree if several trees on the map. Various types of trees and characteristics parsing.

Original proposal: https://www.reddit.com/r/dailyprogrammer/comments/27h53e/662014_challenge_165_hard_simulated_ecology_the/

## Dependencies:
- CMake: https://cmake.org
- Boost: https://www.boost.org
- Metlle for unit testing: https://jimporter.github.io/mettle

## Build
- `$ mkdir build`
- `$ cd build`
- `$ cmake ..`

## Run
To perform all unit tests:
- `$ make testing`

To perform a single unit test:
- `$ make test-${NAME}T`,
where ${NAME} is world, tree, map, lumberjack, example:
- `$ make test-treeT`

To run a simulation of the forest:
- `$ make`
- `$ ./SimuForest`
