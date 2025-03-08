#include <Visual/Screen/Button.hpp>
#include <utils/functions.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constructors and destructor
////////////////////////////////////////////////////////////////////////////////

Button::Button()
{
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->scaleOn = {1.0, 1.0};
	this->scaleOff = {1.0, 1.0};

	this->text = "";
	this->fontSize = 0;
	this->textColor = sf::Color::Black;

	this->mouseOver = false;
	this->pressed = false;

	this->onSprite = SPRITE_BUTTON_ON;
	this->offSprite = SPRITE_BUTTON_OFF;
}

Button::Button(std::string text, int fontSize, sf::Color textColor,
				int x, int y, float w, float h,
				sprite_name onSprite, sprite_name offSprite,
				TextureManager &texture_manager)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	this->text = text;
	this->fontSize = fontSize;
	this->textColor = textColor;

	this->mouseOver = false;
	this->pressed = false;

	this->onSprite = onSprite;
	this->offSprite = offSprite;

	sf::Vector2u texture_size(texture_manager.getTextureSize(onSprite));

	this->scaleOn = {w / static_cast<float>(texture_size.x),
					h / static_cast<float>(texture_size.y)};

	texture_size = texture_manager.getTextureSize(offSprite);
	this->scaleOff = {w / static_cast<float>(texture_size.x),
					h / static_cast<float>(texture_size.y)};
}


Button::~Button()
{

}

////////////////////////////////////////////////////////////////////////////////
// Getters and setters
////////////////////////////////////////////////////////////////////////////////

bool Button::getPressed()
{
	return (this->pressed);
}


void	Button::setText(std::string text)
{
	this->text = text;
}

////////////////////////////////////////////////////////////////////////////////
// Public methods
////////////////////////////////////////////////////////////////////////////////

void Button::draw(sf::RenderWindow &window, sf::Text &text, TextureManager &textureManager)
{
	if (!this->mouseOver)
	{
		textureManager.scaleSprite(this->offSprite, this->scaleOff);
		textureManager.drawTexture(window, this->offSprite, this->x, this->y);
	}
	else
	{
		textureManager.scaleSprite(this->onSprite, this->scaleOn);
		textureManager.drawTexture(window, this->onSprite, this->x, this->y);
	}

	drawText(window, text, this->text, this->x, this->y,
		this->fontSize, sf::Text::Regular, this->textColor);
}


void Button::tick(Mouse &mouse)
{
	this->mouseOver = mouse.inRectangle(this->x, this->y, this->w, this->h);
	this->pressed = this->mouseOver && mouse.isPressed(MBUT_LEFT);
}

////////////////////////////////////////////////////////////////////////////////
// Operator
////////////////////////////////////////////////////////////////////////////////

Button	&Button::operator=(const Button &btn)
{
	this->x = btn.x;
	this->y = btn.y;
	this->w = btn.w;
	this->h = btn.h;

	this->text = btn.text;
	this->fontSize = btn.fontSize;
	this->textColor = btn.textColor;

	this->mouseOver = btn.mouseOver;
	this->pressed = btn.pressed;

	this->onSprite = btn.onSprite;
	this->offSprite = btn.offSprite;

	this->scaleOff = btn.scaleOff;
	this->scaleOn = btn.scaleOn;

	return (*this);
}
