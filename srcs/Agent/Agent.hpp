#ifndef AGENT_HPP
# define AGENT_HPP

# include <string>
# include <unordered_map>
# include <vector>

# include <utils/structs.hpp>

# define ALPHA 0.6
# define GAMMA 0.85
# define MIN_EPSILON 0.001
# define START_EPSILON 0.9
# define BONUS_REWARD 50
# define MALUS_REWARD -30
# define DEATH_REWARD -100
# define MOVE_REWARD -1
# define MOVE_CLOSER_REWARD 5

class Environment;


class Agent
{
	public:
		Agent(int sessions, bool learn);
		~Agent();

		void			loadQTable(std::string &filename);
		void			saveQTable(std::string &filename);
		void			setSessions(int sessions);
		void			setLearn(bool learn);

		void			play(Environment &env, bool step_mode, bool info);
		void			visualPlay(Environment &env, State &state);
		void			visualStepEnd();

		visualModAiStep	&getVisualStep();
		void			resetVisualStep();
		void			resetAI();

	private:
		std::unordered_map<State, std::vector<double>, StateHash> Q;
		visualModAiStep	visualStep;
		int				sessions;
		bool			learn, loaded;
		double			epsilon;

		player_dir	choseAction(const State &state);
};


#endif //AGENT_HPP
