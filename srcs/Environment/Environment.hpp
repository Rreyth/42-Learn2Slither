#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include <Environment/Grid.hpp>
#include <Environment/InputManager.hpp>
#include <Visual/Visual.hpp>
#include <utils/parser.hpp>
#include <utils/enums.hpp>
#include <utils/structs.hpp>
#include <Agent/Agent.hpp>


class Environment
{
	public:
		Environment(flags &launch_flags);
		~Environment();

		void	run();
		void	setMove(bool moved);
		void	close();
		void	reset();
		Grid	&getGrid();
		void	startGame(s_settings settings);
		void	changeWin();

	private:
		sf::Clock		clock;
		Visual			*visual = nullptr;
		flags			env_flags;
		Grid			grid;
		InputManager	input_manager;
		bool			running, move, ai_play;
		gameInfos		infos;
		Agent			ai_agent;
		float			ai_move_time;

		void	input();
		void	tick(float delta);
		void	render();
		int		checkMove();

		// TODO: to_state State struct
};


#endif //ENVIRONMENT_HPP
