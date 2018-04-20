#ifndef POPULATION_INFO__H
#define POPULATION_INFO__H

#include <vector>
#include "positions.h"

namespace forest{
/*
 * Character types usesd in the AddCharacter with the world.
 */
enum CharacterE{
	tree, man
};

// a Character is defined by an id and a position.
struct character_t{
	positions_t positions;
	std::string uid;
};

// a tree has an age
struct tree_t : character_t{
	unsigned long age;
};
std::ostream& operator<<(std::ostream& os, const forest::tree_t t);

struct population_info_t{
	std::vector<tree_t> trees;
};


}

#endif
