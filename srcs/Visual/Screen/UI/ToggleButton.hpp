#ifndef TOGGLEBUTTON_HPP
# define TOGGLEBUTTON_HPP

# include <utils/TextureManager.hpp>
# include <utils/Mouse.hpp>


class ToggleButton
{
public:
	ToggleButton(void);
	ToggleButton(int x, int y, float w, float h,
			sprite_name onSprite, sprite_name offSprite,
			TextureManager &texture_manager);
	~ToggleButton();

	void			setToggled(bool toggled);
	bool			isToggled();

	void			tick(Mouse &mouse);
	void			draw(sf::RenderWindow &window, TextureManager &textureManager);

	ToggleButton	&operator=(const ToggleButton &btn);

private:
	sf::Vector2f	scaleOn, scaleOff;
	sprite_name		onSprite, offSprite;
	int				x, y, w, h;
	bool			toggled;
};


#endif //TOGGLEBUTTON_HPP
