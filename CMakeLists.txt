cmake_minimum_required (VERSION 3.8)
project (SimuForest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add src
set (CODE_SRC_PATH ${CMAKE_SOURCE_DIR}/src)
set (WOLD_BUILD_PATH ${CMAKE_SOURCE_DIR}/build/src/libs) #todo: use correct variable
set (WORLD_SRC_PATH ${CMAKE_SOURCE_DIR}/src/libs) #todo: use correct variable
set (TREE_SRC_PATH ${CMAKE_SOURCE_DIR}/src/libs) #todo: use correct variable
set (LUMBERJACK_SRC_PATH ${CMAKE_SOURCE_DIR}/src/libs/lumberjack)
add_subdirectory(${CODE_SRC_PATH})
include_directories(${WOLRD_SRC_PATH})

# Unit Tests
# ==========
# include the tests
set (TESTS_SRC_PATH ${CMAKE_SOURCE_DIR}/tests) #todo: use correct variable
set (TESTS_BUILD_PATH ${CMAKE_SOURCE_DIR}/build/tests) #todo: use correct variable
add_subdirectory(${TESTS_SRC_PATH})
link_directories(${TEST_SRC_PATH})

# delcare the different tests
set (TESTS "worldT;treeT;mapT;lumberjackT")
foreach(test ${TESTS})
	add_custom_command(
		OUTPUT ${test}
		COMMAND clang++ -std=c++14 -o ${TESTS_BUILD_PATH}/${test} ${TESTS_SRC_PATH}/${test}.cpp ${WORLD_SRC_PATH}/world.cpp ${TREE_SRC_PATH}/tree.cpp ${LUMBERJACK_SRC_PATH}/lumberjack.cpp -lmettle -g
	)
	add_custom_target(
		test-${test}
		COMMAND mettle ./${test}
		DEPENDS ${test}
		WORKING_DIRECTORY ./tests
	)
endforeach(test ${TESTS})
# create a target to compile and run the unit tests
add_custom_target(
	testing
	COMMAND mettle ./treeT ./mapT ./worldT ./lumberjackT # run unit tests
	DEPENDS worldT treeT mapT lumberjackT # ask for compilingn and linking
	WORKING_DIRECTORY ./tests/ # in the build
)

# executable
SET (DEBUG_FLAG "-g")
SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${DEBUG_FLAG}")
add_executable (SimuForest ${CODE_SRC_PATH}/main.cpp )
target_link_libraries(SimuForest World Tree)
