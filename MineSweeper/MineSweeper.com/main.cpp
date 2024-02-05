#include"SFML/Graphics.hpp"
#include"HeaderFiles/Game.h"
int main() {
	sf::RenderWindow wind(sf::VideoMode(480, 640), "MineSweeper", sf::Style::Close);
	wind.setFramerateLimit(60);
	Game myGame;
	myGame.Start(wind);
	return 0;
}