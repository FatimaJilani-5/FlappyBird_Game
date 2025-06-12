using namespace std;
#include<SFML/Graphics.hpp>
#include<vector>
#include<random>
#include"Bird.h"
#include "pipe.h"


class Game
{
public:

	Game(sf::RenderWindow&);
	sf::RenderWindow& win;
	void start_game_loop();

private:

	sf::Texture bg_texture, ground_texture, enter_texture;
	sf::Sprite  bg_sprite, ground1_sprite,ground2_sprite;
	sf::Texture t_restart;
	sf::Sprite s_restart;
	sf::Sprite sp_enter;
	Bird bird;
	bool if_enter_pressed, run_game , start_programming;
	const int moving_speed = 500;
	void draw();
	void move_ground(sf::Time&);
	void processing(sf::Time& dt);
	void check_collisions();
	void restart_game();
	void check_score();
	string tostring(int);//convert int to string for score
	int score;
	int pipe_counter, pipe_spawn_time;//creating the pipes after some time i.e when counter hits spawn time
	vector <pipe> pipes;
	random_device rand_pipes;//generating pipes randomly
	uniform_int_distribution<int> dist{ 250,550 };//to generate a random number
	sf::Font font;
	sf::Text restart_text;
	sf::Text score_text;
};

