#include "backjump_leaf_solution.h"

backjump_leaf_solution::backjump_leaf_solution(sudoku SUDO) : sudo(SUDO.get_clue()) {
	initialize(sudo);
}

const sudoku& backjump_leaf_solution::get_sudo() const {
	return this->sudo;
}

bool backjump_leaf_solution::solve(int row_now, int column_now) {
	std::pair<int, int> vec2 = sudo.next_empty(row_now, column_now);
	if (vec2.first == -1 && vec2.second == -1) {
		std::cout << std::endl;
		sudo.print_board();
		return true;
	}
	for (int i = 0; i < 9; i++) {
		if (state.is_valid(vec2.first, vec2.second, i + 1)) {
			set_digit(vec2.first, vec2.second, i + 1);
			if (config.show_recursion_count) {
				config.count();
			}
			if (!solve(vec2.first, vec2.second)) {
				if (invalid_pos.first != -1 && invalid_pos.second != -1) {
					reset_digit(vec2.first, vec2.second, i + 1);
					if (!state.is_valid(invalid_pos.first, invalid_pos.second)) {
						return false;
					} else {
						invalid_pos.first = -1;
						invalid_pos.second = -1;
					}
				} else {
					reset_digit(vec2.first, vec2.second, i + 1);
				}
			}
		} else if (i == 8) {
			invalid_pos.first = vec2.first;
			invalid_pos.second = vec2.second;
			return false;
		}
	}
	if (sudo.next_empty(0, 0).first == -1) {
		return true;
	}
	return false;
}

void backjump_leaf_solution::solve(configuration_set _config) {
	config = _config;
	if (config.show_time) {
		config.start();
		solve(0, 0);
		config.end();
		std::cout << "Time elapsed:" << config.get_time_difference() << "ms" << std::endl;
	} else {
		solve(0, 0);
	}
	if (config.show_recursion_count) {
		std::cout << "Total solve() call times:" << config.get_recursion_count() << std::endl;
		config.reset();
	}
}

void backjump_leaf_solution::initialize(sudoku sudo) {
	state.reset();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (sudo.get_board().at(i).at(j) == -1) {
				continue;
			}
			state.set_digit(i, j, sudo.get_board().at(i).at(j));
		}
	}
}

void backjump_leaf_solution::set_digit(int row, int column, int num) {
	sudo.set_digit(row, column, num);
	state.set_digit(row, column, num);
}

void backjump_leaf_solution::reset_digit(int row, int column, int num) {
	sudo.reset_digit(row, column, num);
	state.reset_digit(row, column, num);
}

void backjump_leaf_solution::set_sudoku(sudoku SUDO) {
	sudo.set_clue(SUDO.get_clue());
	initialize(SUDO);
}
