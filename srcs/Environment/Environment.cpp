#include <Environment/Environment.hpp>
#include <iostream>

Environment::Environment(flags &launch_flags) : grid(launch_flags.size)
{
	this->env_flags = launch_flags;

	if (launch_flags.visual)
		this->visual = new Visual(launch_flags);

	// TODO: init agent with sessions and dontlearn

	this->running = true;
	this->move = false;
	this->nb_move = 0;
	this->max_size = 3;
	this->last_reward = 0;
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
	this->input_manager.manageInput(*this, *this->visual);
}


void Environment::tick(float delta)
{
	int reward = this->checkMove();
	if (reward != 0)
	{
		this->last_reward = reward;
	}
	if (this->visual)
	{
		this->visual->tick(*this, this->input_manager.getMouse());
	}
}


void Environment::render()
{
	if (!this->visual) //TODO
		std::cout << "WIP -> PRINT TRAINING INFOS" << std::endl;
	else //TODO : add actual size
		this->visual->render(this->grid.getPlayer(), this->grid.getApples(),
			this->nb_move, this->max_size, this->last_reward);
}


int Environment::checkMove()
{
	int reward = -1;
	if (!this->move)
		return 0;
	this->nb_move++;
	this->move = false;
	sf::Vector2i pos = this->grid.getPlayer().head_pos;

	if (this->grid.wallHit(pos) || this->grid.occupiedByBody(pos))
	{
		// TODO: death -> if AI -> next session
		reward = -100;
		this->reset();
	}
	else if (this->grid.occupiedByApples(pos))
	{
		s_apple& apple = this->grid.getAppleByPos(pos);
		if (apple.bonus)
		{
			reward = 30;
			this->grid.playerGrow();
		}
		else
		{
			this->grid.playerShrink();
			reward = -30;
		}
		int	current_len = this->grid.getPlayerLen();
		if (current_len == 0)
		{
			// TODO: death
			this->reset();
			return -100;
		}
		if (current_len + 1 > this->max_size)
			this->max_size = current_len + 1;
		this->grid.moveApple(apple);
	}
	else if (this->grid.isCloserMove())
		reward = 1;

	return reward;
}


void Environment::setMove(bool moved)
{
	this->move = moved;
}


Grid	&Environment::getGrid()
{
	return this->grid;
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
	this->nb_move = 0;
	this->max_size = 3;
	this->last_reward = 0;
}


void	Environment::startGame(s_settings settings)
{
	this->reset();
	this->input_manager.resetMouse();
	this->grid.start(settings.size);
	// TODO: use all settings
}


void	Environment::changeWin()
{
	this->input_manager.resetMouse();
}

//TODO # print if no visual
// # load msg
// # Training...
// # Session X / nb session (rewrite each loop)
// # end message with max life time and max length