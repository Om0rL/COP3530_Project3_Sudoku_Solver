#pragma once
#include <iostream>
#include <bitset>
#include <array>
#include "sudoku.h"
#include "state_triplet.h"
#include "configuration_set.h"
class backjump_leaf_solution {
private:
	state_triplet state;
	sudoku sudo;
	std::pair<int, int> invalid_pos = { -1, -1 };
	configuration_set config;
	void initialize(sudoku sudo);
	void set_digit(int row, int column, int num);
	void reset_digit(int row, int column, int num);
public:
	backjump_leaf_solution(sudoku SUDO);
	const sudoku& get_sudo() const;
	bool solve(int row_now, int column_now);
	void solve(configuration_set _config);
	void set_sudoku(sudoku SUDO);
};

