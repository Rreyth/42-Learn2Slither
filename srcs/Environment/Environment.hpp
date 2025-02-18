#ifndef ENVIRONMENT_HPP
# define ENVIRONMENT_HPP
# include "../parser.hpp"
# include "Grid.hpp"

class Environment
{
	public:
		Environment(const flags &launch_flags);
		~Environment();
		void	run();

	private:
		//visual class
		//agent class
		flags		env_flags;
		Grid		grid;

		//methods
		//TODO: to_state State struct
};

#endif //ENVIRONMENT_HPP
