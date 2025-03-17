#ifndef TEXTUREMANAGER_HPP
# define TEXTUREMANAGER_HPP

# include <SFML/Graphics.hpp>
# include <string>

# define NB_SPRITES 16

typedef enum e_sprite_name
{
	SPRITE_BUTTON_OFF,
	SPRITE_BUTTON_ON,
	SPRITE_WIDE_BUTTON_OFF,
	SPRITE_WIDE_BUTTON_ON,
	SPRITE_CIRCLE_OFF,
	SPRITE_CIRCLE_ON,
	SPRITE_EMPTY_CHECK,
	SPRITE_VALID_CHECK,
	SPRITE_GROUND,
	SPRITE_WALL,
	SPRITE_GREEN_APPLE,
	SPRITE_RED_APPLE,
	SPRITE_SNAKE_HEAD,
	SPRITE_SNAKE_BODY,
	SPRITE_SNAKE_BODY_ANGLE,
	SPRITE_SNAKE_TAIL,
}	sprite_name;

class TextureManager
{
	public:
		TextureManager(void);
		~TextureManager();

		sf::Vector2u	getTextureSize(sprite_name name) const;

		void			loadTextures(void);
		void			scaleSprite(sprite_name name, sf::Vector2f scale);
		void			drawTexture(sf::RenderWindow &window, sprite_name name, sf::Vector2f pos);
		void			rotateDraw(sf::RenderWindow &window, sprite_name name, sf::Vector2f pos, sf::Angle angle);

	private:
		std::vector<sf::Sprite> sprites;
		sf::Texture				textures[NB_SPRITES];

		void loadTexture(sprite_name name, const std::string &filename);
};

#endif
