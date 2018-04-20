## Introduction
A simple piece of code to simulate forest. So far, the tree are created, could be deleted and get aged. They don't seed yet in the sumlation (However they do in the unit test).
Next version will include: lumberjack and seeding from trees.

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
- `$ make treeT`

To run a simulation
- `$ make`
- `$ ./SimuForest`
