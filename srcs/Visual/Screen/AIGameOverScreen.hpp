#ifndef AIGAMEOVERSCREEN_HPP
#define AIGAMEOVERSCREEN_HPP

#include <Visual/Screen/UI/RoundButton.hpp>
#include <utils/structs.hpp>

class AIGameOverScreen
{
	public:
		AIGameOverScreen();
		~AIGameOverScreen();

		void	init(sf::RenderWindow &window);
		void	tick(Mouse &mouse);
		void	render(sf::RenderWindow &window, sf::Text &text,
					TextureManager &texture_manager, visualModAiStep &ai_step);

		bool	getQuit();
		bool	backToMenu();

	private:
		RoundButton	menu_button, quit_button;
		bool		back, quit;

		void		displayInfos(sf::RenderWindow &window, sf::Text &text,
						visualModAiStep &ai_step);
};


#endif //AIGAMEOVERSCREEN_HPP
