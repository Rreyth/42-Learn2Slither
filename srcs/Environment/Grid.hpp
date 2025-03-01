#ifndef GRID_HPP
#define GRID_HPP
#include <string>
#include <vector>
#include <SFML/System.hpp>


struct s_apple
{
	bool			bonus;
	sf::Vector2i	pos;
};


enum player_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


struct s_player
{
	sf::Vector2i				head_pos;
	std::vector<sf::Vector2i>	body_pos;
	player_dir					dir;
};


class Grid
{
	public:
		Grid(const int &size);
		~Grid();

		void					movePlayer(const player_dir &dir);
		std::string				getAgentView() const;
		s_player&				getPlayer();
		std::vector<s_apple>&	getApples();
		std::string&			getGrid();

	private:
		std::vector<s_apple>	apples;
		s_player			player;
		std::string			grid;
		int					size;

		void	initPlayer();
		void	initApples();
		void	initGrid();
		bool	occupiedByPlayer(const sf::Vector2i &pos);
		bool	occupiedByApples(const sf::Vector2i &pos);
};

#endif //GRID_HPP
