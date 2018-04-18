#include "world.h"
#include "character.h"

using namespace forest;

int main(){

	std::unique_ptr<World> world (new World());
	tree_t a_tree;
	a_tree.positions = {0,0}; // position on the landskape
	a_tree.age = 0;
	world->AddCharacter(character_client::CharacterE::tree, &a_tree);

	World::population_info_t pop = world->StartWorld(2); // run the simulation of the world with a 
	std::cout << "At the end we have " << pop.trees.size() << " trees.";
	std::cout << " The first tree is " << pop.trees[0] << std::endl;

	std::cout<< " That's all folks" << std::endl;
	return EXIT_SUCCESS;

}
