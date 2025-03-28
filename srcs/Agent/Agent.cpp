#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <Agent/Agent.hpp>

Agent::Agent(int sessions, bool learn)
{
	this->sessions = sessions;
	this->learn = learn;
}


Agent::~Agent()
{
}

void	Agent::loadQTable(std::string &filename)
{
	std::ifstream	file(filename);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file: " + filename);

	std::string	line;
	while (std::getline(file, line))
	{
		size_t	pos = line.find('|');
		if (pos == std::string::npos)
			throw std::runtime_error("Parsing error: Invalid format in line: " + line
									+ "\nexpected format: state | values");

		std::string statePart = line.substr(0, pos);
		std::string valuesPart = line.substr(pos + 1);

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
}


void	Agent::setSessions(int sessions)
{
	this->sessions = sessions;
}





// play
// # chose move + update q table (or create entry for the first encounter)
// # chose move without learn


// move -1
// closer to bonus + 1
// take bonus + 30
// take malus -30
// dead -100

