#pragma once
#include<SFML/Graphics.hpp>
#include"draw.h"

class Cell {
	Square shape;
	Flag f;
protected:
	sf::RectangleShape r1, r2;
public:
	Cell() {
		shape.setPosition(sf::Vector2f(0, 5000));
		f.setPosition(sf::Vector2f(0, 5000));

		r1.setSize(sf::Vector2f(35, 3));
		r2.setSize(sf::Vector2f(35, 3));
		r1.setPosition(sf::Vector2f(50000, 1000));
		r2.setPosition(sf::Vector2f(50000, 1000));
		r2.setFillColor(sf::Color(0, 0, 0));
		r1.setFillColor(sf::Color(0, 0, 0));
		r1.rotate(44);
		r2.rotate(134);
	}
	virtual int expose(sf::RenderWindow&, int**, int, int) {
		return 0;
	}
	virtual void drawExposes(sf::RenderWindow&) {

	}
	void makeFlag(int, int, sf::RenderWindow&);
	void remFlag(int, int, sf::RenderWindow&);
	void drawCell(sf::RenderWindow&, int, int);
};

void Cell::makeFlag(int i, int j, sf::RenderWindow& window) {
	f.setPosition(sf::Vector2f((i * 32) + 12, (j * 32) + 94));
}

void Cell::remFlag(int i, int j, sf::RenderWindow& window) {
	f.setPosition(sf::Vector2f(5000, 5000));
}

void Cell::drawCell(sf::RenderWindow& wind, int i, int j) {
	shape.setPosition(sf::Vector2f((i * 32 + 12), (j * 32 + 94)));
	shape.draw(wind);
	f.draw(wind);
}

class Nonzero_Cell :public Cell {
	int num;
	sf::Text text;
	sf::RectangleShape rec;
public:
	Nonzero_Cell() {
		num = 0;
	}
	Nonzero_Cell(int n, sf::Font& font) {
		rec.setSize(sf::Vector2f(30, 30));
		rec.setPosition(sf::Vector2f(5000, 0));
		rec.setFillColor(sf::Color(210, 210, 200));

		text.setFont(font);
		text.setString(std::to_string(n));
		text.setStyle(sf::Text::Bold);
		text.setPosition(sf::Vector2f(5000, 0));
		text.setCharacterSize(30);
		switch (n) {
		case 1:
			text.setFillColor(sf::Color(0, 0, 230));
			break;
		case 2:
			text.setFillColor(sf::Color(0, 128, 0));
			break;
		case 3:
			text.setFillColor(sf::Color(240, 0, 0));
			break;
		case 4:
			text.setFillColor(sf::Color(5, 10, 135));
			break;
		case 5:
			text.setFillColor(sf::Color(135, 5, 10));
		default:
			text.setFillColor(sf::Color(128, 128, 0));
		}
		num = n;
	}
	virtual int expose(sf::RenderWindow&, int**, int, int);
	virtual void drawExposes(sf::RenderWindow&);
};

int Nonzero_Cell::expose(sf::RenderWindow& wind, int** arr, int i, int j) {
	if (arr[j][i] < 10) {
		rec.setPosition(sf::Vector2f(i * 32 + 12, j * 32 + 94));
		text.setPosition(sf::Vector2f(i * 32 + 20, j * 32 + 90));
	}
	else if (arr[j][i] > 10) {
		r1.setPosition(sf::Vector2f(i * 32 + 15, j * 32 + 97));
		r2.setPosition(sf::Vector2f(i * 32 + 41, j * 32 + 99));
	}
	return 0;
}

void Nonzero_Cell::drawExposes(sf::RenderWindow& wind) {
	wind.draw(rec);
	wind.draw(text);
	wind.draw(r1);
	wind.draw(r2);
}

class Zero_Cell :public Cell {
	sf::RectangleShape rec;
public:
	Zero_Cell() {
		rec.setSize(sf::Vector2f(30, 30));
		rec.setPosition(sf::Vector2f(5000, 0));
		rec.setFillColor(sf::Color(210, 210, 200));
	}
	virtual int expose(sf::RenderWindow&, int**, int, int);
	virtual void drawExposes(sf::RenderWindow&);
};

int Zero_Cell::expose(sf::RenderWindow& wind, int** arr, int i, int j) {
	if (arr[j][i] == 0)
		rec.setPosition(sf::Vector2f(i * 32 + 12, j * 32 + 94));
	else if (arr[j][i] == 10) {
		r1.setPosition(sf::Vector2f(i * 32 + 15, j * 32 + 97));
		r2.setPosition(sf::Vector2f(i * 32 + 41, j * 32 + 99));
	}
	return 2;
}

void Zero_Cell::drawExposes(sf::RenderWindow& wind) {
	wind.draw(r1);
	wind.draw(r2);
	wind.draw(rec);
}

class Mine_Cell :public Cell {
	sf::CircleShape cir, cir2;
	Mine m;
public:
	Mine_Cell(sf::Texture& tex) {
		m.setTexture(tex);
		m.setPosition(sf::Vector2f(5000, 0));
	}
	virtual int expose(sf::RenderWindow&, int**, int, int);
	virtual void drawExposes(sf::RenderWindow&);
};

int Mine_Cell::expose(sf::RenderWindow& wind, int** arr, int i, int j) {
	if (arr[j][i] == 9) {
		m.setPosition(sf::Vector2f(i * 32 + 11, j * 32 + 92));
	}
	return 1;
}

void Mine_Cell::drawExposes(sf::RenderWindow& wind) {
	m.draw(wind);
}