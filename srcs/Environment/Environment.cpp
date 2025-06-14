#include <Environment/Environment.hpp>

Environment::Environment(flags &launch_flags) : grid(launch_flags.size), ai_agent(launch_flags.sessions, !launch_flags.dontlearn)
{
	this->env_flags = launch_flags;

	if (launch_flags.visual)
		this->visual = new Visual(launch_flags);

	this->running = true;
	this->move = false;
	this->next_step = false;
	this->ai_playing = false;
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
	{ // no visual, only AI running
		this->ai_agent.play(*this, launch_flags.stepmode, launch_flags.info);
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
	if (this->ai_play && this->visual && this->next_step && !this->ai_playing)
	{
		this->ai_playing = true;
		this->next_step = false;
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
			this->visual->aiGameOverInit();
			this->ai_play = false;
		}
		this->ai_playing = false;
	}
}


void Environment::render()
{
	if (this->visual)
		this->visual->render(this->grid.getPlayer(), this->grid.getApples(),
			this->infos, this->ai_move_time, this->ai_agent.getVisualStep());
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


bool Environment::hasMoved() const
{
	return this->move;
}


Grid	&Environment::getGrid()
{
	return this->grid;
}


bool	Environment::getAiPlay() const
{
	return this->ai_play;
}


void	Environment::setAiPlay(bool ai_play)
{
	this->ai_play = ai_play;
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
	this->move = false;
	this->next_step = false;
	this->ai_playing = false;
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
	this->ai_agent.resetVisualStep();
	std::srand(std::time(nullptr));
}


void	Environment::changeWin()
{
	this->input_manager.resetMouse();
}


void	Environment::step(const player_dir &action, learnStep &learn_step)
{
	if (this->env_flags.stepmode && !this->visual)
		waitForUser();

	if (this->env_flags.info)
	{
		this->grid.printAgentView();
		if (this->visual)
		{
			std::string	dirs[] = {"up", "down", "left", "right"};
			std::cout << "Agent choice : " << dirs[action] << std::endl << std::endl;
		}
	}

	this->grid.movePlayer(action);
	this->move = true;
	this->tick();
	learn_step.reward = this->infos.last_reward;
	learn_step.next_state = this->grid.getAgentState();
	learn_step.done = (learn_step.reward == DEATH_REWARD);
}


void	Environment::setNextStep(bool is_next_step)
{
	this->next_step = is_next_step;
}
