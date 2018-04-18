#ifndef WORLD__H
#define WORLD__H

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "myforest.h"
#include "tree.h"


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
	void AddCharacter(CharacterE c_type, const character_t* data );
	/*
	 * Remove a Character to the world.
	 * usually bind by the characters while they cut trees along the world.
	 */
	void RemoveCharacter(CharacterE c_type, const character_t* data);
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
#endif
