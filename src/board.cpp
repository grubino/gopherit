#include "board.h"
#include <boost/tuple.hpp>
#include <boost/bind.hpp>
#include <set>
#include <algorithm>

board::board(size_t size) : m_size(size) {
	for(size_t i = 0; i < size; ++i) {
		for(size_t j = 0; j < size; ++j) {
			m_grid[i][j] = EMPTY;
		}
	}
}

void board::place_stone(size_t x, size_t y, board::point_state color) {
	std::set<point>::const_iterator it =
		m_legal_moves.find(boost::make_tuple(x, y));
	if(it != m_legal_moves.end()) {
		m_legal_moves.erase(it);
		std::remove_if(m_legal_moves.begin(),
									 m_legal_moves.end(),
									 boost::bind(&board::_test_legality,
															 this,
															 _1,
															 opposite(color)));
	} else {
		throw std::runtime_error("cheater!");
	}
}

bool board::_test_legality(const board::point& p,
													 board::point_state color) {

	mp::cpp_int hypothesis_board_id(get_board_id(m_grid));
	hypothesis_board_id	+=
		(mp::cpp_int(color)) << (p.get<0>() + p.get<1>());
	
	if(m_hist.count(hypothesis_board_id) > 0) {
		return false;
	}
	return true;
}

const std::set<point>& get_legal_moves() const {
	return m_legal_moves;
}

mp::cpp_int board::get_board_id(const board::board_grid& grid,
																size_t size) {
	mp::cpp_int id(0);
	for(size_t i = 0; i < size; ++i) {
		for(size_t j = 0; j < size; ++j) {
			id += (mp::cpp_int(grid[i][j]) << (i + j));
		}
	}
	return id;
}

















