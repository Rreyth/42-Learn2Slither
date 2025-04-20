#ifndef AIGAMESCREEN_HPP
# define AIGAMESCREEN_HPP

# include <SFML/Graphics.hpp>

# include <utils/TextureManager.hpp>
# include <Visual/Screen/UI/Button.hpp>
# include <Visual/Screen/UI/RoundButton.hpp>
# include <Environment/Grid.hpp>

# define TILE_SIZE 32
# define MAX_FPS 1000

class AIGameScreen
{
public:
	AIGameScreen();
	~AIGameScreen();

	bool	BackToMenu() const;
	bool	isNextStep() const;

	void	visualInit(sf::RenderWindow &window, TextureManager &texture_manager,
						int tiles_nb);

	void	tick(Mouse &mouse);
	void	render(sf::RenderWindow &window, sf::Text &text,
					TextureManager &texture_manager, s_player &player,
					std::vector<s_apple> &apples, gameInfos &infos,
					float &move_time, visualModAiStep &ai_step);

private:
	sf::Vector2i	grid_pos;
	RoundButton		step_button, back_button;
	bool			back, next_step;
	int				tiles_nb;

	void			gameBackground(sf::RenderWindow &window, TextureManager &texture_manager);
	void			drawGrid(sf::RenderWindow &window, TextureManager &texture_manager);
	void			drawElements(sf::RenderWindow &window, TextureManager &texture_manager,
								s_player &player, std::vector<s_apple> &apples);
	void			displayInfos(sf::RenderWindow &window, sf::Text &text,
								gameInfos &infos, float &move_time,
								visualModAiStep &ai_step);
	bool			isAngle(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos);
	player_dir		getAngleDir(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos);
};


#endif //AIGAMESCREEN_HPP
