#pragma once
#include <array>
#include <iostream>
#include <stack>

#include "sudoku.h"
#include "configuration_set.h"

class DLX {
private:
	class node {
	public:
		int row = -1;
		int column = -1;
		node* left = nullptr;
		node* right = nullptr;
		node* up = nullptr;
		node* down = nullptr;
		node() {};
		node(int _row, int _column);
	};
	class position {
	public:
		int row, column, num;
		position(int _row, int _column, int _num) : row(_row), column(_column), num(_num) {}
	};
	std::vector<std::vector<node*>> set;
	node* head = nullptr;
	node* columns[324];
	sudoku sudo;
	std::stack<node*> solution;
	configuration_set config;

	node* get_column(int _column);
	node* choose_column();
	position decode(int set_row);
	void fold(int _row, int _column, int _num);
	void fold(node* node);
	void unfold(node* node);
	void initialize(sudoku SUDO);
public:
	DLX(sudoku SUDO);
	const sudoku& get_sudo() const;
	bool solve();
	void solve(configuration_set _config);
	void print_solution();
	void set_sudoku(sudoku SUDO);
};

