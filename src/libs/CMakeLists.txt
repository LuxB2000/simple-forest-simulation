add_library(
	Tree tree.cpp
)

add_library(
	World world.cpp
)
target_link_libraries(World Tree)
