#ifndef GAMESCREEN_HPP
# define GAMESCREEN_HPP

# include <SFML/Graphics.hpp>

# include <utils/TextureManager.hpp>
# include <Visual/Screen/UI/RoundButton.hpp>
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
						std::vector<s_apple> &apples, gameInfos &infos);

	private:
		sf::Vector2i	grid_pos;
		RoundButton		back_button;
		bool			back;
		int				tiles_nb;

		void			gameBackground(sf::RenderWindow &window, TextureManager &texture_manager);
		void			drawGrid(sf::RenderWindow &window, TextureManager &texture_manager);
		void			drawElements(sf::RenderWindow &window, TextureManager &texture_manager,
									s_player &player, std::vector<s_apple> &apples);
		void			displayInfos(sf::RenderWindow &window, sf::Text &text,
									gameInfos &infos);
		bool			isAngle(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos);
		player_dir		getAngleDir(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos);
};


#endif //GAMESCREEN_HPP
