#include "DLX.h"

DLX::DLX(sudoku SUDO) : sudo(SUDO.get_clue()) {
	initialize(sudo);
}

const sudoku& DLX::get_sudo() const {
	return this->sudo;
}

bool DLX::solve() {
	if (head->right == head) {
		print_solution();
		return true;
	}
	node* column = choose_column();
	fold(column);
	node* right_node = nullptr;
	for (node* row_node = column->down; row_node != column; row_node = row_node->down) {
		solution.push(row_node);
		for (right_node = row_node->right; right_node != row_node; right_node = right_node->right) {
			fold(right_node);
		}
		if (config.show_recursion_count) {
			config.count();
		}
		if (solve()) {
			return true;
		}
		for (right_node = row_node->right; right_node != row_node; right_node = right_node->right) {
			unfold(right_node);
		}
		solution.pop();
	}
	unfold(column);
	return false;
}

void DLX::solve(configuration_set _config) {
	config = _config;
	if (config.show_time) {
		config.start();
		solve();
		config.end();
		std::cout << "Time elapsed:" << config.get_time_difference() << "ms" << std::endl;
	} else {
		solve();
	}
	if (config.show_recursion_count) {
		std::cout << "Total solve() call times:" << config.get_recursion_count() << std::endl;
		config.reset();
	}
}

void DLX::initialize(sudoku SUDO) {
	set.resize(9 * 9 * 9);
	int row_count = 0;
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			for (int num = 0; num < 9; num++) {
				set[row_count].resize(9 * 9 * 4);
				set[row_count][r * 9 + c] = new node(row_count, r * 9 + c);
				set[row_count][81 + r * 9 + num] = new node(row_count, 81 + r * 9 + num);
				set[row_count][162 + c * 9 + num] = new node(row_count, 162 + c * 9 + num);
				set[row_count][243 + sudo.get_cell(r , c) * 9 + num] = new node(row_count, 243 + sudo.get_cell(r, c) * 9 + num);
				row_count++;
			}
		}
	}
	node* temp = nullptr;
	node* row_start = nullptr;
	for (int r = 0; r < 9 * 9 * 9; r++) {
		temp = nullptr;
		row_start = nullptr;
		for (int c = 0; c < 4 * 9 * 9; c++) {
			if (set[r][c] != nullptr) {
				if (temp == nullptr) {
					temp = set[r][c];
					row_start = temp;
					continue;
				} else {
					set[r][c]->left = temp;
					temp->right = set[r][c];
					temp = set[r][c];
				}
			}
		}
		temp->right = row_start;
		row_start->left = temp;
	}
	head = new node();
	temp = head;
	node* column_start = head;
	for (int c = 0; c < 4 * 9 * 9; c++) {
		column_start->right = new node(-1, c);
		column_start->right->left = column_start;
		column_start = column_start->right;
		temp = column_start;
		columns[c] = column_start;
		for (int r = 0; r < 9 * 9 * 9; r++) {
			if (set[r][c] != nullptr) {
				if (temp->up == nullptr) {
					temp->down = set[r][c];
					temp->down->up = temp;
					temp = set[r][c];
					continue;
				} else {
					set[r][c]->up = temp;
					temp->down = set[r][c];
					temp = set[r][c];
				}
			}
		}
		temp->down = column_start;
		column_start->up = temp;
	}
	column_start->right = head;
	head->left = column_start;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (sudo.get_board().at(i).at(j) == -1) {
				continue;
			}
			fold(i + 1, j + 1, sudo.get_board().at(i).at(j));
		}
	}
}

DLX::node::node(int _row, int _column) {
	this->row = _row;
	this->column = _column;
}

DLX::node* DLX::get_column(int _column) {
	return columns[_column];
}

DLX::node* DLX::choose_column() {
	int count = -1;
	int max = 9;
	node* return_column = nullptr;
	for (node* column = head->right; column != head; column = column->right) {
		count = -1;
		do {
			count++;
			column = column->down;
		} while (column->row != -1);
		if (max > count) {
			max = count;
			return_column = column;
		} else if (count == 0) {
			return column;
		}
	}
	return return_column;
}

void DLX::fold(int _row, int _column, int _num) {
	for (int c = 0; c < 9 * 9 * 4; c++) {
		if (set[(_row - 1) * 81 + (_column - 1) * 9 + _num - 1][c] != nullptr) {
			fold(set[(_row - 1) * 81 + (_column - 1) * 9 + _num - 1][c]);
		}
	}
}

void DLX::fold(node* node) {
	DLX::node* column = get_column(node->column);
	column->right->left = column->left;
	column->left->right = column->right;
	for (DLX::node* row =  column->down; row != column; row = row->down) {
		for (DLX::node* right_node = row->right; right_node != row; right_node = right_node->right) {
			right_node->up->down = right_node->down;
			right_node->down->up = right_node->up;
		}
	}
}

void DLX::unfold(node* node) {
	DLX::node* column = get_column(node->column);
	column->right->left = column;
	column->left->right = column;
	for (DLX::node* row = column->down; row != column; row = row->down) {
		for (DLX::node* right_node = row->right; right_node != row; right_node = right_node->right) {
			right_node->up->down = right_node;
			right_node->down->up = right_node;
		}
	}
}

DLX::position DLX::decode(int set_row) {
	int row = set_row / 81 + 1;
	set_row %= 81;
	int column = set_row / 9 + 1;
	set_row %= 9;
	int num = set_row + 1;
	return position(row, column, num);
}

void DLX::print_solution() {
	std::cout << std::endl;
	position pos(0, 0, 0);
	while (!solution.empty()) {
		pos = decode(solution.top()->row);
		sudo.set_digit(pos.row - 1, pos.column - 1, pos.num);
		solution.pop();
	}
	sudo.print_board();
}

void DLX::set_sudoku(sudoku SUDO) {
	sudo.set_clue(SUDO.get_clue());
	initialize(sudo);
}
