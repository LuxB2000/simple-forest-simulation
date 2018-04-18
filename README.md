## Introduction
A simple piece of code to simulate forest. So far, the tree are created, could be deleted and get aged. They don't seed yet in the sumlation (However they do in the unit test).
Next version will include: lumberjack and seeding from trees.
## Dependencies:
* CMake: https://cmake.org
* Boost: https://www.boost.org
* Metlle for unit testing: https://jimporter.github.io/mettle
## Build
- `$ mkdir build`
- `$ cmake ..`

To perform unit tests:
- `$ make testing`

To run a simulation
- `$ make`
- `$ ./SimuForest`
