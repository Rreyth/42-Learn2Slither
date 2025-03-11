#include <utils/functions.hpp>
#include <cmath>

void	drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					int x, int y, int fontSize, sf::Text::Style style, sf::Color color)
{
	float w, h;

	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setStyle(style);
	w = text.getLocalBounds().size.x;
	h = text.getLocalBounds().size.y + fontSize / 2;

	sf::Vector2f pos(x - w / 2, y - h / 2);

	text.setPosition(pos);

	text.setFillColor(color);
	window.draw(text);
}


void	drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					sf::Vector2f pos, int fontSize, sf::Text::Style style, sf::Color color)
{
	float w, h;

	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setStyle(style);
	w = text.getLocalBounds().size.x;
	h = text.getLocalBounds().size.y + fontSize / 2;

	sf::Vector2f accurate_pos(pos.x - w / 2, pos.y - h / 2);

	text.setPosition(accurate_pos);

	text.setFillColor(color);
	window.draw(text);
}


bool	isInt(float x)
{
	return (x == std::trunc(x));
}


std::string	formatFloat(float x)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << x;
	std::string s = oss.str();
	return s;
}
