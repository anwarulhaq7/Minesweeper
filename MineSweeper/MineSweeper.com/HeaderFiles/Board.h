#pragma once
#include<SFML/Graphics.hpp>
#include"Cell.h"
#include"draw.h"
#include"OtherFuncs.h"
class Board {
	int row;
	int col;
	int flag;
	sf::Font num, digital;
	sf::Texture mine_tex;
	int** arr;
	Cell*** cells;
public:
	Board() {
		row = 0;
		col = 0;
		arr = nullptr;
		flag = 0;
		cells = nullptr;
	}
	Board(int mode) {
		if (mode == 1) {
			row = 9;
			col = 9;
			flag = 10;
		}
		if (mode == 2) {
			row = 16;
			col = 16;
			flag = 40;
		}
		if (mode == 3) {
			row = 16;
			col = 30;
			flag = 99;
		}
		mine_tex.loadFromFile("Images/new.png");
		num.loadFromFile("Fonts/Stay and Shine.ttf");
		digital.loadFromFile("Fonts/Ticking.ttf");
		arr = new int* [row];
		for (int i = 0;i < row;i++)
			arr[i] = new int[col];
		place_mines(arr, row, col, flag);
		count_mines(arr, row, col);
		conv_cells(num, mine_tex, cells, arr, row, col);
	}
	Board(Board& b) {
		row = b.row;
		col = b.col;
		flag = b.flag;

		arr = new int* [row];
		for (int i = 0;i < row;i++)
			arr[i] = new int[col];
		for (int i = 0;i < row;i++)
			for (int j = 0;j < col;j++)
				arr[i] = b.arr[i];

		cells = new Cell * *[row];
		for (int i = 0;i < row;i++)
			cells[i] = new Cell * [col];
		for (int i = 0;i < row;i++)
			for (int j = 0;j < col;j++)
				cells[i][j] = b.cells[i][j];
	}
	~Board() {
		if (arr != nullptr) {
			for (int i = 0;i < row;i++)
				delete[]arr[i];
		}
		delete[]arr;
		if (cells != nullptr) {
			for (int i = 0;i < row;i++)
				delete[]cells[i];
		}
		delete[]cells;
	}

	void drawBoard(sf::RenderWindow&, int, int, int, int);
	void setFlag(sf::RenderWindow&, int, int);
	bool openBox(sf::RenderWindow&, int, int);
	void openZeroBox(sf::RenderWindow&, int, int);
	bool isWinner();
	void cheatCode();

	int** get_arr();
	Cell*** get_cells();
	int get_row();
	int get_col();
	sf::Font get_digital();
};

void Board::drawBoard(sf::RenderWindow& window, int mode, int sec, int stop, int m_time) {
	drawBorder(window, mode);
	showBoxes(window, cells, row, col);
	showFlags(window, digital, flag);
	showEmoji(window, col);
	showExposes(window, cells, row, col);
	showTimer(window, digital, sec, col, stop, m_time);
}

void Board::setFlag(sf::RenderWindow& window, int i, int j) {
	if (arr[i][j] < 10 && arr[i][j] != -5) {
		(cells[i][j])->makeFlag(j, i, window);
		arr[i][j] += 10;
		flag--;
	}
	else if (arr[i][j] > 9) {
		cells[i][j]->remFlag(j, i, window);
		arr[i][j] -= 10;
		flag++;
	}
}

bool Board::openBox(sf::RenderWindow& window, int i, int j) {
	int check = 0;
	if (arr[i][j] < 10 && arr[i][j] != -5) {
		check = cells[i][j]->expose(window, arr, j, i);
		arr[i][j] = -5;
	}

	//------------ To check if exposing box is a mine cell 

	if (check == 1) {
		for (int x = 0;x < row;x++)
			for (int y = 0;y < col;y++) {
				/*if (arr[x][y] == 9)*/ {
					cells[x][y]->expose(window, arr, y, x);
					arr[x][y] = -5;
				}
			}
		return 1;

	}
	//------------ To check if exposing box is a zero cell 

	else if (check == 2) {
		Board::openZeroBox(window, i, j);
	}
	return 0;
}

void Board::openZeroBox(sf::RenderWindow& window, int i, int j) {
	for (int x = i - 1;x <= i + 1;x++) {
		if (x < 0 || x == row)
			continue;
		for (int y = j - 1;y <= j + 1;y++) {
			if (y < 0 || y == col)
				continue;
			if (x == i && j == y)
				continue;
			if (arr[x][y] < 10 && arr[x][y] != -5) {
				cells[x][y]->expose(window, arr, y, x);

				//--------- For exposing all 0 Cells

				if (arr[x][y] == 0) {
					arr[x][y] = -5;
					this->openZeroBox(window, x, y);
				}
				arr[x][y] = -5;
			}
		}
	}
}

bool Board::isWinner() {
	bool check = 1;
	for (int i = 0;i < row;i++)
		for (int j = 0;j < col;j++)
			if (arr[i][j] != -5 && arr[i][j] != 19 && arr[i][j] != 9) {
				check = 0;
				break;
			}
	return check;
}

void Board::cheatCode() {
	system("cls");
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (arr[i][j] == 9)
				std::cout << "M" << "  ";
			else if (arr[i][j] == 0)
				std::cout << "o" << "  ";
			else
				std::cout << "I" << "  ";
		}
		std::cout << std::endl;
	}
}

int** Board::get_arr() {
	return arr;
}
Cell*** Board::get_cells() {
	return cells;
}
int Board::get_row() {
	return row;
}
int Board::get_col() {
	return col;
}
sf::Font Board::get_digital() {
	return digital;
}