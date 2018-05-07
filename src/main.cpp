#include "libs/world.h"
#include "libs/tree/tree.h"
#include "libs/lumberjack/lumberjack.h"

using namespace forest;

int main(){

	std::unique_ptr<World> world (new World(5)); // size of the squared map
	tree_t a_tree;
	tree_t an_other_type_of_tree;
	an_other_type_of_tree.positions = {4,4};
	an_other_type_of_tree.characteristics.growing_rate = 1.5;
	lumberjack_t a_lumberjack;
	a_lumberjack.positions = {2,2};
	a_lumberjack.ressources = 0;
	world->AddCharacter(CharacterE::tree, &a_tree);
	world->AddCharacter(CharacterE::lumberjack, &a_lumberjack);

	auto pop = world->StartWorld(20); // run the simulation of the world with 20 periodes of time. 
	std::cout << "At the end we have " << pop.trees.size() << " trees." << std::endl;
	for(auto tree: pop.trees )
	{
		std::cout << tree << std::endl;
	}
	std::cout << "The lumberjack is: " << pop.lumberjacks[0] << std::endl;

	std::cout<< " That's all folks" << std::endl;
	return EXIT_SUCCESS;

}
