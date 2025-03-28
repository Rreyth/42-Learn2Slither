#ifndef AGENT_HPP
# define AGENT_HPP

# include <string>
# include <unordered_map>
# include <vector>

# include <utils/structs.hpp>

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
};


#endif //AGENT_HPP
