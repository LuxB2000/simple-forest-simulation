#ifndef MAP__H
#define MAP__H

#include "../character.h"

namespace map_forest{
// the map stocking which characters below to which coordinates
using list_charact_t = std::vector<std::string>;

/*
 * The map of the world.
 * You can access to the list of Ids at a position.
 * You can add an id and remove one.
 */
struct map_t{
	std::vector<list_charact_t> _map;
	int _mapSz;
	forest::list_positions_t _neigh1;
	map_t(int sz = 0) : 
		_mapSz(sz),
		_neigh1( // constant, used to compute a local neighborhood
			{
				{0, 1},{ 1, 0},
				{0,-1},{-1, 0},
				{1, 1},{-1, 1},
				{1,-1},{-1,-1}
			})
	{
		_map.resize(_mapSz * _mapSz);
		for(auto it = _map.begin(); it != _map.end(); it++)
		{
			it->resize(0);
		}
	}
	// get the size of the map
	const forest::positions_t GetSizes() const {return {_mapSz,_mapSz}; }
	// compute the position in the _map based on position_t
	inline const int _compute_coord(forest::positions_t pos) const
	{
		return pos[0] + pos[1] * _mapSz;
	}
	// Set a character in the map
	void SetCharacter(forest::positions_t pos, std::string uid){
		_map[_compute_coord(pos)].push_back(uid);
	}
	// remove a character from the map
	void RemoveCharacter(forest::positions_t pos, std::string uid)
	{
		_map[_compute_coord(pos)].erase(
			std::remove(
				_map[_compute_coord(pos)].begin(),
				_map[_compute_coord(pos)].end(),
				uid),
			_map[_compute_coord(pos)].end()
		);;
	}
	// get the list of IDs at a position
	const list_charact_t GetCharacters(forest::positions_t pos) const 
	{
		return _map[_compute_coord(pos)];
	}
	// get a neighborhood of a position
	forest::list_positions_t GetNeighborhood(forest::positions_t pos)
	{
		forest::list_positions_t neigh;
		neigh.resize(0);
		for(auto n: _neigh1)
		{
			auto nn = pos + n;
			if(!(nn<0) && !(nn>(_mapSz-1)))
			{
				neigh.push_back(nn);
			}
		}
		return neigh;
	}
};// end struct map


} //end namespace
#endif
