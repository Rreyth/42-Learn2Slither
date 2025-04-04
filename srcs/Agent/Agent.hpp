#ifndef AGENT_HPP
# define AGENT_HPP

# include <string>
# include <unordered_map>
# include <vector>

# include <utils/structs.hpp>

# define ALPHA 0.9
# define GAMMA 0.95
# define MIN_EPSILON 0.01

class Environment;


class Agent
{
	public:
		Agent(int sessions, bool learn);
		~Agent();

		void	loadQTable(std::string &filename);
		void	saveQTable(std::string &filename);
		void	setSessions(int sessions);
		void	setLearn(bool learn);

		void	play(Environment &env);

	private:
		std::unordered_map<State, std::vector<double>, StateHash> Q;
		int		sessions;
		bool	learn;
		double	epsilon;

		player_dir	choseAction(const State &state);
};


#endif //AGENT_HPP
