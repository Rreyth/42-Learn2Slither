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
	while (this->running)
	{
		this->input();
		if (!this->running)
			break;
		this->tick();
		this->render();
		//clock tick / sleep
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
		{
			win.close();
			this->running = false;
		}
	}
}


void Environment::tick()
{

}


void Environment::render()
{
	if (!this->visual) //TODO
		std::cout << "WIP -> PRINT TRAINING INFOS" << std::endl;
	else
		this->visual->render(this->grid.getPlayer(), this->grid.getApples());
		// this->visual.render -> map + infos

}


// # print if no visual
// # load msg
// # Training...
// # Session X / nb session (rewrite each loop)
// # end message with max life time and max length