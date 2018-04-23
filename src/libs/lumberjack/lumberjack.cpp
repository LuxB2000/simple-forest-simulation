#include "lumberjack.h"

forest::Lumberjack::Lumberjack(const lumberjack_t &data) : Character<forest::lumberjack_t>(data)
{

}

forest::Lumberjack::Lumberjack(const Lumberjack &l) : Character<forest::lumberjack_t>(l.GetInfo())
{

}

void
forest::Lumberjack::TimePassed()
{

}

std::string
forest::Lumberjack::Print() &
{
	std::string msg;
	return msg;
	
}
