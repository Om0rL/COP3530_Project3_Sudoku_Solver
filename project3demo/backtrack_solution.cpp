#include "backtrack_solution.h"

backtrack_solution::backtrack_solution(sudoku SUDO) : sudo(SUDO.get_clue()) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (sudo.get_board().at(i).at(j) == -1) {
				continue;
			}
			state.set_digit(i, j, sudo.get_board().at(i).at(j));
		}
	}
}

const sudoku& backtrack_solution::get_sudo() const {
	return this->sudo;
}

bool backtrack_solution::solve(int row_now, int column_now) {
	if (sudo.next_empty(row_now, column_now).first == -1 && sudo.next_empty(row_now, column_now).second == -1) {
		std::cout << std::endl;
		sudo.print_board();
		return true;
	}
	std::pair<int, int> vec2 = sudo.next_empty(row_now, column_now);
	for (int i = 0; i < 9; i++) {
		if (state.is_valid(vec2.first, vec2.second, i + 1)) {
			set_digit(vec2.first, vec2.second, i + 1);
			if (config.show_recursion_count) {
				config.count();
			}
			if (!solve(vec2.first, vec2.second)) {
				reset_digit(vec2.first, vec2.second, i + 1);
			} else {
				return true;
			}
		}
	}
	return false;
}

void backtrack_solution::solve(configuration_set _config) {
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

void backtrack_solution::set_digit(int row, int column, int num) {
	sudo.set_digit(row, column, num);
	state.set_digit(row, column, num);
}

void backtrack_solution::reset_digit(int row, int column, int num) {
	sudo.reset_digit(row, column, num);
	state.reset_digit(row, column, num);
}

void backtrack_solution::set_sudoku(sudoku SUDO) {
	sudo.set_clue(SUDO.get_clue());
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
