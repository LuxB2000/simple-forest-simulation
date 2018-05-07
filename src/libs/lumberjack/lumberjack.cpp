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
	this->moving_sig(this->GetID(), this->GetInfo().positions, to);
}

void forest::Lumberjack::Cutting(std::string uid)
{
	this->cutting_sig(uid);
}

void
forest::Lumberjack::TimePassed()
{
	// find the local neighborhood
	auto neigh = this->ask_neigh_sig(this->GetInfo().positions);
	// @TODO: create a general function in Character
	if(neigh->size() > 0)
	{
		// randomly choose a location
		std::uniform_int_distribution<> dis(1, neigh->size()-1);
		auto randn = dis(this->gen);
		auto rpos = neigh->at(randn);
		// move to the location
		this->Moving(rpos);
		// ask if there is a tree
		auto pop_info = this->ask_info_pop_sig(rpos);
		// TODO: WARNING: NOT SAFE !! If several lumberjacks two can ask for the
		// same tree. Need a confirmation from the world that the tree is well cut.
		if(pop_info->trees.size() > 0)
		{
			tree_t tree_to_cut;
			for(auto tree: pop_info->trees)
			{
				if(tree.age>=3)
				{
					// the first tree is the default one
					if( tree_to_cut.uid.size() <= 0)
					{
						tree_to_cut = tree;
					}
					if( tree_to_cut.height < tree.height ){
						tree_to_cut = tree;
					}
				}
			}
			if( tree_to_cut.uid.size() > 0)
			{
				// if we find a tree to cut, cut the biggest one
				this->Cutting(tree_to_cut.uid);
				this->m_data.ressources += tree_to_cut.height;
			}
		}
	}

}

std::string
forest::Lumberjack::Print() &
{
	std::string msg;
	return msg;
	
}
