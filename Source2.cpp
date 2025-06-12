#include<SFML/Graphics.hpp>
#include"globals.h"
#include "game.h"

int main() {

	sf::RenderWindow win(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird");

	Game game(win);

	game.start_game_loop();


	return 0;
}