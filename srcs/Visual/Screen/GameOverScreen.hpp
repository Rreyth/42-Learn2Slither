#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include <Visual/Screen/UI/RoundButton.hpp>
#include <utils/structs.hpp>


class GameOverScreen
{
	public:
		GameOverScreen();
		~GameOverScreen();

		void	init(gameInfos &infos, sf::RenderWindow &window,
					TextureManager &texture_manager);
		void	tick(Mouse &mouse);
		void	render(sf::RenderWindow &window, sf::Text &text,
					TextureManager &texture_manager);

		bool	getQuit();
		bool	backToMenu();

	private:
		gameInfos	infos;
		RoundButton	menu_button, quit_button;
		bool		back, quit;

		void		displayInfos(sf::RenderWindow &window, sf::Text &text);
};


#endif //GAMEOVERSCREEN_HPP
