#include "libs/world.h"
#include "libs/tree.h"
#include "libs/lumberjack/lumberjack.h"

using namespace forest;

int main(){

	std::unique_ptr<World> world (new World(5)); // size of the squared map
	tree_t a_tree;
	a_tree.positions = {0,0}; // position on the landsckape
	a_tree.age = 0;
	lumberjack_t a_lumberjack;
	a_lumberjack.positions = {2,2};
	a_lumberjack.ressources = 0;
	world->AddCharacter(CharacterE::tree, &a_tree);
	world->AddCharacter(CharacterE::lumberjack, &a_lumberjack);

	auto pop = world->StartWorld(5); // run the simulation of the world with 5 periodes of time. 
	std::cout << "At the end we have " << pop.trees.size() << " trees." << std::endl;
	for(auto tree: pop.trees )
	{
		std::cout << tree << std::endl;
	}
	std::cout << "The lumberjack is: " << pop.lumberjacks[0] << std::endl;

	std::cout<< " That's all folks" << std::endl;
	return EXIT_SUCCESS;

}
