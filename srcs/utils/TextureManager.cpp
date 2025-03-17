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

sf::Vector2u	TextureManager::getTextureSize(sprite_name name) const
{
	return this->textures[name].getSize();
}


void	TextureManager::loadTextures(void)
{
	// Load sprites
	this->loadTexture(SPRITE_BUTTON_OFF, "round_button_off.png");
	this->loadTexture(SPRITE_BUTTON_ON, "round_button_on.png");
	this->loadTexture(SPRITE_WIDE_BUTTON_OFF, "wide_button(off).png");
	this->loadTexture(SPRITE_WIDE_BUTTON_ON, "wide_button(on).png");
	this->loadTexture(SPRITE_CIRCLE_OFF, "circleOff.png");
	this->loadTexture(SPRITE_CIRCLE_ON, "circleOn.png");
	this->loadTexture(SPRITE_EMPTY_CHECK, "empty_check.png");
	this->loadTexture(SPRITE_VALID_CHECK, "valid_check.png");
	this->loadTexture(SPRITE_GROUND, "ground.png");
	this->loadTexture(SPRITE_WALL, "wall.png");
	this->loadTexture(SPRITE_GREEN_APPLE, "green_apple.png");
	this->loadTexture(SPRITE_RED_APPLE, "red_apple.png");
	this->loadTexture(SPRITE_SNAKE_HEAD, "snake_head.png");
	this->loadTexture(SPRITE_SNAKE_BODY, "snake_body.png");
	this->loadTexture(SPRITE_SNAKE_BODY_ANGLE, "snake_body_angle.png");
	this->loadTexture(SPRITE_SNAKE_TAIL, "snake_tail.png");
}


void TextureManager::scaleSprite(sprite_name name, sf::Vector2f scale)
{
	this->sprites[name].setScale(scale);
}


void	TextureManager::drawTexture(sf::RenderWindow &window, sprite_name name, sf::Vector2f pos)
{
	this->sprites[name].setPosition(pos);

	window.draw(this->sprites[name]);
}


void	TextureManager::rotateDraw(sf::RenderWindow &window, sprite_name name,
								sf::Vector2f pos, sf::Angle angle)
{
	this->sprites[name].rotate(angle);

	this->sprites[name].setPosition(pos);

	window.draw(this->sprites[name]);
	this->sprites[name].rotate(-angle);
}

////////////////////////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////////////////////////

void	TextureManager::loadTexture(sprite_name name, const std::string &filename)
{
	if (!this->textures[name].loadFromFile("data/sprites/" + filename))
		throw std::invalid_argument("");
	this->sprites.push_back(sf::Sprite(this->textures[name]));
	sf::Vector2u size = this->textures[name].getSize();
	this->sprites.back().setOrigin({size.x / 2.f, size.y / 2.f});
}
