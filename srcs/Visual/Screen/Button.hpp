#ifndef BUTTON_HPP
# define BUTTON_HPP

# include <utils/TextureManager.hpp>
# include <utils/Mouse.hpp>

# include <SFML/Graphics.hpp>
# include <iostream>

class Button
{
public:
	Button(void);
	Button(std::string text, int fontSize, sf::Color textColor,
			int x, int y, float w, float h, sprite_name onSprite, sprite_name offSprite);
	~Button();

	bool	getPressed(void);
	void	setText(std::string text);

	void	tick(Mouse &mouse);
	void	draw(sf::RenderWindow &window, sf::Text &text, TextureManager &textureManager);

	Button	&operator=(const Button &btn);

private:
	int			x, y, w, h, fontSize;
	sprite_name	onSprite, offSprite;
	bool		mouseOver, pressed;
	sf::Color	textColor, colorOff, colorOn;
	std::string	text;
};


#endif
