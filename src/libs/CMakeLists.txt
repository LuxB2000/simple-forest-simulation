include_directories(tree)
add_subdirectory(tree)

include_directories(lumberjack)
add_subdirectory(lumberjack)

add_library(
	World world.cpp
)
target_link_libraries(World Tree Lumberjack)
