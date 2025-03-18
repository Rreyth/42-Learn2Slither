#ifndef STRUCTS_HPP
# define STRUCTS_HPP


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


#endif //STRUCTS_HPP
