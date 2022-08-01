#pragma once
#include <vector>
#include <string>
#include <cmath>
class sudoku	{
private:
	std::vector<std::vector<int>> board;
	std::string clues;
public:
	explicit sudoku(std::string clue);
	sudoku();
	std::string get_clue();
	int get_digit(int row, int column);
	void set_clue(std::string clue);
	void set_digit(int row, int column, int num);
	void reset_digit(int row, int column, int num);
	void clear();
	void print_board() const;
	std::vector<std::vector<int>> get_board();
	static int get_cell(int row, int column);
	std::pair<int, int> next_empty(int row, int column);
};

