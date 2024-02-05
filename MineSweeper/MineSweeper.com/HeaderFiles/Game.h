#pragma once
#include"draw.h"
#include"Board.h"
#include"OtherFuncs.h"
#include<thread>

void timer(int& sec, int& stop) {
	sec = 0;
	while (stop == 0) {
		sf::sleep(sf::seconds(1));
		sec++;
	}
}

class Game {
	int   winner, lvl, stop, seconds, reset, end_sec, mine_time;
	Board* b;
public:
	Game() {
		lvl = 0;
		seconds = 0;
		reset = 0;
		b = nullptr;
		end_sec = 0;
		mine_time = -1;
	}
	Game(Game& g) {
		b = new Board;
		*b = *g.b;
	}
	~Game() {
		delete b;
	}
	void Start(sf::RenderWindow&);
	int Menu(sf::RenderWindow&);
	int Play(sf::RenderWindow&);
	void Restart(sf::RenderWindow&);

};

void Game::Start(sf::RenderWindow& wind) {
	int check = 0, again = 1;
	while (again == 1) {
		check = 0;
		Game::Menu(wind);
		while (check == 0) {
			check = Game::Play(wind);
			if (check == 0)
				Game::Restart(wind);
		}
		if (check == 1) {
			again = drawEnd(wind, end_sec);
		}
	}
	wind.close();
}

int Game::Menu(sf::RenderWindow& wind) {
mnu:
	int menu = drawMenu(wind);
	if (menu == 3) {
		wind.close();
		return 0;
	}
	else if (menu == 2 || menu == 1) {
	levels:
		lvl = drawLevel(wind);
		if (lvl == 10)
			goto mnu;
	}
	if (menu == 2) {
		int back = showScores(wind, lvl);
		if (back == 1)
			goto levels;
	}
}

int Game::Play(sf::RenderWindow& wind) {
	int x = 0, y = 0, i = 0, j = 0;
	bool time_restart = 1;
	b = new Board(lvl);
	drawBorder(wind, lvl);
	wind.display();
	seconds = 0;
	reset = 0, stop = 1;
	while (wind.isOpen()) {
		sf::Event event;
		while (wind.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				goto end;
			}
			if (event.type == sf::Event::MouseButtonPressed) {

				if (time_restart == 1) {
					stop = 0;
					std::thread time(&timer, std::ref(seconds), std::ref(stop));
					time.detach();
					time_restart = 0;
				}

				if (event.mouseButton.button == sf::Mouse::Right) {
					x = event.mouseButton.x;
					y = event.mouseButton.y;

					i = (y - 94) / 32;
					j = (x - 12) / 32;
					if (stop == 0)
						b->setFlag(wind, i, j);
					b->drawBoard(wind, lvl, seconds, stop, mine_time);
					b->drawBoard(wind, lvl, seconds, stop, mine_time);
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
					x = event.mouseButton.x;
					y = event.mouseButton.y;

					i = (y - 94) / 32;
					j = (x - 12) / 32;
					reset = isReset(wind, x, y, lvl);
					
					//b->cheatCode();
				}
				
			}
		}

		if (reset == 1) {
			stop = 1;
			seconds = 0;
			mine_time = -1;
			time_restart = 1;
			return 0;
		}

		if (reset == 0 && stop == 0)
			if (i < b->get_row() && j < b->get_col())
				stop = b->openBox(wind, i, j);

		if (stop == 1) {
			if (mine_time == -1)
				mine_time = seconds;
		}

		winner = b->isWinner();

		if (winner == 1 && stop == 0) {
			end_sec = seconds;
			b->drawBoard(wind, lvl, seconds, stop, mine_time);
			wind.display();

			updateScores(wind, lvl, end_sec);

			sf::sleep(sf::seconds(1));

			return 1;
		}

		b->drawBoard(wind, lvl, seconds, stop, mine_time);
		showTimer(wind, b->get_digital(), seconds, b->get_col(), stop, mine_time);
		wind.display();
	}
end:
	wind.close();
	return 2;
}

void Game::Restart(sf::RenderWindow& wind) {
	delete b;
}