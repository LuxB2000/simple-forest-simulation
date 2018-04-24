#ifndef POPULATION_INFO__H
#define POPULATION_INFO__H

#include <vector>
#include "positions.h"

namespace forest{
/*
 * Character types usesd in the AddCharacter with the world.
 */
enum CharacterE{
	tree, lumberjack
};

// a Character is defined by an id and a position.
struct character_t{
	//character_t(): positions(positions_t(-1,-1)), uid(""){}
	positions_t positions;
	std::string uid;
};

// a tree has an age
struct tree_t : character_t{
	//tree_t() : character_t(), age(0){}
	unsigned long age;
};
// note, implemented in tree.cpp
std::ostream& operator<<(std::ostream& os, const tree_t t);

struct lumberjack_t : character_t{
	int ressources;
};
// note, implemented in lumberjack.cpp
std::ostream& operator<<(std::ostream& os, const lumberjack_t l);

/*
 * Contains a picture of the world
 */
struct population_info_t{
	std::vector<tree_t> trees;
	std::vector<lumberjack_t> lumberjacks;
};


}

#endif
