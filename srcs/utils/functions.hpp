#ifndef FUNCTIONS_HPP
# define FUNCTIONS_HPP

# include <SFML/Graphics.hpp>
# include <string>

void	drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					int x, int y, int fontSize, sf::Text::Style style, sf::Color color);


void	drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					sf::Vector2f pos, int fontSize, sf::Text::Style style, sf::Color color);

#endif //FUNCTIONS_HPP
