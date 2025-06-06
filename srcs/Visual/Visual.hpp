#ifndef VISUAL_HPP
#define VISUAL_HPP


#include <Environment/Grid.hpp>
#include <SFML/Graphics.hpp>
#include <Visual/Screen/GameOverScreen.hpp>
#include <Visual/Screen/AIGameOverScreen.hpp>
#include <Visual/Screen/GameScreen.hpp>
#include <Visual/Screen/AIGameScreen.hpp>
#include <Visual/Screen/Menu.hpp>
#include <utils/TextureManager.hpp>
#include <utils/enums.hpp>
#include <utils/functions.hpp>
#include <utils/structs.hpp>


#define MAX_FPS 1000


class Visual
{
	public:
		Visual(flags &launch_flags);
		~Visual();

		sf::RenderWindow	&getWin();
		gameState			&getState();
		void				setState(gameState state);
		void				render(s_player &player, std::vector<s_apple> &apples,
									gameInfos &infos, float &move_time, visualModAiStep &ai_step);
		void				tick(Environment &env, Mouse &mouse);
		void				gameOverInit(gameInfos &infos);
		void				aiGameOverInit();

	private:
		sf::RenderWindow	window;
		sf::Font			font;
		sf::Text			text;
		TextureManager		texture_manager;
		Menu				menu;
		GameScreen			game_screen;
		AIGameScreen		ai_game_screen;
		GameOverScreen		game_over_screen;
		AIGameOverScreen	ai_game_over_screen;
		gameState			state;

		void				resetWindow();

};

#endif //VISUAL_HPP
