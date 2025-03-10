#include <utils/Mouse.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constructors and destructor
////////////////////////////////////////////////////////////////////////////////

Mouse::Mouse(void)
{
	this->x = 0;
	this->y = 0;
	for (int i = 0; i < 3; i++)
	{
		this->pressed[i] = false;
		this->down[i] = false;
	}
}


Mouse::~Mouse()
{
}

////////////////////////////////////////////////////////////////////////////////
// Getters and setters
////////////////////////////////////////////////////////////////////////////////

int	Mouse::getX(void) const
{
	return (this->x);
}


int	Mouse::getY(void) const
{
	return (this->y);
}


bool	Mouse::isPressed(mouse_button mbut) const
{
	return (this->pressed[mbut]);
}


bool	Mouse::isDown(mouse_button mbut) const
{
	return (this->down[mbut]);
}

////////////////////////////////////////////////////////////////////////////////
// Public methods
////////////////////////////////////////////////////////////////////////////////

void	Mouse::updatePosition(sf::RenderWindow &window)
{
	sf::Vector2i posInWindow = sf::Mouse::getPosition(window);
	sf::Vector2f posInView = window.mapPixelToCoords(posInWindow);
	this->x = posInView.x;
	this->y = posInView.y;
	for (int i = 0; i < 3; i++)
		this->pressed[i] = false;
}


void	Mouse::updateMbutton(mouse_button mbut, bool state)
{
	if (state)
	{
		this->pressed[mbut] = true;
		this->down[mbut] = true;
	}
	else
		this->down[mbut] = false;
}


bool	Mouse::inRectangle(int x, int y, int w, int h) const
{
	return (this->x <= x + w && this->x >= x &&
			this->y <= y + h && this->y >= y);
}


bool	Mouse::inRectangle(sf::Vector2i pos, sf::Vector2i size) const
{
	return (this->x <= pos.x + size.x && this->x >= pos.x &&
			this->y <= pos.y + size.y && this->y >= pos.y);
}
