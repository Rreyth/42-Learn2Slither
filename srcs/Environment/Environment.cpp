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
	this->next_step = false;

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
	{ // no visual, only AI running
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
	float delta, timer;
	timer = 0;
	while (this->running)
	{
		this->next_step = false;
		this->input();
		if (!this->running)
			break;
		delta = clock.restart().asSeconds();
		if (!this->env_flags.stepmode)
		{
			timer += delta;
			if (timer >= this->ai_move_time)
			{
				this->next_step = true;
				timer = 0;
			}
		}

		// if (this->visual)
		// {
			// fps = 1.0f / delta;
			// std::string title("I'M A SNAKE! | " + std::to_string(static_cast<int>(fps)));
			// this->visual->getWin().setTitle(title);
		// }
		this->tick();
		this->render(); //TODO: ADAPT FOR AI
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
	if (this->ai_play && this->visual && this->next_step)
	{
		State state = this->grid.getAgentState();
		this->ai_agent.visualPlay(*this, state);

		visualModAiStep ai_step = this->ai_agent.getVisualStep();

		if (ai_step.step.done)
		{
			this->ai_agent.visualStepEnd();
			this->reset();
		}

		if (ai_step.session_count == this->env_flags.sessions) //End of training / play
		{
			this->visual->setState(AI_GAMEOVER);
			this->ai_play = false;
		}
	}
}


void Environment::render() //TODO: HERE
{
	//TODO: modif render when ai plays
	// get ai struct
	if (this->visual)
		this->visual->render(this->grid.getPlayer(), this->grid.getApples(),
			this->infos);
}


int Environment::checkMove()
{
	int reward = MOVE_REWARD;
	int shrinked = 0; // 0 = neutral, 1 = valid shrink, -1 = nothing to shrink

	if (!this->move)
		return 0;
	this->infos.nb_moves++;
	this->move = false;
	sf::Vector2i pos = this->grid.getPlayer().head_pos;

	if (this->grid.wallHit(pos) || this->grid.occupiedByBody(pos))
	{
		reward = DEATH_REWARD;
		if (!this->ai_play)
		{
			this->visual->setState(GAMEOVER);
			this->visual->gameOverInit(this->infos);
		}
		// else
		// 	this->reset();
	}
	else if (this->grid.occupiedByApples(pos))
	{
		s_apple& apple = this->grid.getAppleByPos(pos);
		if (apple.bonus)
		{
			reward = BONUS_REWARD;
			this->grid.playerGrow();
		}
		else
		{
			shrinked = this->grid.playerShrink();
			reward = MALUS_REWARD;
		}
		int	current_len = this->grid.getPlayerLen();
		if (current_len == 1 && shrinked == -1)
		{
			this->infos.current_size = current_len;
			if (!this->ai_play)
			{
				this->visual->setState(GAMEOVER);
				this->visual->gameOverInit(this->infos);
			}
			// else
			// 	this->reset();
			return DEATH_REWARD;
		}
		this->infos.current_size = current_len;
		if (current_len > this->infos.max_size)
			this->infos.max_size = current_len;
		this->grid.moveApple(apple);
	}
	else if (this->grid.isCloserMove())
		reward = MOVE_CLOSER_REWARD;

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


bool	Environment::getAiPlay() const
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
	// TODO : add choice -> new ai or same ai
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
	this->ai_agent.resetVisualStep();
	std::srand(std::time(nullptr));

	// if (this->ai_play)
	// {
	// 	this->ai_agent.play(*this);
	// 	// TODO : GAME OVER SCREEN FOR AI
	// 	this->visual->setState(GAMEOVER);
	// 	this->visual->gameOverInit(this->infos);
	// }
}


void	Environment::changeWin()
{
	this->input_manager.resetMouse();
}


void	Environment::step(const player_dir &action, learnStep &learn_step)
{
	//TODO: step-by-step mod needs input

	this->grid.movePlayer(action);
	this->move = true;
	this->tick();
	learn_step.reward = this->infos.last_reward;
	learn_step.next_state = this->grid.getAgentState();
	learn_step.done = (learn_step.reward == DEATH_REWARD);
	// this->render(); //TODO : REMOVE ?
}


void	Environment::setNextStep(bool is_next_step)
{
	this->next_step = is_next_step;
}
