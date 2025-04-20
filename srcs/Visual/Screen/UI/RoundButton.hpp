#ifndef ROUNDBUTTON_HPP
# define ROUNDBUTTON_HPP

# include <utils/TextureManager.hpp>
# include <utils/Mouse.hpp>
# include <Visual/Screen/UI/RoundedRectangleShape.hpp>

# include <SFML/Graphics.hpp>
#include <iostream>


class RoundButton
{
public:
	RoundButton(void);
	RoundButton(std::string text, int fontSize, sf::Color textColor,
			sf::Vector2i pos, sf::Vector2i size, float corner_radius,
			sf::Color onColor, sf::Color offColor, sf::Color backColor);
	~RoundButton();

	bool			getPressed(void);
	bool			isDown(void);
	void			setText(std::string text);
	sf::Vector2i	getPos(void) const;
	void			setPos(sf::Vector2i new_pos);

	void	tick(Mouse &mouse);
	void	draw(sf::RenderWindow &window, sf::Text &text);

	RoundButton	&operator=(const RoundButton &btn);

private:
	sf::Color				textColor, backColor, frontColorOff, frontColorOn;
	std::string				text;
	sf::Vector2i			pos, size;
	RoundedRectangleShape	visual;
	int						fontSize;
	float					corner_radius;
	bool					mouseOver, pressed, down;

	void			initRoundedVisual(void);
};


#endif
