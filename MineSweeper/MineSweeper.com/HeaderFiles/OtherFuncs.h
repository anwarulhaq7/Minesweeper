#pragma once
#include"Cell.h"

void place_mines(int**& arr, int r, int c, int no_of_mines) {

	srand(time(0));

	int idx, ro, co;
	bool repeat = false;

	//----------------------------------- Temp Array to store random index numbers where we will place mines.

	int* temp = new int[no_of_mines];

	for (int i = 0;i < no_of_mines;i++) {
		repeat = false;
		idx = rand() % (r * c);

		//------------------------------- To check if numbers already exsit in the temp array.

		if (i > 0) {
			for (int j = 0;j < i;j++)
				if (temp[j] == idx) {
					repeat = true;
					i--;
				}
		}
		if (repeat == false)
			temp[i] = idx;
	}
	//----------------------------------- To Place mines in original array from indexes stored in Temp array.

	for (int i = 0;i < no_of_mines;i++) {
		ro = temp[i] / c;
		co = temp[i] % c;
		arr[ro][co] = 9;
	}
	//----------------------------------- Deleting Temp Array.
	delete[]temp;
}

int one_cell(int**& arr, int r, int c, int i, int j) {
	int count = 0;

	for (int x = i - 1;x <= i + 1;x++) {
		if (x < 0 || x == r)
			continue;
		for (int y = j - 1;y <= j + 1;y++) {
			if (y < 0 || y == c)
				continue;
			if (arr[x][y] == 9)
				count++;
		}
	}
	return count;
}

void count_mines(int**& arr, int r, int c) {
	for (int i = 0;i < r;i++)
		for (int j = 0;j < c;j++)
			if (arr[i][j] != 9)
				arr[i][j] = one_cell(arr, r, c, i, j);
}

void conv_cells(sf::Font& font, sf::Texture& tex, Cell***& cels, int** arr, int r, int c) {
	cels = new Cell * *[r];
	for (int i = 0;i < r;i++)
		cels[i] = new Cell * [c];

	for (int i = 0;i < r;i++)
		for (int j = 0;j < c;j++) {
			if (arr[i][j] == 0)
				cels[i][j] = new Zero_Cell;
			else if (arr[i][j] == 9)
				cels[i][j] = new Mine_Cell(tex);
			else
				cels[i][j] = new Nonzero_Cell(arr[i][j], font);
		}
}

void showExposes(sf::RenderWindow& wind, Cell***& cell, int r, int c) {
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++)
			cell[i][j]->drawExposes(wind);
	}
}

void showBoxes(sf::RenderWindow& wind, Cell***& cell, int r, int c) {
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++)
			cell[i][j]->drawCell(wind, j, i);
	}
}

void showTimer(sf::RenderWindow& wind, const sf::Font& font, int sec, int col, int stop, int m_time) {
	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(sec));
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(50);
	text.setLetterSpacing(2.f);
	text.setFillColor(sf::Color(255, 0, 0));
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color(255, 200, 200));

	sf::RectangleShape rec;
	rec.setFillColor(sf::Color(0, 0, 0));
	rec.setOutlineColor(sf::Color(90, 90, 90));
	rec.setOutlineThickness(3);

	if (col != 30) {
		rec.setPosition(sf::Vector2f(col * 32 - 85, 17));
		rec.setSize(sf::Vector2f(90, 60));
	}
	else {
		rec.setPosition(sf::Vector2f(col * 32 - 115, 17));
		rec.setSize(sf::Vector2f(120, 60));
	}
	if (sec < 10)
		text.setPosition(sf::Vector2f(col * 32 - 26, 12));
	else if (sec < 100)
		text.setPosition(sf::Vector2f(col * 32 - 52, 12));
	else if (sec < 1000)
		text.setPosition(sf::Vector2f(col * 32 - 80, 12));
	else
		text.setPosition(sf::Vector2f(col * 32 - 110, 12));

	if (stop == 1)
		if (m_time == -1)
			text.setString(std::to_string(0));
		else
			text.setString(std::to_string(m_time));

	wind.draw(rec);
	wind.draw(text);

}

void showFlags(sf::RenderWindow& wind, const sf::Font& font, int num) {
	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(num));
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(50);
	text.setLetterSpacing(2.f);
	text.setFillColor(sf::Color(255, 0, 0));
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color(255, 200, 200));
	text.setPosition(sf::Vector2f(24, 12));

	sf::RectangleShape rec;
	rec.setPosition(sf::Vector2f(19, 17));
	rec.setSize(sf::Vector2f(60, 60));
	rec.setFillColor(sf::Color(0, 0, 0));
	rec.setOutlineColor(sf::Color(90, 90, 90));
	rec.setOutlineThickness(3);

	wind.draw(rec);
	wind.draw(text);
}

void showEmoji(sf::RenderWindow& wind, int c) {
	Square emoji(50);
	emoji.setPosition(sf::Vector2f((c * 32) / 2 - 21.5, 22));
	emoji.draw(wind);

	sf::CircleShape cir;
	cir.setRadius(20);
	cir.setPosition(sf::Vector2f((c * 32) / 2 - 16.5, 27));
	cir.setFillColor(sf::Color(255, 220, 0));
	cir.setOutlineThickness(1);
	cir.setOutlineColor(sf::Color::Black);
	wind.draw(cir);

	cir.setOutlineThickness(0);
	cir.setRadius(15);
	cir.setPosition(sf::Vector2f((c * 32) / 2 - 11.5, 30));
	cir.setFillColor(sf::Color::Black);
	wind.draw(cir);

	cir.setPosition(sf::Vector2f((c * 32) / 2 - 11.5, 27));
	cir.setFillColor(sf::Color(255, 220, 0));
	wind.draw(cir);

	cir.setRadius(2);
	cir.setPosition(sf::Vector2f((c * 32) / 2 - 5.5, 36));
	cir.setFillColor(sf::Color::Black);
	wind.draw(cir);

	cir.setPosition(sf::Vector2f((c * 32) / 2 + 7, 36));
	wind.draw(cir);

}

bool isReset(sf::RenderWindow& window, int x, int y, int lvl) {
	int start_x = 0, start_y = 22, end_x = 0, end_y = 72;
	switch (lvl) {
	case 1:
		start_x = 122.5;
		end_x = 172.5;
		break;
	case 2:
		start_x = 234.5;
		end_x = 284.5;
		break;
	case 3:
		start_x = 458.5;
		end_x = 508.5;
		break;
	}
	if (x >= start_x && x <= end_x)
		if (y >= start_y && y <= end_y) {

			return 1;
		}
	return false;
}