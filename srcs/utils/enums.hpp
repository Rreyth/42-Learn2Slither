#ifndef ENUMS_HPP
# define ENUMS_HPP


enum gameState
{
	MENU,
	GAME,
	AI_GAME,
	GAMEOVER,
	AI_GAMEOVER,
};


enum player_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


typedef enum e_mouse_button
{
	MBUT_LEFT,
	MBUT_MIDDLE,
	MBUT_RIGHT
}	mouse_button;


#endif //ENUMS_HPP
