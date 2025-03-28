#ifndef STRUCTS_HPP
# define STRUCTS_HPP

# include <utils/enums.hpp>
# include <SFML/System.hpp>


struct s_apple
{
	bool			bonus;
	sf::Vector2i	pos;
};


struct s_body
{
	sf::Vector2i	pos;
	player_dir		dir;
};


struct s_player
{
	sf::Vector2i		head_pos;
	std::vector<s_body>	body_parts;
	player_dir			dir;
};


struct gameInfos
{
	int	nb_moves = 0,
	current_size = 3,
	max_size = 3,
	last_reward = 0;
};


struct State {
	int bonus_dir;    // 0 = none, 1 = up, 2 = down, 3 = left, 4 = right
	int danger_up;    // distance from 0 (no danger) to 4
	int danger_down;
	int danger_left;
	int danger_right;
	int malus_up;     // distance from 0 (no danger) to 4
	int malus_down;
	int malus_left;
	int malus_right;


	bool operator==(const State &other) const
	{
		return bonus_dir    == other.bonus_dir &&
		       danger_up    == other.danger_up &&
		       danger_down  == other.danger_down &&
		       danger_left  == other.danger_left &&
		       danger_right == other.danger_right &&
		       malus_up     == other.malus_up &&
		       malus_down   == other.malus_down &&
		       malus_left   == other.malus_left &&
		       malus_right  == other.malus_right;
	}
};


struct StateHash {
	std::size_t operator()(const State &s) const {
		std::size_t seed = 0;
		seed ^= std::hash<int>()(s.bonus_dir) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.danger_up) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.danger_down) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.danger_left) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.danger_right) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.malus_up) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.malus_down) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.malus_left) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(s.malus_right) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};


#endif //STRUCTS_HPP
