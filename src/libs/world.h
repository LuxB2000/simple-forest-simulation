#ifndef WORLD__H
#define WORLD__H

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "tree.h"
#include "map.h"
#include "lumberjack/lumberjack.h"

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
/*
struct population_info_t{
	std::vector<forest::tree_t> trees;
};
*/
	// constructor
	World(int N=10);
	
	/*
	 * Run the simulation for a maximal number of epoch.
	 * Returns a population.
	 */
	population_info_t StartWorld(int max_epoch=10) const;

	// getters
	int GetMapSize() { return this->m_mapSz; }
	long GetNumberOfCharacters() { return this->GetNumberOfTrees() + this->GetNumberOfLumberjacks(); }
	long GetNumberOfTrees() { return this->m_population.trees.size(); }
	long GetNumberOfLumberjacks() { return this->m_population.lumberjacks.size();}
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
	 * Get all the coordinates of a surronding position.
	 */
	list_positions_t GetNeighborhood(positions_t);
	/*
	 * Get population info of all the neighborhoods of a specific position.
	 * param int area: define the area for the neight.
	 * area = 0 -> got only on the position
	 * area = 1 -> got only the first-neighborhood
	 * area = 1.5 -> got the position AND the first-neighborhood // @TODO
	 */
	population_info_t GetNeighborhoodPopulationInfo(positions_t, float area=1.0);
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
	/*
	 * Move a Character from a position to an other,
	 * update the map and population.
	 * WARNING: only Lumberjack can move for now
	 */
	void MoveCharacter(std::string uid, positions_t from, positions_t to );

private:
	int m_mapSz;

	using LumberjackT = std::unique_ptr<Lumberjack, void(*) (Lumberjack*)>;
	using lumberjack_vector_t = std::unordered_map<std::string, LumberjackT>;
	struct population_t{
		Tree::trees_vector_t trees;
		lumberjack_vector_t lumberjacks;
	};
	// population on the world
	population_t m_population;

	// the time is a signal calling the character `TimePassed' function
	using time_signal_t = boost::signals2::signal<void()>;
	time_signal_t m_global_time;

	
	// the map
	map_forest::map_t m_map;

};

}
#endif
