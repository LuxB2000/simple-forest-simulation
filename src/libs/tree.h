#ifndef TREE__H
#define TREE__H

#include "character.h"

namespace forest{
/*
 * The information relative to the Tree
 */
struct tree_t : character_t{
	unsigned long age;
};
std::ostream& operator<<(std::ostream& os, const forest::tree_t t);

class Tree: public Character<tree_t>{
public:
using TreeT = std::unique_ptr<Tree, void(*) (Tree*)>;
using trees_vector_t = std::unordered_map<std::string, TreeT>;
	Tree(const tree_t& data) ;
	Tree(const Tree& t) ;
	// the smart pointer comes with his own delete 
	static void TreeDel (Tree* t);
	~Tree();
	

	// Virutal functions
	// time passed
	void TimePassed();
	// print the tree information
	virtual std::string Print() &;

private:
};
}
#endif
