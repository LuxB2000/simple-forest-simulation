include_directories(lumberjack)
add_subdirectory(lumberjack)

add_library(
	Tree tree.cpp
)

add_library(
	World world.cpp
)
target_link_libraries(World Tree Lumberjack)
