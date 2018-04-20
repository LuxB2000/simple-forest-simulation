#ifndef CHARACTER__H
#define CHARACTER__H

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <unordered_map>

#include "positions.h"
/**
 * A Character is a generic element of the simulation. It is defined by:
 * 	- having an id
 *  - having a physical position on the map
 *  - interact with world with creation (`add_sig`) or suppression (`del_sig` @TODO) of other Charcter
 *  - can be informed that the time passed time is clicking with `TimePassed` function
 */

namespace forest{
/*
 * Character types usesd in the AddCharacter with the world.
 */
enum CharacterE{
	tree, man
};
/*
 * information relative to a character
 */
// a Character is defined by an id and a position.
struct character_t{
	positions_t positions;
	std::string uid;
};
// print the information relative to a character.
/*std::ostream& operator<<(std::ostream& os, const character_t c)
{
	os << "Character @{" +
				std::to_string(c.positions[0]) + "," + 
				std::to_string(c.positions[1]) +
			"}";
	return os;
}*/
/**
 * Represent any individual acting in the world.
 * This class contains pure virtual functions.
 */
template<class CharacterT>
class Character{
public:

	// output signal to send information to world regards a creation of an other character.
	boost::signals2::signal<void(CharacterE, CharacterT*)> add_sig;

	// default constructor
	Character(const CharacterT& data): m_uid(boost::lexical_cast<std::string>(boost::uuids::random_generator()()))
	{
		this->m_data = CharacterT (data);
		this->m_data.uid = this->m_uid;
	}
	// copy constructor
	// Note: the UID is never copied, a copy constructor creates a new character
	// with same data but with a different ID, so `==' returns false.
	Character(const Character& c): m_uid(boost::lexical_cast<std::string>(boost::uuids::random_generator()()))
	{
		this->m_data = CharacterT(c.GetInfo());
	}

	//get the id of the character
	// returns lvalue
	const std::string& GetID() const &{
		return this->m_uid;
	}
	// get the information relative to the character
	virtual const CharacterT& GetInfo() const & { return m_data; } //lvalue
	virtual const CharacterT GetInfo() const && { return m_data; } // rvalue

	// compare two characters based on the ID
	bool operator==(const Character &charact){
		return std::strcmp(this->GetID()==charact.GetID()) == 0;
	}

	// PURE VIRTUAL FUNCTIONS
	// each character has his own way to implement how the time goes.
	virtual void TimePassed() = 0;
	// print
	virtual std::string Print() & = 0;


protected:
	std::string m_uid; // the unique id of the object
	CharacterT m_data; // the data defining a particular character
};

}

#endif
