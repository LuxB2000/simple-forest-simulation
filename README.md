## Introduction
A simple piece of code to simulate forest.
The initialization requires a tree.
At each epoch, all the trees plants a seed in a random place surounding them.
Next version will include: lumberjack and parameters to define different type of trees.

Original proposal: https://www.reddit.com/r/dailyprogrammer/comments/27h53e/662014_challenge_165_hard_simulated_ecology_the/
## Dependencies:
* CMake: https://cmake.org
* Boost: https://www.boost.org
* Metlle for unit testing: https://jimporter.github.io/mettle
## Build
- `$ mkdir build`
- `$ cmake ..`

To perform all unit tests:
- `$ make testing`

To perform a single unit tests:
- `$ make test-treeT`

To run a simulation
- `$ make`
- `$ ./SimuForest`
