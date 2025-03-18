#ifndef MOUSE_HPP
# define MOUSE_HPP

# include <SFML/Graphics.hpp>
# include <utils/enums.hpp>


class Mouse
{
public:
	Mouse(void);
	~Mouse();

	int		getX(void) const;
	int		getY(void) const;
	bool	isPressed(mouse_button mbut) const;
	bool	isDown(mouse_button mbut) const;

	void	updatePosition(sf::RenderWindow &window);
	void	updateMbutton(mouse_button mbut, bool state);

	bool	inRectangle(int x, int y, int w, int h) const;
	bool	inRectangle(sf::Vector2i pos, sf::Vector2i size) const;

private:
	int			x, y;
	bool		pressed[3];
	bool		down[3];
};

#endif
