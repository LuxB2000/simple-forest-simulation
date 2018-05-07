#include <mettle.hpp>
#include "../src/libs/world/map.h"

using namespace mettle;
using namespace map_forest;

suite<> first("Map Tree suite", [](auto& _){
	_.test("Map creations", [](){
		// default map
		map_t map;
		forest::positions_t expected = {0,0};
		expect(map.GetSizes()==expected, equal_to(true));
		// map with a know size
		auto N=10;
		expected = {N,N};
		map_t map2(N);
		expect(map2.GetSizes()==expected, equal_to(true));
		expect(true, equal_to(true));
	});
	_.test("Set and Get a character",[](){
		std::string uid = "someUID";
		forest::positions_t pos = {1,1};
		map_t map(10);
		map.SetCharacter(pos, uid);
		expect(map.GetCharacters(pos).size(), greater(0));
	});
	_.test("Remove a character",[](){
		std::string uid = "someUID";
		forest::positions_t pos = {1,1};
		map_t map(10);
		map.SetCharacter(pos, uid);
		map.RemoveCharacter(pos, uid);
		expect(map.GetCharacters(pos).size(), equal_to(0));
	});
	_.test("Get Neighborhood", [](){
		map_t map(10);
		forest::positions_t pos = {0,0};
		auto neigh = map.GetNeighborhood(pos);
		expect(neigh.size(), equal_to(3));
		pos = {4,4};
		neigh = map.GetNeighborhood(pos);
		expect(neigh.size(), equal_to(8));
		pos = {9,9};
		neigh = map.GetNeighborhood(pos);
		expect(neigh.size(), equal_to(3));
	});
});
