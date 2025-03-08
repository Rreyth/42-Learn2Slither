#include "Menu.hpp"

#include <utils/functions.hpp>


Menu::Menu(const flags &launch_flags)
{
	this->settings = {launch_flags.size,
					launch_flags.sessions,
					!launch_flags.dontlearn,
					launch_flags.stepmode,
					0.5};
}


 Menu::~Menu()
{
}


s_settings &Menu::getSettings()
{
	return this->settings;
}


void		Menu::visualInit(sf::Vector2u win_size, TextureManager &texture_manager)
{
	int x, y;
	float w, h;

	x = win_size.x * 1/4;
	y = win_size.y * 0.4;
	w = 200;
	h = 50;
	this->play_button = Button("Play", 30, sf::Color::White, x, y, w, h,
					SPRITE_WIDE_BUTTON_ON, SPRITE_WIDE_BUTTON_OFF, texture_manager);

	x = win_size.x * 1/4;
	y = win_size.y * 0.6;
	w = 200;
	h = 50;
	this->AI_button = Button("AI play", 30, sf::Color::White, x, y, w, h,
					SPRITE_WIDE_BUTTON_ON, SPRITE_WIDE_BUTTON_OFF, texture_manager);

	x = win_size.x * 0.075;
	y = win_size.y * 0.93;
	w = 100;
	h = 40;
	this->quit_button = Button("Quit", 25, sf::Color::White, x, y, w, h,
						SPRITE_BUTTON_ON, SPRITE_BUTTON_OFF, texture_manager);
}



void Menu::render(sf::RenderWindow &window, sf::Text &text, TextureManager &texture_manager)
{
	sf::Vector2u win_size = window.getSize();
	//background
	//title
	sf::Vector2f pos(win_size.x / 2, win_size.y * 0.1);
	drawText(window, text, "Learn2Slither", pos, 50, sf::Text::Bold, sf::Color::White);
	//buttons
	this->play_button.draw(window, text, texture_manager);
	this->AI_button.draw(window, text, texture_manager);
	this->quit_button.draw(window, text, texture_manager);
	//settings
}
