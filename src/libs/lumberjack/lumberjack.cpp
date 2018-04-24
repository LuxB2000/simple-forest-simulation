#include "lumberjack.h"

// opertor on lumberjack_t
std::ostream& forest::operator<<(std::ostream& os, const forest::lumberjack_t l)
{
	os << "Lumberjack @{" +
				std::to_string(l.positions[0]) + "," +
				std::to_string(l.positions[1]) +
			"} R=" + std::to_string(l.ressources) ;
	return os;
}

forest::Lumberjack::Lumberjack(const lumberjack_t &data) : Character<forest::lumberjack_t>(data)
{

}

forest::Lumberjack::Lumberjack(const Lumberjack &l) : Character<forest::lumberjack_t>(l.GetInfo())
{

}

void
forest::Lumberjack::Moving(positions_t to)
{
	this->moving_sig(this->GetInfo().positions, to, this->GetID());
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
