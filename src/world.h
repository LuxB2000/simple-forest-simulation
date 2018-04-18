#ifndef WORLD__H
#define WORLD__H

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "character.h"


namespace forest{
/*
 * The World 
 * 	- records the events,
 * 	- maintains the corrent data 
 * 	- informs about the state of the map
 * 	- informs about the clicking of the time
 */
class World{
public:


// some type
struct population_info_t{
	std::vector<forest::tree_t> trees;
};
	// constructor
	World(int N=10);
	
	/*
	 * Run the simulation for a maximal number of epoch.
	 * Returns a population.
	 */
	population_info_t StartWorld(int max_epoch=10) const;

	// getters
	int GetMapSize() { return this->m_mapSz; }
	long GetNumberOfCharacters() { return this->GetNumberOfTrees(); }
	long GetNumberOfTrees() { return this->m_population.trees.size(); }
	/*
	 * Ask the global population
	 * Return the global population as a structur of pointer to the different objects.
	 */
	//population_t& GetPopulation() { return this->m_population; }
	/*
	 * Ask information about the world.
	 * Returns a structur containing data about the all the characters in the world.
	 */
	population_info_t GetPopulationInfo() const;
	/*
	 * Ask information about a coordinate on the map.
	 * Return a local population;
	 */
	population_info_t GetLocalPopulationInfo(positions_t) const;
	/*
	 * Add a Character to the world,
	 * usually bind by the characters while they create trees by seeding.
	 */
	void AddCharacter(character_client::CharacterE c_type, const character_t* data );
	/*
	 * Remove a Character to the world.
	 * usually bind by the characters while they cut trees along the world.
	 */
	void RemoveCharacter(character_client::CharacterE c_type, const character_t* data);
	/*
	 * Remove a character based on the uid
	 */
	void RemoveCharacter(std::string uid);

private:
	int m_mapSz;

	struct population_t{
		Tree::trees_vector_t trees;
	};
	// population on the world
	population_t m_population;

	// the time is a signal calling the character `TimePassed' function
	using time_signal_t = boost::signals2::signal<void()>;
	time_signal_t m_global_time;

	// the map stocking which characters below to which coordinates
	using list_charact_t = std::vector<std::string>;
	struct map_t{
		std::vector<list_charact_t> _map;
		int _mapSz;
		map_t(){_map.resize(0); _mapSz=0;}
		map_t(int sz) : _mapSz(sz)
		{
			_map.resize(sz*sz);
			for(auto it=_map.begin(); it!=_map.end(); it++)
			{
				it->resize(0);
			}
		}
		inline const int _compute_coord(positions_t pos) const { return pos[0]+pos[1]*_mapSz;}
		void SetCharacter(positions_t pos, std::string uid){ _map[_compute_coord(pos)].push_back(uid); }
		void RemoveCharacter(positions_t pos, std::string uid){ _map[_compute_coord(pos)].erase(std::remove(_map[_compute_coord(pos)].begin(),_map[_compute_coord(pos)].end(), uid), _map[_compute_coord(pos)].end());; }
		const list_charact_t GetCharacters(positions_t pos) const { return _map[_compute_coord(pos)]; }
		const positions_t GetSizes() const {return {_mapSz,_mapSz}; }
	};
	map_t m_map;

};

}
// constuctor
forest::World::World(int N) : m_mapSz(N){
	this->m_map = map_t(N);
}
// Run the World
forest::World::population_info_t forest::World::StartWorld(int max_epoch) const{
	for(auto epoch=0; epoch<max_epoch; epoch++){
		std::cout << "** epoch " << epoch << " **" << std::endl;
		this->m_global_time(); // time is clicking

	}
	return this->GetPopulationInfo();
}
// Add a Character
void forest::World::AddCharacter(character_client::CharacterE c_type, const character_t* data ){
	// create a specific delete function
	if ( c_type == character_client::CharacterE::tree )
	{
		// convert the data
		tree_t* t_data= (tree_t*)(data); //todo: check
		// smart pointer.
		Tree::TreeT new_t(new Tree(*t_data), forest::Tree::TreeDel);
		// connect the new object with the global time.
		this->m_global_time.connect(boost::bind(&Tree::TimePassed, new_t.get()));
		// let the new object create other objects.
		new_t->add_sig.connect(boost::bind(&World::AddCharacter, this, _1, _2));
		// record the character on the map.
		this->m_map.SetCharacter(t_data->positions, new_t->GetID());
		// insert the new element to the global population
		this->m_population.trees.insert(std::make_pair(new_t->GetID(),std::move(new_t)));
	}
	else if (c_type == character_client::CharacterE::man)
	{
		std::cerr  << "NOT YET IMPLEMENTED" << std::endl;
	}
	else
	{
		std::cerr << "ERROR TYPE UNKNOWN!" << std::endl;
	}
	//if( strcmp(typeid(*data).name(), "tree_t")==0 ){
	//}
}
// removing a character based on the UID
void forest::World::RemoveCharacter(std::string uid)
{
	auto it = this->m_population.trees.find(uid);
	if( it!= this->m_population.trees.end())
	{
		this->m_map.RemoveCharacter(it->second->GetInfo().positions, uid);
		this->m_global_time.disconnect(boost::bind(&Tree::TimePassed, it->second.get()));
		this->m_population.trees.erase(it);
	}

}
forest::World::population_info_t forest::World::GetPopulationInfo() const{
	population_info_t pop_info;
	pop_info.trees.resize(0); // todo: create local function to initiate the population_info_t
	for(auto tree_it= this->m_population.trees.begin(); tree_it!=this->m_population.trees.end(); tree_it++)
	{
		pop_info.trees.push_back(tree_it->second->GetInfo());
	}

	return pop_info;
}

forest::World::population_info_t forest::World::GetLocalPopulationInfo(positions_t pos) const
{
	population_info_t local_pop;
	local_pop.trees.resize(0);
	// find the information on the map
	auto ids = this->m_map.GetCharacters(pos);
	for(auto id : ids){
		auto it = this->m_population.trees.find(id);
		std::cout << "Id: " << id << std::endl;
		if(it!=m_population.trees.end())
		{
			local_pop.trees.push_back(it->second->GetInfo());
		}
	}
	return local_pop;
}
#endif
