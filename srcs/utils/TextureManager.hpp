#ifndef TEXTUREMANAGER_HPP
# define TEXTUREMANAGER_HPP

# include <SFML/Graphics.hpp>
# include <string>

# define NB_SPRITES 4

typedef enum e_sprite_name
{
	SPRITE_BUTTON_OFF,
	SPRITE_BUTTON_ON,
	SPRITE_CIRCLE_OFF,
	SPRITE_CIRCLE_ON,
}	sprite_name;

class TextureManager
{
	public:
		TextureManager(void);
		~TextureManager();

		void	loadTextures(void);
		void	scaleSprite(sprite_name name, sf::Vector2f scale);
		void	drawTexture(sf::RenderWindow &window, sprite_name name, int x, int y);

	private:
		std::vector<sf::Sprite> sprites;
		sf::Texture				textures[NB_SPRITES];

		void loadTexture(sprite_name name, const std::string &filename);
};

#endif
