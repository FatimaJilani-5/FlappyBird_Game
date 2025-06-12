#include "game.h"
#include "globals.h"
#include<sstream>

Game::Game(sf::RenderWindow& window):win(window), if_enter_pressed(false), run_game(true) , start_programming(false), pipe_counter(71), pipe_spawn_time(70), score(0)
{
	win.setFramerateLimit(60);
	bg_texture.loadFromFile("assets/bgg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);

	ground_texture.loadFromFile("assets/ground.png");
	ground1_sprite.setTexture(ground_texture);
	ground2_sprite.setTexture(ground_texture);

	ground1_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	ground2_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);

	ground1_sprite.setPosition(0, 510);
	ground2_sprite.setPosition(ground1_sprite.getGlobalBounds().width, 510);

	t_restart.loadFromFile("assets/restart.png");
	s_restart.setTexture(t_restart);
	s_restart.setPosition(140, 570);

	enter_texture.loadFromFile("assets/enter.png");
	sp_enter.setTexture(enter_texture);
	sp_enter.setPosition(150, 250);

	font.loadFromFile("assets/arial.ttf");
	score_text.setFont(font);
	score_text.setCharacterSize(27);
	score_text.setFillColor(sf::Color::Black);
	score_text.setPosition(15 ,15);
	score_text.setString("Score: 0");

	pipe::loadTextures();

}


void Game::start_game_loop()
{

	
	sf::Clock clock;
	//game loop
	while (win.isOpen()) {

		sf::Time dt = clock.restart();
		sf::Event event;
		
		//event loop
		while (win.pollEvent(event))//jo bhi event horha hai
		{
			if (event.type == sf::Event::Closed)
			{
				win.close();
			}
			if (event.type == sf::Event::KeyPressed && run_game)
			{
				if (event.key.code == sf::Keyboard::Enter && !if_enter_pressed)
				{
					if_enter_pressed = true;
					bird.set_isflying(true);
				}

				if (event.key.code == sf::Keyboard::Space && if_enter_pressed)
				{
					bird.flapBird(dt);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game)
			{
				if (s_restart.getGlobalBounds().contains(event.mouseButton.x ,event.mouseButton.y))
				{
					restart_game();
				}
				
			}
		}//event loop

		processing(dt);
		draw();
		win.display();
	}	
}//game loop

void Game::draw()
{
	win.draw(bg_sprite);
	for (pipe& pipe : pipes)
	{
		win.draw(pipe.sprite_pipedown);
		win.draw(pipe.sprite_pipeup);
	}
	win.draw(ground1_sprite);
	win.draw(ground2_sprite);
	win.draw(bird.bird_sprite);
	win.draw(score_text);

	if (!if_enter_pressed && run_game) {
		win.draw(sp_enter); //press enter to start image
	}

	if (!run_game)
	{
		win.draw(s_restart);
	}


}
void Game::move_ground(sf::Time& dt)
{
	ground1_sprite.move(-moving_speed * dt.asSeconds(), 0.f);
	ground2_sprite.move(-moving_speed * dt.asSeconds(), 0.f);

	if (ground1_sprite.getGlobalBounds().left + ground1_sprite.getGlobalBounds().width < 0)
	{

		ground1_sprite.setPosition(ground2_sprite.getGlobalBounds().left + ground2_sprite.getGlobalBounds().width, 510);
	}

	if (ground2_sprite.getGlobalBounds().left + ground2_sprite.getGlobalBounds().width < 0)
	{

		ground2_sprite.setPosition(ground1_sprite.getGlobalBounds().left + ground1_sprite.getGlobalBounds().width, 510);
	}
}

void Game::processing(sf::Time& dt)
{
	if (if_enter_pressed)
	{
		move_ground(dt);

		if (pipe_counter > pipe_spawn_time)//pipe counter increments in every fps , if it get exceeds a new pipe is generated
		{
            pipes.push_back(pipe(dist(rand_pipes)));//giving random value to pipe vector
		    pipe_counter = 0;
		}
		pipe_counter++;
			
		for (int i = 0; i < pipes.size(); i++)
		{
			pipes[i].update(dt);
			if (pipes[i].getrightbound() < 0)
			{
				pipes.erase(pipes.begin() + i);//if pipe goes out of screen-> erasing from the screen
			}
		}

		check_collisions();
		check_score();
	}
	bird.update(dt);
}

void Game::check_collisions()
{
	if (pipes.size() > 0)
	{
		if (pipes[0].sprite_pipedown.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds())//first pipe
			|| (pipes[0].sprite_pipeup.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds())//up pipe
            || bird.bird_sprite.getGlobalBounds().top>=460))
		 {
			if_enter_pressed = false;
			run_game = false;

		 }
	}
}

void Game::restart_game()
{

	bird.reset_bird_position();
	bird.set_isflying(false);
	run_game = true;
	if_enter_pressed = false;
	pipe_counter = 71;
	pipes.clear();
	score = 0;
	score_text.setString("Score: 0");

}

void Game::check_score()
{
	if (pipes.size() > 0)
	{
		if (!start_programming)
		{
			if (bird.bird_sprite.getGlobalBounds().left > pipes[0].sprite_pipedown.getGlobalBounds().left &&
				bird.get_right_bound() < pipes[0].getrightbound())
			{
				start_programming = true;
			}
		}
			else
			{
				if (bird.bird_sprite.getGlobalBounds().left > pipes[0].getrightbound())
				{
					score++;
					score_text.setString("Score:" + tostring(score));
					start_programming = false;
				}
			}
		
	}

}

string Game::tostring(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();//takes an integer num and returs its string
}