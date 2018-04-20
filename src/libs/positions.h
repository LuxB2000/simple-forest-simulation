#ifndef POSITIONS__H
#define POSITIONS__H

#include <iostream>
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
	// comparison of two positions
	const bool operator==(const positions_t& rhs) const { return std::equal(_pos.begin(), _pos.end(), rhs._pos.begin()); }
	// addition of two positions
	positions_t operator+(const positions_t& rhs)
	{
		positions_t add(_pos);
		std::transform(_pos.begin(), _pos.end(), rhs._pos.begin(), 
                   add._pos.begin(), std::plus<pos_t>());
		return add;
	}
	// return true if ANY position in _pos is smaller than comp
	bool operator<(const pos_t comp){
		for(auto p: _pos)
		{
			if(p<comp){
				return true;
			}
		}
		return false;
	}
	// return true if ANY position in _pos is bigger than comp
	bool operator>(const pos_t comp){
		for(auto p: _pos)
		{
			if(p>comp){
				return true;
			}
		}
		return false;
	}
	//const bool operator==(const positions_t& rhs) const { return std::equal(_pos.begin(), _pos.end(), rhs._pos.begin()); }
	auto size(){return _pos.size();}
	std::ostream& operator<<(std::ostream& os){ return os;}
};
const inline std::ostream& operator<<(std::ostream& os, positions_t p)
{
	os << "[ ";
	for(auto pos : p._pos ){
		os << pos << " ";
	}
	os << "]";
	return os;
}

};

#endif
