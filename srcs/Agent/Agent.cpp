#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>

#include <Agent/Agent.hpp>
#include <Environment/Environment.hpp>


Agent::Agent(int sessions, bool learn) : visualStep()
{
	this->sessions = sessions;
	this->learn = learn;
	this->loaded = false;
	this->epsilon = START_EPSILON;
	this->visualStep.decay = std::pow(MIN_EPSILON / START_EPSILON, 1 / static_cast<double>(this->sessions));
	this->visualStep.total_sessions = this->sessions;
}


Agent::~Agent()
{
}


void	Agent::loadQTable(std::string &filename)
{
	std::cout << "Loading QTable from " << filename << std::endl;

	std::ifstream	file(filename);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file: " + filename);

	std::string	line;
	while (std::getline(file, line))
	{
		size_t	q_pos = line.find('|');

		if (q_pos == std::string::npos)
			throw std::runtime_error("Parsing error: Invalid format in line: " + line
									+ "\nexpected format: 'state | values'");

		std::string statePart = line.substr(0, q_pos);
		std::string valuesPart = line.substr(q_pos + 1);

		std::istringstream	stateStream(statePart);
		State	s{};

		stateStream >> s.bonus_dir >> s.danger_up >> s.danger_down
					>> s.danger_left >> s.danger_right
					>> s.malus_up >> s.malus_down >> s.malus_left >> s.malus_right;

		std::istringstream	qStream(valuesPart);
		std::vector<double> q_values(4, 0.0);
		for (int i = 0; i < 4; ++i)
			qStream >> q_values[i];

		if (stateStream.fail() || qStream.fail())
			throw std::runtime_error("Parsing error: Invalid or incomplete line: " + line
									+ "\nexpected 9 values for state | 4 values for actions");

		this->Q[s] = q_values;
	}
	file.close();
	this->loaded = true;
	this->epsilon = (this->learn) ? 0.1 : MIN_EPSILON;
}


void Agent::saveQTable(std::string &filename)
{
	std::cout << "Saving QTable to " << filename << std::endl;
	std::ofstream	file(filename, std::ofstream::out | std::ofstream::trunc);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file for writing: " + filename);

	for (const auto &entry : this->Q)
	{
		const State &s = entry.first;
		const std::vector<double> &q_values = entry.second;

		file << s.bonus_dir << " "
			 << s.danger_up << " "
			 << s.danger_down << " "
			 << s.danger_left << " "
			 << s.danger_right << " "
			 << s.malus_up << " "
			 << s.malus_down << " "
			 << s.malus_left << " "
			 << s.malus_right;

		file << " | ";

		for (const double q : q_values)
			file << q << " ";

		file << "\n";
	}
	file.close();
}


void	Agent::setLearn(bool learn)
{
	this->learn = learn;
	if (!learn)
		this->epsilon = MIN_EPSILON;
	else
		this->epsilon = (this->loaded) ? 0.1 : START_EPSILON;
}


void	Agent::setSessions(int sessions)
{
	this->sessions = sessions;
}


