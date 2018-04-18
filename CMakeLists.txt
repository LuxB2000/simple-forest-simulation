cmake_minimum_required (VERSION 3.8)
project (SimuForest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add src
set (CODE_SRC_PATH ${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CODE_SRC_PATH})

# Unit Tests
# ==========
# include the tests
set (TESTS_SRC_PATH ${CMAKE_SOURCE_DIR}/tests) #todo: use correct variable
set (TESTS_BUILD_PATH ${CMAKE_SOURCE_DIR}/build/tests) #todo: use correct variable
add_subdirectory(${TESTS_SRC_PATH})

# delcare the different tests
set (TESTS "worldT;treeT")
foreach(test ${TESTS})
	add_custom_command(
		OUTPUT ${test}
		COMMAND clang++ -std=c++14 -o ${TESTS_BUILD_PATH}/${test} ${TESTS_SRC_PATH}/${test}.cpp -lmettle -g
	)
endforeach(test ${TESTS})
# create a target to compile and run the unit tests
add_custom_target(
	testing
	COMMAND mettle ./treeT ./worldT # run unit tests
	DEPENDS worldT treeT # ask for compilingn and linking
	WORKING_DIRECTORY ./tests/ # in the build
)

# executable
SET (DEBUG_FLAG "-g")
SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${DEBUG_FLAG}")
add_executable (SimuForest ${CODE_SRC_PATH}/main.cpp )
