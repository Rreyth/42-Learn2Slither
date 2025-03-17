#ifndef GRID_HPP
# define GRID_HPP
# include <string>
# include <vector>
# include <SFML/System.hpp>
# include <utils/enums.hpp>


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


class Grid
{
	public:
		Grid(const int &size);
		~Grid();

		void					movePlayer(const player_dir &dir);
		std::string				getAgentView() const;
		s_player&				getPlayer();
		s_apple&				getAppleByPos(const sf::Vector2i &pos);
		std::vector<s_apple>&	getApples();
		bool					occupiedByBody(const sf::Vector2i &pos);
		bool					occupiedByApples(const sf::Vector2i &pos);
		bool					wallHit(const sf::Vector2i &pos);
		void					moveApple(s_apple &apple);
		bool					isCloserMove() const;
		void					playerGrow();
		void					playerShrink();
		int						getPlayerLen() const;
		void					reset();
		void					start(int size);

	private:
		std::vector<s_apple>	apples;
		s_player				player;
		s_body					next_body_part;
		bool					closer;
		int						size;

		void	initPlayer();
		void	initApples();
		bool	occupiedByPlayer(const sf::Vector2i &pos);
		bool	moveInBonusDir(const sf::Vector2i &pos, player_dir dir);
};

#endif //GRID_HPP
