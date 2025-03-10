#ifndef MENU_HPP
# define MENU_HPP

#include <Visual/Screen/Button.hpp>
#include <utils/parser.hpp>

class Environment;


struct s_settings
{
	int		size = 10;
	int		sessions = 0;
	bool	learn = true;
	bool	step_mode = false;
	float	move_time = 0;
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
		void		tick(Environment &env, Mouse &mouse);

	private:
		s_settings	settings;
		Button		play_button, AI_button, quit_button;
		//size selector (slider ?)
		//session selector
		//learn toggle (default true)
		//stepmode toggle
		//time per move if no step (slider / selector)
};


#endif //MENU_HPP
