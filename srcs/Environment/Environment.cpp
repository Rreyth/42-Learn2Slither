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
				this->grid.movePlayer(UP);
			else if (keyPressed->code == sf::Keyboard::Key::Down)
				this->grid.movePlayer(DOWN);
			else if (keyPressed->code == sf::Keyboard::Key::Left)
				this->grid.movePlayer(LEFT);
			else if (keyPressed->code == sf::Keyboard::Key::Right)
				this->grid.movePlayer(RIGHT);
		}
	}
}


void Environment::tick(float delta)
{
	// TODO : if move in wall or in body part -> dead
	// check head pos
	// if head on body or wall -> dead (- 100)
	// elif head on bonus -> + 30 -> move apple
	// elif head on malus -> - 30 -> move apple
	// elif closer to bonus -> + 1
	// else -> - 1
}


void Environment::render()
{
	if (!this->visual) //TODO
		std::cout << "WIP -> PRINT TRAINING INFOS" << std::endl;
	else
		this->visual->render(this->grid.getPlayer(), this->grid.getApples());
		// this->visual.render -> map + infos

}


void Environment::close()
{
	if (this->visual)
	{
		this->visual->getWin().close();
	}
	this->running = false;
}

// # print if no visual
// # load msg
// # Training...
// # Session X / nb session (rewrite each loop)
// # end message with max life time and max length