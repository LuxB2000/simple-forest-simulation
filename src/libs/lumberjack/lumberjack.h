#ifndef LUBBERJACK__H
#define LUBBERJACK__H

#include "../character.h"

namespace forest{

/*
 * Lumberjacks kill trees and collect ressources.
 */

class Lumberjack : public Character<lumberjack_t>
{
public:
	Lumberjack(const lumberjack_t &data);
	Lumberjack(const Lumberjack &l);

	// its dedicated delete function, passed as parameter for the unique ptr construction
	static void LumberjackDel(Lumberjack* l){
		std::cout << "I was a lumberjack and that was OK. I slept all night and worked all day." << std::endl;
		delete l;
	}

	void TimePassed();
	std::string Print() &;
};


}
#endif