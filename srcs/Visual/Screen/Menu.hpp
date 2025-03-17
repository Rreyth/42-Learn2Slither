#ifndef MENU_HPP
# define MENU_HPP

#include <Visual/Screen/UI/Button.hpp>
#include <Visual/Screen/UI/Slider.hpp>
#include <Visual/Screen/UI/ToggleButton.hpp>
#include <utils/parser.hpp>

class Environment;


struct s_settings
{
	int		size = 10;
	int		sessions = 10;
	bool	learn = true;
	bool	step_mode = false;
	bool	start = false;
	bool	AI_play = false;
	float	move_time = 0.5;
};


class Menu
{
	public:
		Menu(const flags &launch_flags);
		~Menu();

		s_settings	&getSettings();

		void		visualInit(sf::Vector2u win_size, TextureManager &texture_manager);
		void		render(sf::RenderWindow &window, sf::Text &text,
							TextureManager &texture_manager);
		void		tick(Environment &env, Mouse &mouse, sf::RenderWindow &window);

	private:
		s_settings		settings;
		Button			play_button, AI_button, quit_button;
		Slider			size_slider, sessions_slider, move_time_slider;
		ToggleButton	learn_toggle, step_toggle;

		void			saveSettings();
		void			drawBackground(sf::RenderWindow &window,
								TextureManager &texture_manager);
};


#endif //MENU_HPP
