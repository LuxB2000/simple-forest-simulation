#ifndef POSITIONS__H
#define POSITIONS__H

#include <vector>

namespace forest{

// a character has a position on the map
//using positions_t = std::vector<int>;
struct positions_t {
	using pos_t = int;
	std::vector<pos_t> _pos;
	positions_t() : _pos(){}
	positions_t(const std::vector<int> & p) : _pos(p){}
	positions_t(const pos_t p1, const pos_t p2 ) : _pos({p1,p2}){}
	const auto operator[](const pos_t n) const { return _pos[n];}
	inline bool is_equal(const positions_t& rhs){ return std::equal(_pos.begin(), _pos.end(), rhs._pos.begin());}
	const bool operator==(const positions_t& rhs) const { return std::equal(_pos.begin(), _pos.end(), rhs._pos.begin()); }
	//const bool operator==(const positions_t& rhs) const { return std::equal(_pos.begin(), _pos.end(), rhs._pos.begin()); }
	auto size(){return _pos.size();}
};

};

#endif
