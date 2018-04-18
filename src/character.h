#ifndef CHARACTER__H
#define CHARACTER__H

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <unordered_map>

namespace character_client{
enum CharacterE{
	tree, man
};
}

namespace forest{
/*
 * information relative to a character
 */
// a character has a position on the map
using positions_t = std::vector<int>;
using uid_t = boost::uuids::uuid;
// a character is defined by an id and a position
struct character_t{
	positions_t positions;
	std::string uid;
};
std::ostream& operator<<(std::ostream& os, const character_t c)
{
	os << "AbstractCharacter @{" +
				std::to_string(c.positions[0]) + "," + 
				std::to_string(c.positions[1]) +
			"}";
	return os;
}
/**
 * Represent any individual acting in the world.
 * This class contains pure virtual functions.
 */
template<class CharacterT>
class Character{
public:

	// implement it owns destructor
	static void delCharacter (Character<CharacterT>* c){
		std::string uid = (c)->GetID();
		std::cout<< "Deleting Character" << uid << std::endl;
		delete c;
	};
	// output signal to send information to world
	boost::signals2::signal<void(character_client::CharacterE, CharacterT*)> add_sig;

	// default constructor
	Character(const CharacterT& data): m_uid(boost::lexical_cast<std::string>(boost::uuids::random_generator()()))
	{
		this->m_data = CharacterT (data);
		this->m_data.uid = this->m_uid;
	}
	// for comparison == with uid
	/*Character(const std::string uid){
		this->m_uid = uid;
		this->m_data.uid = uid;
	}*/
	// copy constructor
	// Note: the UID is never copied, a copy constructor creates a new character
	// with same data but with a different ID, so `==' returns false.
	Character(const Character& c): m_uid(boost::lexical_cast<std::string>(boost::uuids::random_generator()()))
	{
		this->m_data = CharacterT(c.GetInfo());
	}
	// destructor
	~Character(){
	}


	//get the id of the character
	// returns lvalue
	const std::string& GetID() const &{
		return this->m_uid;
	}
	// returns rvalue
	//const std::string GetID() const &&{
	//	return std::move(this->m_uid);
	//}
	// get the information relative to the character
	virtual const CharacterT& GetInfo() const & { return m_data; } //lvalue
	virtual const CharacterT GetInfo() const && { return m_data; } // rvalue

	// compare two characters based on the ID
	bool operator==(const Character &charact){
		return std::strcmp(this->GetID()==charact.GetID()) == 0;
	}
	/*
	friend bool operator==(const Character& c, const std::string &uid){
		return c->GetID() == uid;
	}
	*/

	// each character has his own way to implement how the time goes.
	virtual void TimePassed() = 0;
	// each character has his own way to implement his own print
	virtual std::ostream& operator<<(std::ostream& os) = 0;
	virtual std::string Print() & = 0;


protected:
	std::string m_uid; // the unique id of the object
	CharacterT m_data; // the data defining a particular character
};

/*
 * The information relative to the Tree
 */
struct tree_t : character_t{
	unsigned long age;
};
std::ostream& operator<<(std::ostream& os, const tree_t t)
{
	os << "Tree @{" + 
				std::to_string(t.positions[0]) + "," + 
				std::to_string(t.positions[1]) +
			"} age:" + std::to_string(t.age); 
	return os;
}

class Tree: public Character<tree_t>{
public:
using TreeT = std::unique_ptr<Tree, void(*) (Tree*)>;
using trees_vector_t = std::unordered_map<std::string, TreeT>;
	Tree(const tree_t& data) ;
	Tree(const Tree& t) ;
	//Tree(const std::string uid) : Character(uid){}
	// it implements it owns depstructor
	static void delCharacter (Tree* t);
	~Tree();

	// Virutal functions
	// time passed
	void TimePassed();
	// print the tree information
	virtual std::ostream& operator<<(std::ostream& os);
	virtual std::string Print() &;

private:
};
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
std::ostream& forest::Tree::operator<<(std::ostream& os){
	os <<
		"{[" << 
			this->m_data.positions[0] << "," << this->m_data.positions[1] << "], " <<
			"age: " << this->m_data.age << 
		"}";
	return os;
}
std::string forest::Tree::Print() &
{
	return 	"{[" +
			std::to_string(this->m_data.positions[0]) + "," + std::to_string(this->m_data.positions[1]) + "], " +
			"age: " + std::to_string(this->m_data.age) +
		"}";
}
void forest::Tree::delCharacter (Tree* t) {
	std::cout<< "It was a lovely tree." << std::endl;
	delete t;
};
#endif
