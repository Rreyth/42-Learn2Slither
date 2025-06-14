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
			int x, int y, float w, float h,
			sprite_name onSprite, sprite_name offSprite,
			TextureManager &texture_manager);
	~Button();

	bool			getPressed(void);
	bool			isDown(void);
	void			setText(std::string text);
	sf::Vector2i	getPos(void);
	void			setPos(int x, int y);
	void			setPos(sf::Vector2i pos);

	void	tick(Mouse &mouse);
	void	draw(sf::RenderWindow &window, sf::Text &text, TextureManager &textureManager);

	Button	&operator=(const Button &btn);

private:
	sf::Vector2f	scaleOn, scaleOff;
	sf::Color		textColor;
	sprite_name		onSprite, offSprite;
	std::string		text;
	int				x, y, w, h, fontSize;
	bool			mouseOver, pressed, down;
};


#endif
