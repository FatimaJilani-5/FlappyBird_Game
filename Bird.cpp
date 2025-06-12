#include "Bird.h"
#include"globals.h"

Bird::Bird() :
	gravity(14),
	flap_speed(250),
	image_counter(0),
	texture_switch(1),
	isflying(false)
{
	textures[0].loadFromFile("assets/birddown.png");
	textures[1].loadFromFile("assets/birdup.png");

	bird_sprite.setTexture(textures[0]);
	bird_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	reset_bird_position();
}

void Bird::update(sf::Time&dt)
{
	if (bird_sprite.getGlobalBounds().top < 480 && isflying)//prevents it going past the ground
	{
		if (image_counter == 3)//switches the texture after 3 frames
		{
			bird_sprite.setTexture(textures[texture_switch]);
			if (texture_switch)texture_switch = 0;
			else texture_switch = 1;
			image_counter = 0;
		}
		image_counter++;

		veloctiy_y += gravity * dt.asSeconds();
		bird_sprite.move(0, veloctiy_y);//move down

		if (bird_sprite.getGlobalBounds().top < 0)
			bird_sprite.setPosition(100, 0);//resetting so it does not go out from frame from the top

	}
}

void Bird::flapBird(sf::Time&dt)
{
	veloctiy_y = -flap_speed * dt.asSeconds();//whenever space bar is pressed it stmlates it flying upwards
}

float Bird::get_right_bound()
{
	return bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width;//to detect collision
}

void Bird::reset_bird_position()
{
	bird_sprite.setPosition(100, 50);
	veloctiy_y = 0;
}

void Bird::set_isflying(bool is_flying)
{
	this->isflying = is_flying;

}



