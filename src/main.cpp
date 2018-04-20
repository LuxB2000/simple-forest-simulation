#include "libs/world.h"
#include "libs/tree.h"

using namespace forest;

int main(){

	std::unique_ptr<World> world (new World());
	tree_t a_tree;
	a_tree.positions = {0,0}; // position on the landsckape
	a_tree.age = 0;
	world->AddCharacter(CharacterE::tree, &a_tree);

	auto pop = world->StartWorld(5); // run the simulation of the world with a 
	std::cout << "At the end we have " << pop.trees.size() << " trees." << std::endl;
	for(auto tree: pop.trees )
	{
		std::cout << tree << std::endl;
	}

	std::cout<< " That's all folks" << std::endl;
	return EXIT_SUCCESS;

}
