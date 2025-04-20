#include <Visual/Screen/UI/RoundButton.hpp>
#include <utils/functions.hpp>

RoundButton::RoundButton()
{
	this->pos = {0, 0};
	this->size = {0, 0};

	this->text = "";
	this->fontSize = 0;
	this->textColor = sf::Color::Black;
	this->backColor = sf::Color::White;
	this->frontColorOn = sf::Color(200, 200, 200);
	this->frontColorOff = sf::Color(100, 100, 100);

	this->mouseOver = false;
	this->pressed = false;
	this->down = false;
}

RoundButton::RoundButton(std::string text, int fontSize, sf::Color textColor,
				sf::Vector2i pos, sf::Vector2i size, float corner_radius,
				sf::Color onColor, sf::Color offColor, sf::Color backColor)
{
	this->pos = pos;
	this->size = size;

	this->text = text;
	this->fontSize = fontSize;
	this->textColor = textColor;
	this->backColor = backColor;
	this->frontColorOn = onColor;
	this->frontColorOff = offColor;

	this->mouseOver = false;
	this->pressed = false;
	this->down = false;

	this->corner_radius = corner_radius;

	this->initRoundedVisual();
}


void	RoundButton::initRoundedVisual()
{
	this->visual = RoundedRectangleShape(sf::Vector2f(this->size), this->corner_radius);
	this->visual.setFillColor(this->frontColorOff);
	this->visual.setPosition(sf::Vector2f(this->pos.x - this->size.x / 2, this->pos.y - this->size.y / 2));
	this->visual.setOutlineColor(this->backColor);
	this->visual.setOutlineThickness(2);
}



RoundButton::~RoundButton()
{

}

////////////////////////////////////////////////////////////////////////////////
// Getters and setters
////////////////////////////////////////////////////////////////////////////////

bool RoundButton::getPressed()
{
	return (this->pressed);
}


bool RoundButton::isDown()
{
	return (this->down);
}


void	RoundButton::setText(std::string text)
{
	this->text = text;
}


sf::Vector2i	RoundButton::getPos() const
{
	return this->pos;
}


void	RoundButton::setPos(sf::Vector2i new_pos)
{
	this->pos = new_pos;
}


////////////////////////////////////////////////////////////////////////////////
// Public methods
////////////////////////////////////////////////////////////////////////////////

void RoundButton::draw(sf::RenderWindow &window, sf::Text &text)
{
	if (!this->mouseOver)
		this->visual.setFillColor(this->frontColorOff);
	else
		this->visual.setFillColor(this->frontColorOn);

	window.draw(this->visual);

	drawText(window, text, this->text, this->pos.x, this->pos.y,
		this->fontSize, sf::Text::Regular, this->textColor);
}


void RoundButton::tick(Mouse &mouse)
{
	const sf::Vector2i collide_pos(this->pos.x - (size.x / 2), this->pos.y - (size.y / 2));
	this->mouseOver = mouse.inRectangle(collide_pos, this->size);
	this->pressed = this->mouseOver && mouse.isPressed(MBUT_LEFT);
	if (mouse.isDown(MBUT_LEFT) && this->down)
		return;
	this->down = this->mouseOver && mouse.isDown(MBUT_LEFT);
}

////////////////////////////////////////////////////////////////////////////////
// Operator
////////////////////////////////////////////////////////////////////////////////

RoundButton	&RoundButton::operator=(const RoundButton &btn)
{
	this->pos = btn.pos;
	this->size = btn.size;

	this->text = btn.text;
	this->fontSize = btn.fontSize;
	this->textColor = btn.textColor;
	this->backColor = btn.backColor;
	this->frontColorOn = btn.frontColorOn;
	this->frontColorOff = btn.frontColorOff;

	this->mouseOver = btn.mouseOver;
	this->pressed = btn.pressed;
	this->down = btn.down;

	this->corner_radius = btn.corner_radius;

	this->visual = btn.visual;

	return (*this);
}
