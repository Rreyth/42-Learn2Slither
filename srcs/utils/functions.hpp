#ifndef FUNCTIONS_HPP
# define FUNCTIONS_HPP

# include <SFML/Graphics.hpp>
# include <utils/TextureManager.hpp>
# include <string>
# include <utils/enums.hpp>
# include <utils/structs.hpp>

void		drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					int x, int y, int fontSize, sf::Text::Style style, sf::Color color);

void		drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					sf::Vector2f pos, int fontSize, sf::Text::Style style, sf::Color color);

bool		isInt(float x);

std::string	formatFloat(float x);

void		drawBackground(sf::RenderWindow &window, TextureManager &texture_manager);

void		waitForUser();

void		printStepInfos(const int &session_counter, const int &step_counter,
						const player_dir &action, const learnStep &learn_step);

void		printSessionInfos(const int &session_counter, const int &session_total, const int &step_counter,
				const int &len, const int &bonus_counter, const int &malus_counter);

#endif //FUNCTIONS_HPP
