#ifndef VISUAL_HPP
# define VISUAL_HPP

# include <SFML/Graphics.hpp>
# include <Environment/Grid.hpp>

# define TILE_SIZE 32
# define MAX_FPS 1000


class Visual
{
	public:
		Visual(const int &tiles);
		~Visual();

		sf::RenderWindow	&getWin();
		void				render(s_player &player, std::vector<s_apple> &apples,
									int nb_moves, int max_size, int reward);

	private:
		sf::RenderWindow	window;
		sf::Vector2i		grid_pos;
		sf::Font			font;
		int					tiles_nb;

		void				drawGrid();
		void				drawElements(s_player &player, std::vector<s_apple> &apples);
		void				displayInfos(int nb_moves, int max_size, int reward);
};

#endif //VISUAL_HPP
