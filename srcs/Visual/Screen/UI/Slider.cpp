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


Slider::Slider(float min, float max, float value, std::string type, sf::Vector2i pos, sf::Vector2i size,
				sprite_name onSprite, sprite_name offSprite, TextureManager &texture_manager)
{
	this->min = min;
	this->max = max;
	this->value = value;
	this->pos = pos;
	this->size = size;
	this->type = type;

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
	this->type = other.type;

	return *this;
}

float	Slider::getValue() const
{
	return this->value;
}


void	Slider::setValue(float value)
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
		float range = this->max - this->min;
		float relative_pos = this->button.getPos().x - (this->pos.x - this->size.x / 2);
		float val_perc = relative_pos / this->size.x;
		if (this->type == "int")
			this->value = std::round(val_perc * range + this->min);
		else
			this->value = val_perc * range + this->min;
	}
}


void	Slider::draw(sf::RenderWindow &window, sf::Text &text, TextureManager &textureManager)
{
	this->back_line.draw(window);
	this->button.draw(window, text, textureManager);

	int dist = (this->min < 100 ? 20 : (this->min < 1000 ? 25 : 30));
	sf::Vector2f txt_pos(this->pos.x - (this->size.x / 2) - dist, this->pos.y - 2);
	std::string	value_txt[3];
	value_txt[0] = (isInt(this->min) ? std::to_string(static_cast<int>(this->min)) : formatFloat(this->min));
	value_txt[1] = (isInt(this->max) ? std::to_string(static_cast<int>(this->max)) : formatFloat(this->max));
	value_txt[2] = (isInt(this->value) ? std::to_string(static_cast<int>(this->value)) : formatFloat(this->value));

	drawText(window, text, value_txt[0], txt_pos, 20, sf::Text::Regular, sf::Color::White);

	dist = (this->max < 100 ? 20 : (this->max < 1000 ? 25 : 30));
	txt_pos.x = this->pos.x + this->size.x / 2 + dist;

	drawText(window, text, value_txt[1], txt_pos, 20, sf::Text::Regular, sf::Color::White);

	txt_pos.x = this->button.getPos().x;
	txt_pos.y -= this->size.y * 3;

	drawText(window, text, value_txt[2], txt_pos, 20, sf::Text::Regular, sf::Color::White);
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
