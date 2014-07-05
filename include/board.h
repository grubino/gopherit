#ifndef _BOARD_H_
#define _BOARD_H_

#include <boost/multi_array.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/tuple.hpp>

#include <cmath>

#include <set>

namespace mp = boost::multiprecision;

class board {
	
public:

	enum point_state { EMPTY = 0, WHITE = 1, BLACK = 2 };
	
	typedef boost::multi_array<point_state, 2> board_grid;
	typedef std::set<mp::cpp_int> history;
	typedef boost::tuple<size_t, size_t> point;

	board(size_t size = 19);

	void place_stone(size_t, size_t, point_state);
	const std::set<point>& get_legal_moves() const {
		return m_legal_moves;
	}

	static mp::cpp_int get_board_id(const board_grid&, size_t);

	point_state opposite(point_state color) {
		return abs(signed(color) - 3);
	}

private:

	bool _test_legality(const point&);

	size_t m_size;
	board_grid m_grid;
	history m_hist;
	std::set<point> m_legal_moves;

};

#endif











