#pragma once
#include <bitset>
#include <array>
#include "sudoku.h"
class state_triplet {
private:
	std::array<std::bitset<9>, 9> rows = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::array<std::bitset<9>, 9> columns = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::array<std::bitset<9>, 9> cells = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::string clue = ".................................................................................";
	std::bitset<9> contains = 0;
public:
	void set_digit(int row, int column, int num);
	void reset_digit(int row, int column, int num);
	void reset();
	void copy(const state_triplet& state_to_copy);
	bool is_valid(int row, int column, int num);
	bool is_valid(int row, int column);
	std::string get_clue();
	state_triplet();
};

