#ifndef VISUAL_HPP
# define VISUAL_HPP

# include <SFML/Graphics.hpp>
# include "../Environment/Grid.hpp"

# define TILE_SIZE 32


class Visual
{
	public:
		Visual(const int &grid_size);
		~Visual();

		sf::RenderWindow	&getWin();
		void				render(s_player &player, std::vector<s_apple> &apples);

	private:
		sf::RenderWindow	window;
		int					grid_visual_size;

		void				drawGrid();
		void				drawElements(s_player &player, std::vector<s_apple> &apples);
};

#endif //VISUAL_HPP
