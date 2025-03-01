#ifndef ENVIRONMENT_HPP
# define ENVIRONMENT_HPP
# include "../parser.hpp"
# include "Grid.hpp"
# include "../Visual/Visual.hpp"

class Environment
{
	public:
		Environment(const flags &launch_flags);
		~Environment();
		void	run();

	private:
		// agent class
		sf::Clock	clock;
		Visual		*visual = nullptr;
		flags		env_flags;
		Grid		grid;
		bool		running;

		void	input();
		void	tick(float delta);
		void	render();
		void	close();

		// TODO: to_state State struct
};

#endif //ENVIRONMENT_HPP
