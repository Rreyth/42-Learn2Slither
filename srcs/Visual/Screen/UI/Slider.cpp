#include <Visual/Screen/UI/Slider.hpp>
#include <utils/functions.hpp>
#include <cmath>

Slider::Slider()
{
	this->pos = {0, 0};
	this->size = {0, 0};
	this->min = 0;
	this->max = 0;
	this->value = 0;
}


Slider::Slider(int min, int max, int value, sf::Vector2i pos, sf::Vector2i size,
				sprite_name onSprite, sprite_name offSprite, TextureManager &texture_manager)
{
	this->min = min;
	this->max = max;
	this->value = value;
	this->pos = pos;
	this->size = size;

	float range = max - min;
	float val_perc = (value - min) / range;
	int val_pos = val_perc * size.x + pos.x - (size.x / 2);

	this->button = Button("", 10, sf::Color::White, val_pos, pos.y,
						size.y * 2, size.y * 2, onSprite, offSprite, texture_manager);
	this->back_line.rect = sf::RectangleShape(sf::Vector2f(size));
	this->back_line.rect.setFillColor(sf::Color(200, 200, 200));
	this->back_line.rect.setPosition(sf::Vector2f(pos.x - (size.x / 2), pos.y - (size.y / 2)));

	this->back_line.back_rect = sf::RectangleShape(sf::Vector2f(size.x, size.y + 4));
	this->back_line.back_rect.setFillColor(sf::Color::White);
	this->back_line.back_rect.setPosition(sf::Vector2f(pos.x - (size.x / 2), pos.y - (size.y / 2) - 2));

	this->back_line.circles[0] = sf::CircleShape(size.y / 2);
	this->back_line.circles[1] = sf::CircleShape(size.y / 2);
	this->back_line.circles[0].setFillColor(sf::Color(200, 200, 200));
	this->back_line.circles[1].setFillColor(sf::Color(200, 200, 200));
	this->back_line.circles[0].setOutlineColor(sf::Color::White);
	this->back_line.circles[1].setOutlineColor(sf::Color::White);
	this->back_line.circles[0].setOutlineThickness(2);
	this->back_line.circles[1].setOutlineThickness(2);

	sf::Vector2f circle_pos(pos.x - (size.x / 2) - (size.y / 2), pos.y - (size.y / 2));
	this->back_line.circles[0].setPosition(circle_pos);

	circle_pos.x = pos.x + (size.x / 2) - (size.y / 2);
	this->back_line.circles[1].setPosition(circle_pos);
}


Slider::~Slider()
{
}


Slider	&Slider::operator=(const Slider &other)
{
	this->min = other.min;
	this->max = other.max;
	this->value = other.value;
	this->pos = other.pos;
	this->size = other.size;
	this->button = other.button;
	this->back_line = other.back_line;

	return *this;
}

int	Slider::getValue() const
{
	return this->value;
}


void	Slider::setValue(int value)
{
	this->value = value;
}


void	Slider::tick(Mouse &mouse, sf::RenderWindow &window)
{
	sf::Vector2i check_pos(this->pos.x - (this->size.x / 2) - (size.y / 2),
						this->pos.y - (this->size.y / 2));
	sf::Vector2i check_size(this->size.x + this->size.y, this->size.y);
	if (mouse.inRectangle(check_pos, check_size) && mouse.isPressed(MBUT_LEFT))
		this->moveSelector(mouse.getX(), this->pos.y);

	this->button.tick(mouse);

	if (this->button.isDown())
	{
		mouse.updatePosition(window);
		this->moveSelector(mouse.getX(), this->pos.y);
	}

	float range = this->max - this->min;
	float relative_pos = this->button.getPos().x - (this->pos.x - this->size.x / 2);
	float val_perc = relative_pos / this->size.x;
	this->value = std::round(val_perc * range + this->min);
}


void	Slider::draw(sf::RenderWindow &window, sf::Text &text, TextureManager &textureManager)
{
	this->back_line.draw(window);
	this->button.draw(window, text, textureManager);

	sf::Vector2f txt_pos(this->pos.x - (this->size.x / 2) - 20, this->pos.y - 2);

	drawText(window, text, std::to_string(this->min), txt_pos, 20, sf::Text::Regular, sf::Color::White);

	txt_pos.x = this->pos.x + this->size.x / 2 + 20;

	drawText(window, text, std::to_string(this->max), txt_pos, 20, sf::Text::Regular, sf::Color::White);

	txt_pos.x = this->button.getPos().x;
	txt_pos.y -= 30;
	drawText(window, text, std::to_string(this->value), txt_pos, 20, sf::Text::Regular, sf::Color::White);
}


void	Slider::moveSelector(int x, int y)
{
	int max_pos = this->pos.x + this->size.x / 2;
	int min_pos = this->pos.x - this->size.x / 2;
	if (x > max_pos)
		x = max_pos;
	else if (x < min_pos)
		x = min_pos;

	this->button.setPos(x, y);
}
