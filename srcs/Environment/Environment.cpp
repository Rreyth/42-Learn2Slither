#include "Environment.hpp"
#include <iostream>

Environment::Environment(const flags &launch_flags) : grid(launch_flags.size)
{
	this->env_flags = launch_flags;

	// std::string	test = this->grid.getAgentView();
	// s_player player = this->grid.getPlayer();
	// std::string	spaces(player.head_pos.x, ' ');
	// std::cout << "Agent view:" << std::endl;
	// for (int y = 0; y < this->env_flags.size + 2; y++)
	// {
	// 	if (y == player.head_pos.y)
	// 		std::cout << &test[this->env_flags.size + 2] << std::endl;
	// 	else
	// 		std::cout << spaces << test[y] << std::endl;
	// }

	if (launch_flags.visual)
		this->visual = new Visual(launch_flags.size);

	// TODO: init agent with sessions and dontlearn

	this->running = true;
	this->move = false;
}


Environment::~Environment()
{
	delete this->visual;
}


void Environment::run()
{
	float delta, fps;
	while (this->running)
	{
		this->input();
		if (!this->running)
			break;
		delta = clock.restart().asSeconds();
		if (this->visual)
		{
			fps = 1.0f / delta;
			std::string title("I'M A SNAKE! | " + std::to_string(static_cast<int>(fps)));
			this->visual->getWin().setTitle(title);
		}
		this->tick(delta);
		this->render();
	}
}


void Environment::input()
{
	if (!this->visual)
		return;
	sf::RenderWindow	&win = this->visual->getWin();
	while (const std::optional event = win.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->code == sf::Keyboard::Key::Escape)
				this->close();
			else if (keyPressed->code == sf::Keyboard::Key::Up)
			{
				this->move = true;
				this->grid.movePlayer(UP);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Down)
			{
				this->move = true;
				this->grid.movePlayer(DOWN);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Left)
			{
				this->move = true;
				this->grid.movePlayer(LEFT);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Right)
			{
				this->move = true;
				this->grid.movePlayer(RIGHT);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Space)
			{
				this->reset();
			}
		}
	}
}


void Environment::tick(float delta)
{
	int reward = this->checkMove();
	if (reward != 0)
		std::cout << "Reward: " << reward << std::endl;
}


void Environment::render()
{
	if (!this->visual) //TODO
		std::cout << "WIP -> PRINT TRAINING INFOS" << std::endl;
	else
		this->visual->render(this->grid.getPlayer(), this->grid.getApples());
		// this->visual.render -> map + infos

}


int Environment::checkMove()
{
	int reward = -1;
	if (!this->move)
		return 0;
	this->move = false;
	sf::Vector2i pos = this->grid.getPlayer().head_pos;

	if (this->grid.wallHit(pos) || this->grid.occupiedByBody(pos))
	{
		// TODO: death -> if AI -> next session
		reward = -100;
	}
	else if (this->grid.occupiedByApples(pos))
	{
		s_apple& apple = this->grid.getAppleByPos(pos);
		if (apple.bonus)
			reward = 30;
		else
			reward = -30;
		this->grid.moveApple(apple);
		//TODO: update snake size -> if body parts = 0 ? if total len = 0 ? -> death
	}
	else if (this->grid.isCloserMove())
		reward = 1;

	return reward;
}


void Environment::close()
{
	if (this->visual)
	{
		this->visual->getWin().close();
	}
	this->running = false;
}


void Environment::reset()
{
	this->running = true;
	this->grid.reset();
}


// # print if no visual
// # load msg
// # Training...
// # Session X / nb session (rewrite each loop)
// # end message with max life time and max length