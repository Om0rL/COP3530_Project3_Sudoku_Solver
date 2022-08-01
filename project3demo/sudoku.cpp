#include "sudoku.h"
#include <stdexcept>
#include <iostream>
sudoku::sudoku(std::string clue) {
	set_clue(clue);
}

sudoku::sudoku() {
}

std::string sudoku::get_clue() {
	return clues;
}

int sudoku::get_digit(int row, int column) {
	return board.at(row).at(column);
}

void sudoku::set_clue(std::string clue) {
	clear();
	for (int i = 0; i < 9; i++) {
		board.push_back(std::vector<int>());
		for (int j = 0; j < 9; j++) {
			if (clue.at(i * 9 + j) != '.' && clue.at(i * 9 + j) != '0') {
				board.at(i).push_back(clue.at(i * 9 + j) - '0');
			} else {
				board.at(i).push_back(-1);
			}
		}
	}
	clues = clue;
}

void sudoku::set_digit(int row, int column, int num) {
	board.at(row).at(column) = num;
	clues.at(9 * row + column) = num + '0';
}

void sudoku::reset_digit(int row, int column, int num) {
	board.at(row).at(column) = -1;
	clues.at(9 * row + column) = '.';
}

void sudoku::clear() {
	while (board.size() != 0) {
		board.pop_back();
	}
	clues = "";
}

void sudoku::print_board() const {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << clues.at(9 * i + j) << ' ';
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<int>> sudoku::get_board() {
	return board;
}

int sudoku::get_cell(int row, int column) {
	return row / 3 * 3 + column / 3;
}

std::pair<int, int> sudoku::next_empty(int row, int column) {
	std::pair<int, int> vec2 = { -1, -1 };
	for (size_t j = column; j < 9; j++) {
		if (get_digit(row, j) == -1) {
			vec2.first = row;
			vec2.second = j;
			return vec2;
		}
	}
	for (size_t i = row + 1; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			if (get_digit(i, j) == -1) {
				vec2.first = i;
				vec2.second = j;
				return vec2;
			}
		}
	}
	return vec2;
}