void	Agent::play(Environment &env, bool step_mode, bool info)
{
	State				state;
	learnStep			learn_step;
	player_dir			action;
	std::vector<double>	q_values;
	double				old_value, next_max, decay;
	int					step_counter, max_step, curr_len, max_len,
						bonus_counter, max_bonus, malus_counter, max_malus;

	max_step = 0;
	max_len = 0;
	max_bonus = 0;
	max_malus = 0;
	decay = std::pow(MIN_EPSILON / START_EPSILON, 1 / static_cast<double>(this->sessions));

	if (this->learn)
		std::cout << "Starting training for " << this->sessions << " sessions" << std::endl;
	else
		std::cout << "Playing without learning for " << this->sessions << " sessions" << std::endl;

	for (int i = 0; i < this->sessions; ++i)
	{
		bonus_counter = 0;
		malus_counter = 0;
		step_counter = 0;
		curr_len = 0;
		learn_step.done = false;
		state = env.reset();
		while (!learn_step.done)
		{
			action = this->choseAction(state);

			env.step(action, learn_step);
			if (step_mode || info)
				printStepInfos(i + 1, step_counter + 1, action, learn_step);

			if (learn_step.reward == BONUS_REWARD)
				bonus_counter++;
			if (learn_step.reward == MALUS_REWARD)
				malus_counter++;

			old_value = this->Q[state][action];
			if (this->Q.contains(learn_step.next_state))
			{
				q_values = this->Q[learn_step.next_state];
				next_max = *std::ranges::max_element(q_values);
			}
			else
				next_max = 0.0;

			if (this->learn)
				this->Q[state][action] = (1 - ALPHA) * old_value + ALPHA * (learn_step.reward + GAMMA * next_max);
			step_counter++;
			curr_len = env.getGrid().getPlayerLen();
			if (curr_len > max_len)
				max_len = curr_len;
			state = learn_step.next_state;
		}
		this->epsilon = std::max(MIN_EPSILON, this->epsilon * decay);
		if (step_counter > max_step)
			max_step = step_counter;
		if (malus_counter > max_malus)
			max_malus = malus_counter;
		if (bonus_counter > max_bonus)
			max_bonus = bonus_counter;

		if (step_mode || info)
			printSessionInfos(i + 1, this->sessions, step_counter, curr_len, bonus_counter, malus_counter);

	}
	std::cout << "End of sessions:" << std::endl;
	if (this->learn)
		std::cout << "Trained for " << this->sessions << " sessions" << std::endl;
	else
		std::cout << "Played through " << this->sessions << " sessions" << std::endl;
	std::cout << "Max life time (in steps):\t" << max_step << std::endl
	<< "Max snake length:\t\t" << max_len << std::endl
	<< "Max eaten green apples:\t" << max_bonus << std::endl
	<< "Max eaten red apples:\t" << max_malus << std::endl;
}


void	Agent::visualPlay(Environment &env, State &state)
{
	player_dir			action;
	double				old_value, next_max;
	std::vector<double>	q_values;

	action = choseAction(state);
	env.step(action, this->visualStep.step);

	if (this->visualStep.step.reward == BONUS_REWARD)
		this->visualStep.bonus_count++;
	else if (this->visualStep.step.reward == MALUS_REWARD)
		this->visualStep.malus_count++;

	old_value = this->Q[state][action];
	if (this->Q.contains(this->visualStep.step.next_state))
	{
		q_values = this->Q[this->visualStep.step.next_state];
		next_max = *std::ranges::max_element(q_values);
	}
	else
		next_max = 0.0;

	if (this->learn)
		this->Q[state][action] = (1 - ALPHA) * old_value + ALPHA * (this->visualStep.step.reward + GAMMA * next_max);
	this->visualStep.step_count++;
	this->visualStep.curr_len = env.getGrid().getPlayerLen();
	if (this->visualStep.curr_len > this->visualStep.max_len)
		this->visualStep.max_len = this->visualStep.curr_len;
}


void	Agent::visualStepEnd()
{
	this->epsilon = std::max(MIN_EPSILON, this->epsilon * this->visualStep.decay);
	if (this->visualStep.step_count > this->visualStep.max_step)
		this->visualStep.max_step = this->visualStep.step_count;
	if (this->visualStep.malus_count > this->visualStep.max_malus)
		this->visualStep.max_malus = this->visualStep.malus_count;
	if (this->visualStep.bonus_count > this->visualStep.max_bonus)
		this->visualStep.max_bonus = this->visualStep.bonus_count;
	this->visualStep.session_count++;
	this->visualStep.step_count = 0;
	this->visualStep.malus_count = 0;
	this->visualStep.bonus_count = 0;
}


player_dir Agent::choseAction(const State &state)
{
	player_dir action;

	double randomVal = static_cast<double>(std::rand()) / RAND_MAX;

	if (!this->Q.contains(state)) // state not in Q table
	{
		this->Q[state] = std::vector<double>(4, 10.0);
		action = static_cast<player_dir>(std::rand() % 4);
	}
	else if (randomVal < this->epsilon) // exploration
	{
		action = static_cast<player_dir>(std::rand() % 4);
	}
	else
	{
		int best = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (this->Q[state][i] > this->Q[state][best])
				best = i;
		}
		action = static_cast<player_dir>(best);
	}

	return action;
}


visualModAiStep &Agent::getVisualStep()
{
	return this->visualStep;
}


void	Agent::resetVisualStep()
{
	this->visualStep = visualModAiStep();
	this->visualStep.decay = std::pow(MIN_EPSILON / START_EPSILON, 1 / static_cast<double>(this->sessions));
	this->visualStep.total_sessions = this->sessions;
}


void	Agent::resetAI()
{
	this->Q.clear();
}