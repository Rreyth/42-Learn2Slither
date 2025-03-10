#ifndef SLIDER_HPP
# define SLIDER_HPP

# include <SFML/Graphics.hpp>
# include <utils/TextureManager.hpp>
# include <Visual/Screen/UI/Button.hpp>


struct rounded_rect
{
	sf::RectangleShape	rect, back_rect;
	sf::CircleShape		circles[2];

	void	draw(sf::RenderWindow &window) const
	{
		window.draw(back_rect);
		window.draw(circles[0]);
		window.draw(circles[1]);
		window.draw(rect);
	}
};

class Slider
{
	public:
		Slider();
		Slider(int min, int max, int value, sf::Vector2i pos, sf::Vector2i size,
			   sprite_name onSprite, sprite_name offSprite, TextureManager &texture_manager);
		~Slider();

		int		getValue() const;
		void	setValue(int value);
		void	tick(Mouse &mouse, sf::RenderWindow &window);
		void	draw(sf::RenderWindow &window, sf::Text &text, TextureManager &textureManager);

		Slider	&operator=(const Slider &other);

	private:
		sf::Vector2i	pos, size;
		rounded_rect	back_line;
		Button			button;
		int				min, max, value;

		void			moveSelector(int x, int y);

};


#endif //SLIDER_HPP
