#include "pipe.h"
#include"globals.h"

pipe::pipe(int y_position)
{
	sprite_pipedown.setTexture(texture_pipedown);
	sprite_pipeup.setTexture(texture_pipeup);

	sprite_pipedown.setScale(SCALE_FACTOR, SCALE_FACTOR);
	sprite_pipeup.setScale(SCALE_FACTOR, SCALE_FACTOR);

	sprite_pipeup.setPosition(WINDOW_WIDTH, y_position);
	sprite_pipedown.setPosition(WINDOW_WIDTH, y_position - pipe_distance - sprite_pipeup.getGlobalBounds().height);
}

void pipe::update(sf::Time&dt)
{
	sprite_pipeup.move(-move_speed * dt.asSeconds(), 0.f);
	sprite_pipedown.move(-move_speed * dt.asSeconds(), 0.f);
}

void pipe::loadTextures()
{
	texture_pipedown.loadFromFile("assets/pipedown.png");
	texture_pipeup.loadFromFile("assets/pipe.png");
}

float pipe::getrightbound()
{
	return sprite_pipedown.getGlobalBounds().left + sprite_pipedown.getGlobalBounds().width;
}
sf::Texture pipe::texture_pipedown, pipe::texture_pipeup;
int pipe::pipe_distance = 160, pipe::move_speed = 400;
