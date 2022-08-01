#include "state_triplet.h"
#include <iostream>
void state_triplet::set_digit(int row, int column, int num) {
	this->rows[row][num - 1] = 1;
	this->columns[column][num - 1] = 1;
	this->cells[sudoku::get_cell(row, column)][num - 1] = 1;
	clue.at(9 * row + column) = num + '0';
}

void state_triplet::reset_digit(int row, int column, int num) {
	this->rows[row][num - 1] = 0;
	this->columns[column][num - 1] = 0;
	this->cells[sudoku::get_cell(row, column)][num - 1] = 0;
	clue.at(9 * row + column) = '.';
}

void state_triplet::reset() {
	rows = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	columns = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	cells = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	clue = ".................................................................................";
}

void state_triplet::copy(const state_triplet& state_to_copy) {
	std::copy(state_to_copy.rows.begin(), state_to_copy.rows.end(), this->rows.begin());
	std::copy(state_to_copy.columns.begin(), state_to_copy.columns.end(), this->columns.begin());
	std::copy(state_to_copy.cells.begin(), state_to_copy.cells.end(), this->cells.begin());
	this->clue = state_to_copy.clue;
}

bool state_triplet::is_valid(int row, int column, int num) {
	if (!(this->rows[row][num - 1] || this->columns[column][num - 1] || this->cells[sudoku::get_cell(row, column)][num - 1])) {
		return true;
	}
	return false;
}

bool state_triplet::is_valid(int row, int column) {
	contains = rows[row] | columns[column] | cells[sudoku::get_cell(row, column)];
	if (contains.all()) {
		contains = 0;
		return false;
	}
	contains = 0;
	return true;
}

std::string state_triplet::get_clue() {
	return clue;
}

state_triplet::state_triplet() {
}
