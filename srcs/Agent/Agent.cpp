#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>

#include <Agent/Agent.hpp>
#include <Environment/Environment.hpp>


Agent::Agent(int sessions, bool learn)
{
	this->sessions = sessions;
	this->learn = learn;
	this->epsilon = 1.0;
}


Agent::~Agent()
{
}


void	Agent::loadQTable(std::string &filename)
{
	std::cout << "Loading QTable from " << filename << std::endl;

	bool	has_epsilon = false;

	std::ifstream	file(filename);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file: " + filename);

	std::string	line;
	while (std::getline(file, line))
	{
		size_t	q_pos = line.find('|');
		size_t	e_pos = line.find(':');

		if (q_pos == std::string::npos && e_pos == std::string::npos)
			throw std::runtime_error("Parsing error: Invalid format in line: " + line
									+ "\nexpected format: 'state | values' or 'epsilon: value'");

		if (e_pos != std::string::npos)
		{
			if (has_epsilon)
				throw std::runtime_error("Parsing error: File contains more than one epsilon");
			std::istringstream epsilonStream(line.substr(e_pos + 1));
			epsilonStream >> this->epsilon;
			if (epsilonStream.fail() || line.substr(0, e_pos) != "epsilon")
				throw std::runtime_error("Parsing error: Invalid or incomplete line: " + line
										+ "\nexpected 'epsilon: value'");
			has_epsilon = true;
			if (this->epsilon > 1.0)
				this->epsilon = 1.0;
			continue;
		}

		std::string statePart = line.substr(0, q_pos);
		std::string valuesPart = line.substr(q_pos + 1);

		std::istringstream	stateStream(statePart);
		State	s;

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
	file << "epsilon: " << this->epsilon << "\n";
	file.close();
}


void	Agent::setLearn(bool learn)
{
	this->learn = learn;
}


void	Agent::setSessions(int sessions)
{
	this->sessions = sessions;
}


void	Agent::play(Environment &env)
{
	State				state;
	learnStep			learn_step;
	player_dir			action;
	std::vector<double>	q_values;
	double				old_value, next_max, decay;
	int					step_counter, max_step, curr_len, max_len;

	max_step = 0;
	max_len = 0;
	decay = std::pow(0.007 / 1, 1 / static_cast<double>(this->sessions));
	std::srand(std::time(nullptr));

	if (this->learn)
		std::cout << "Starting training for " << this->sessions << " sessions" << std::endl;
	else
		std::cout << "Playing without learning for " << this->sessions << " sessions" << std::endl;

	for (int i = 0; i < this->sessions; ++i)
	{
		curr_len = 0;
		step_counter = 0;
		learn_step.done = false;
		state = env.reset();
		while (!learn_step.done)
		{
			action = this->choseAction(state);

			env.step(action, learn_step);
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
			state = learn_step.next_state;
			step_counter++;
			curr_len = env.getGrid().getPlayerLen();
			if (curr_len > max_len)
				max_len = curr_len;
		}
		this->epsilon = std::max(MIN_EPSILON, this->epsilon * decay);
		if (step_counter > max_step)
			max_step = step_counter;
		// std::cout << "Session " << i + 1 << " / " << this->sessions << ":" << std::endl
		// << "life time (in steps):\t" << step_counter << std::endl
		// << "final length:\t\t" << curr_len << std::endl << std::endl;
	}
	std::cout << "End of sessions:" << std::endl;
	if (this->learn)
		std::cout << "Trained for " << this->sessions << " sessions" << std::endl;
	else
		std::cout << "Played through " << this->sessions << " sessions" << std::endl;
	std::cout << "Max life time (in steps):\t" << max_step << std::endl
	<< "Max snake length:\t\t" << max_len << std::endl;
}


player_dir	Agent::choseAction(const State &state)
{
	player_dir	action;

	double randomVal = static_cast<double>(std::rand()) / RAND_MAX;

	if (!this->Q.contains(state)) // state not in Q table
	{
		this->Q[state] = std::vector<double>(4, 0.0);
		action = static_cast<player_dir>(std::rand() % 4);
	}
	else if (this->learn && randomVal < this->epsilon) // exploration
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
