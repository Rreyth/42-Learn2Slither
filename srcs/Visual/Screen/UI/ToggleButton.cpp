#include <Visual/Screen/UI/ToggleButton.hpp>
#include <utils/functions.hpp>


ToggleButton::ToggleButton()
{
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->scaleOn = {1.0, 1.0};
	this->scaleOff = {1.0, 1.0};

	this->toggled = false;

	this->onSprite = SPRITE_VALID_CHECK;
	this->offSprite = SPRITE_EMPTY_CHECK;
}

ToggleButton::ToggleButton(int x, int y, float w, float h,
			sprite_name onSprite, sprite_name offSprite,
			TextureManager &texture_manager)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	this->toggled = false;

	this->onSprite = onSprite;
	this->offSprite = offSprite;

	sf::Vector2u texture_size(texture_manager.getTextureSize(onSprite));

	this->scaleOn = {w / static_cast<float>(texture_size.x),
					h / static_cast<float>(texture_size.y)};

	texture_size = texture_manager.getTextureSize(offSprite);
	this->scaleOff = {w / static_cast<float>(texture_size.x),
					h / static_cast<float>(texture_size.y)};
}


ToggleButton::~ToggleButton()
{
}


void	ToggleButton::setToggled(bool toggled)
{
	this->toggled = toggled;
}


bool	ToggleButton::isToggled()
{
	return this->toggled;
}


void ToggleButton::draw(sf::RenderWindow &window, TextureManager &textureManager)
{
	if (!this->toggled)
	{
		textureManager.scaleSprite(this->offSprite, this->scaleOff);
		textureManager.drawTexture(window, this->offSprite, sf::Vector2f(this->x, this->y));
	}
	else
	{
		textureManager.scaleSprite(this->onSprite, this->scaleOn);
		textureManager.drawTexture(window, this->onSprite, sf::Vector2f(this->x, this->y));
	}
}


void ToggleButton::tick(Mouse &mouse)
{
	bool mouseOver = mouse.inRectangle(this->x - this->w / 2, this->y - this->h / 2,
										this->w, this->h);
	if (mouseOver && mouse.isPressed(MBUT_LEFT))
		this->toggled = !this->toggled;
}

////////////////////////////////////////////////////////////////////////////////
// Operator
////////////////////////////////////////////////////////////////////////////////

ToggleButton	&ToggleButton::operator=(const ToggleButton &btn)
{
	this->x = btn.x;
	this->y = btn.y;
	this->w = btn.w;
	this->h = btn.h;

	this->toggled = btn.toggled;

	this->onSprite = btn.onSprite;
	this->offSprite = btn.offSprite;

	this->scaleOff = btn.scaleOff;
	this->scaleOn = btn.scaleOn;

	return (*this);
}
