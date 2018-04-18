#include "tree.h"

// operator on tree_t
std::ostream& forest::operator<<(std::ostream& os, const forest::tree_t t)
{
	os << "Tree @{" + 
				std::to_string(t.positions[0]) + "," + 
				std::to_string(t.positions[1]) +
			"} age:" + std::to_string(t.age); 
	return os;
}

// compare Tree with string.
inline bool operator==(const std::unique_ptr<forest::Tree>& lhs, const std::string& rhs)
{
	return lhs->GetID() == rhs;
}
inline bool operator==(const std::string& lhs, const std::unique_ptr<forest::Tree>& rhs)
{
	return lhs == rhs->GetID();
}

// constructor
forest::Tree::Tree(const tree_t& data) : Character<forest::tree_t>(data)
{

}
forest::Tree::Tree(const Tree& t) : Character<forest::tree_t>(t.GetInfo())
{

}
// destructor
forest::Tree::~Tree()
{

}
// time passed
void forest::Tree::TimePassed()
{
	this->m_data.age += 1 ;
	// todo: run a seed with a known probablity
	// todo: find correct place
	//tree_t new_tree; new_tree.positions = {1,2}; new_tree.age = 0;
	//this->add_sig(character_client::CharacterE::tree, &new_tree);
}
// printing function
std::string forest::Tree::Print() &
{
	return 	"{[" +
			std::to_string(this->m_data.positions[0]) + "," + std::to_string(this->m_data.positions[1]) + "], " +
			"age: " + std::to_string(this->m_data.age) +
		"}";
}
void forest::Tree::TreeDel (Tree* t) {
	std::cout<< "... Goodbye, you were a lovely tree." << std::endl;
	delete t;
};
