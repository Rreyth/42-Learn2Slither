#include <Environment/Environment.hpp>
// #include <cmath>
// #include <iostream>

Environment::Environment(flags &launch_flags) : grid(launch_flags.size), ai_agent(launch_flags.sessions, !launch_flags.dontlearn)
{
	this->env_flags = launch_flags;

	if (launch_flags.visual)
		this->visual = new Visual(launch_flags);

	this->running = true;
	this->move = false;
	this->ai_play = !launch_flags.visual;
	this->ai_move_time = 0;

	if (launch_flags.load)
	{
		try
		{
			this->ai_agent.loadQTable(launch_flags.loadfile);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	if (this->ai_play)
	{ // no visual, only ai running
		this->ai_agent.play(*this);
		this->close();
	}
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
		this->tick();
		this->render();
	}
}


void Environment::input()
{
	if (!this->visual)
		return;
	this->input_manager.manageInput(*this, *this->visual);
}


void Environment::tick()
{
	int reward = this->checkMove();
	if (reward != 0)
	{
		this->infos.last_reward = reward;
	}
	if (this->visual)
	{
		this->visual->tick(*this, this->input_manager.getMouse());
	}
}


void Environment::render()
{
	if (this->visual)
		this->visual->render(this->grid.getPlayer(), this->grid.getApples(),
			this->infos);
}


int Environment::checkMove()
{
	int reward = -1;
	if (!this->move)
		return 0;
	this->infos.nb_moves++;
	this->move = false;
	sf::Vector2i pos = this->grid.getPlayer().head_pos;

	if (this->grid.wallHit(pos) || this->grid.occupiedByBody(pos))
	{
		// TODO: death -> if AI -> next session
		reward = -100;
		if (!this->ai_play)
		{
			this->visual->setState(GAMEOVER);
			this->visual->gameOverInit(this->infos);
		}
		else
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
			this->infos.current_size = 0;
			if (!this->ai_play)
			{
				this->visual->setState(GAMEOVER);
				this->visual->gameOverInit(this->infos);
			}
			else
				this->reset();
			return -100;
		}
		this->infos.current_size = current_len + 1;
		if (current_len + 1 > this->infos.max_size)
			this->infos.max_size = current_len + 1;
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


bool	Environment::getAiPlay()
{
	return this->ai_play;
}


void Environment::close()
{
	if (this->visual)
	{
		this->visual->getWin().close();
	}
	this->running = false;
	if (this->env_flags.save && (this->ai_play || !this->visual))
	{
		this->ai_agent.saveQTable(this->env_flags.savefile);
	}
}


State Environment::reset()
{
	this->running = true;
	this->grid.reset();
	this->infos = gameInfos();

	return this->grid.getAgentState();
}


void	Environment::startGame(s_settings settings)
{
	this->reset();
	this->input_manager.resetMouse();
	this->grid.start(settings.size);
	this->ai_play = settings.AI_play;

	this->env_flags.size = settings.size;
	this->env_flags.sessions = settings.sessions;
	this->env_flags.stepmode = settings.step_mode;
	this->env_flags.dontlearn = !settings.learn;
	this->ai_move_time = settings.move_time;

	this->ai_agent.setLearn(settings.learn);
	this->ai_agent.setSessions(settings.sessions);
}


void	Environment::changeWin()
{
	this->input_manager.resetMouse();
}


void	Environment::step(const player_dir &action, learnStep &learn_step)
{
	//TODO: add timer to slow ai

	this->grid.movePlayer(action);
	this->move = true;
	this->tick();
	learn_step.reward = this->infos.last_reward;
	learn_step.next_state = this->grid.getAgentState();
	learn_step.done = (learn_step.reward == -100);
	this->render();
}

