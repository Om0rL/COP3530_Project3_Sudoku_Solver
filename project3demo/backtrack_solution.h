#pragma once
#include "sudoku.h"
#include <bitset>
#include <array>
#include <vector>
#include <iostream>
#include "state_triplet.h"
#include "configuration_set.h"

class backtrack_solution {
private:
	state_triplet state;
	sudoku sudo;
	configuration_set config;
	void set_digit(int row, int column, int num);
	void reset_digit(int row, int column, int num);
public:
	backtrack_solution(sudoku SUDO);
	const sudoku& get_sudo() const;
	bool solve(int row_now, int column_now);
	void solve(configuration_set _config);
	void set_sudoku(sudoku SUDO);
};

