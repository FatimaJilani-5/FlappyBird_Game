#pragma once
#include<SFML/Graphics.hpp>

class Bird
{
private:
	sf::Texture textures[2];
	const int gravity;
	const int flap_speed;
	float veloctiy_y; 
	int image_counter; //changing flapping image
    int texture_switch;
	bool isflying;//when pressing space bar 

public:
	sf::Sprite bird_sprite;
	Bird();
	void set_isflying(bool);
	void flapBird(sf::Time&);//when called bird will flap
	void reset_bird_position(); //when bird crashes, then it needs resetting
	void update(sf::Time&);
	float get_right_bound();//returning right x cordination for when it crashes with the pipe
};

