#include <iostream>
#include <utils/TextureManager.hpp>

#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
// Constructors and destructor
////////////////////////////////////////////////////////////////////////////////

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{

}

////////////////////////////////////////////////////////////////////////////////
// Public methods
////////////////////////////////////////////////////////////////////////////////
void	TextureManager::loadTextures(void)
{
	// Load sprites
	this->loadTexture(SPRITE_BUTTON_OFF, "round_button_off.png");
	this->loadTexture(SPRITE_BUTTON_ON, "round_button_on.png");
	this->loadTexture(SPRITE_CIRCLE_OFF, "circleOff.png");
	this->loadTexture(SPRITE_CIRCLE_ON, "circleOn.png");

	// Scale sprites
	// this->scaleSprite(SPRITE_BUTTON_OFF, 2.0f, 2.0f);
	// this->scaleSprite(SPRITE_BUTTON_ON, 2.0f, 2.0f);
}


void TextureManager::scaleSprite(sprite_name name, sf::Vector2f scale)
{
	this->sprites[name].setScale(scale);
}


void	TextureManager::drawTexture(sf::RenderWindow &window, sprite_name name, int x, int y)
{
	int w, h;

	sf::Vector2u txt_size = this->textures[name].getSize();
	sf::Vector2f scale = this->sprites[name].getScale();

	w = txt_size.x * scale.x;
	h = txt_size.y * scale.y;

	sf::Vector2f pos(x - w / 2, y - h / 2);
	this->sprites[name].setPosition(pos);

	window.draw(this->sprites[name]);
}

////////////////////////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////////////////////////

void	TextureManager::loadTexture(sprite_name name, const std::string &filename)
{
	if (!this->textures[name].loadFromFile("data/sprites/" + filename))
		throw std::invalid_argument("");
	this->sprites.push_back(sf::Sprite(this->textures[name]));
}
