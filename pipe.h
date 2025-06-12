#pragma once
#include<SFML/Graphics.hpp>
class pipe
{
public:
	pipe(int);
	sf::Sprite sprite_pipeup, sprite_pipedown;
	static void loadTextures();//loads both pipes textures
	void update(sf::Time&);
	float getrightbound();//position of pipe

private:

	static sf::Texture texture_pipeup, texture_pipedown;
	static int pipe_distance, move_speed; //distance between two pipes

};

