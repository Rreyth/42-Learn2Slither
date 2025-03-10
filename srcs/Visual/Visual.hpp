#ifndef VISUAL_HPP
# define VISUAL_HPP

#include <Environment/Grid.hpp>
#include <SFML/Graphics.hpp>
#include <Visual/Screen/Menu.hpp>
#include <utils/TextureManager.hpp>
#include <utils/enums.hpp>
#include <utils/functions.hpp>

#define TILE_SIZE 32
# define MAX_FPS 1000


class Visual
{
	public:
		Visual(flags &launch_flags);
		~Visual();

		sf::RenderWindow	&getWin();
		gameState			&getState();
		void				render(s_player &player, std::vector<s_apple> &apples,
									int nb_moves, int max_size, int reward);
		void				tick(Environment &env, Mouse &mouse);

	private:
		sf::RenderWindow	window;
		sf::Vector2i		grid_pos;
		sf::Font			font;
		sf::Text			text;
		TextureManager		texture_manager;
		Menu				menu;
		gameState			state;
		int					tiles_nb;

		void				drawGrid();
		void				drawElements(s_player &player, std::vector<s_apple> &apples);
		void				displayInfos(int nb_moves, int max_size, int reward);
};

#endif //VISUAL_HPP
