#include "tree.h"

// operator on tree_t
std::ostream& forest::operator<<(std::ostream& os, const forest::tree_t t)
{
	os << "Tree @{" + 
				std::to_string(t.positions[0]) + "," + 
				std::to_string(t.positions[1]) +
			"} age:" + std::to_string(t.age) + ", " +
			"height: " + std::to_string(t.height); 
	return os;
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
	this->m_data.height += this->m_data.characteristics.growing_rate;
	// compute a probablity of seeding
	std::uniform_int_distribution<> dis(1, 100);
	auto randn = dis(this->gen);
	if( randn <= this->m_data.characteristics.proba_seeding*100){
		// get the local neighborhood
		auto neigh = this->ask_neigh_sig(this->m_data.positions);
		//std::cout << ">> UID: " << this->GetID() << std::endl;
		//std::cout << "I receive " << std::to_string(neigh->size()) << " potential places for my seed."<<std::endl;
		if(neigh->size() > 0){
			// randomly select a position
			std::uniform_int_distribution<> dis(1, neigh->size()-1);
			auto randn = dis(this->gen);
			//std::cout<<"we choose the position " << randn <<std::endl;
			auto rpos = neigh->at(randn);
			//std::cout << "that is the position " << rpos._pos[0] << ", " << rpos._pos[1] << std::endl;
			// if there is less than 3 trees at the position
			auto local_pop = this->ask_info_pop_sig(rpos);
			if(local_pop->trees.size()<3) // @TODO: make it variable
			{
				// plant the seed there
				this->Seeding(rpos);
			}
		}
	}
	//std::cout << "<<" << std::endl;
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
	//std::cout<< "... Goodbye, you were a lovely tree." << std::endl;
	delete t;
};

void forest::Tree::Seeding(forest::positions_t pos)
{
	tree_t new_t;
	new_t.age = 0;
	new_t.positions = pos;
	new_t.characteristics = this->m_data.characteristics;
	this->add_sig(CharacterE::tree, &new_t);
}
