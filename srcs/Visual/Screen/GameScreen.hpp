#ifndef GAMESCREEN_HPP
# define GAMESCREEN_HPP

# include <SFML/Graphics.hpp>

# include <utils/TextureManager.hpp>
# include <Visual/Screen/UI/Button.hpp>
# include <Environment/Grid.hpp>

# define TILE_SIZE 32
# define MAX_FPS 1000

class GameScreen
{
	public:
		GameScreen();
		~GameScreen();

		bool	BackToMenu() const;


		void	visualInit(sf::RenderWindow &window, TextureManager &texture_manager,
							int tiles_nb);

		void	tick(Mouse &mouse);
		void	render(sf::RenderWindow &window, sf::Text &text,
						TextureManager &texture_manager, s_player &player,
						std::vector<s_apple> &apples, int nb_moves, int max_size,
						int reward);

	private:
		sf::Vector2i	grid_pos;
		Button			back_button;
		bool			back;
		int				tiles_nb;

		void			drawGrid(sf::RenderWindow &window, TextureManager &texture_manager);
		void			drawElements(sf::RenderWindow &window, TextureManager &texture_manager,
									s_player &player, std::vector<s_apple> &apples);
		void			displayInfos(sf::RenderWindow &window, sf::Text &text,
									int nb_moves, int max_size, int reward);
		bool			isAngle(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos);
		player_dir		getAngleDir(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos);
};


#endif //GAMESCREEN_HPP
