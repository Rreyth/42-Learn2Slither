#include "Environment.hpp"
#include <iostream>

Environment::Environment(const flags &launch_flags) : grid(launch_flags.size)
{
	this->env_flags = launch_flags;

	std::string	test = this->grid.getAgentView();

	s_player player = this->grid.getPlayer();

	std::string	spaces(player.head_pos.x, ' ');

	std::cout << "Agent view:" << std::endl;
	for (int y = 0; y < this->env_flags.size + 2; y++)
	{
		if (y == player.head_pos.y)
			std::cout << &test[this->env_flags.size + 2] << std::endl;
		else
			std::cout << spaces << test[y] << std::endl;
	}

	// TODO: if visual init visual
	// TODO: init agent with sessions and dontlearn
}


Environment::~Environment()
{
}


void Environment::run()
{

}




// # print if no visual
// # load msg
// # Training...
// # Session X / nb session (rewrite each loop)
// # end message with max life time and max length