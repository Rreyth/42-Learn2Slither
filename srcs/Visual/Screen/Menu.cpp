#include "Menu.hpp"

#include <utils/functions.hpp>
#include <Environment/Environment.hpp>


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
	int x, y, w, h;

	x = win_size.x * 1/4;
	y = win_size.y * 0.4;
	w = 200;
	h = 50;
	this->play_button = Button("Play", 30, sf::Color::White, x, y, w, h,
					SPRITE_WIDE_BUTTON_ON, SPRITE_WIDE_BUTTON_OFF, texture_manager);

	y = win_size.y * 0.6;
	this->AI_button = Button("AI play", 30, sf::Color::White, x, y, w, h,
					SPRITE_WIDE_BUTTON_ON, SPRITE_WIDE_BUTTON_OFF, texture_manager);

	x = win_size.x * 0.075;
	y = win_size.y * 0.93;
	w = 100;
	h = 40;
	this->quit_button = Button("Quit", 25, sf::Color::White, x, y, w, h,
						SPRITE_BUTTON_ON, SPRITE_BUTTON_OFF, texture_manager);

	x = win_size.x * 3/4;
	y = win_size.y * 0.3;
	w = 200;
	h = 6;
	this->size_slider = Slider(10, 25, this->settings.size, "int", {x, y}, {w, h},
						SPRITE_CIRCLE_ON, SPRITE_CIRCLE_OFF, texture_manager);

	y = win_size.y * 0.9;
	this->move_time_slider = Slider(0.1, 2, this->settings.move_time, "float", {x, y}, {w, h},
						SPRITE_CIRCLE_ON, SPRITE_CIRCLE_OFF, texture_manager);

	y = win_size.y * 0.5;
	w = 250;
	this->sessions_slider = Slider(1, 1000, this->settings.sessions, "int", {x, y}, {w, h},
						SPRITE_CIRCLE_ON, SPRITE_CIRCLE_OFF, texture_manager);
}



void Menu::render(sf::RenderWindow &window, sf::Text &text, TextureManager &texture_manager)
{
	sf::Vector2f win_size(window.getSize());
	//background
	//title
	sf::Vector2f pos(win_size.x / 2, win_size.y * 0.1);
	drawText(window, text, "Learn2Slither", pos, 50, sf::Text::Bold, sf::Color::White);

	//buttons
	this->play_button.draw(window, text, texture_manager);
	this->AI_button.draw(window, text, texture_manager);
	this->quit_button.draw(window, text, texture_manager);

	//settings
	pos.x = win_size.x * 3/4;
	pos.y = win_size.y * 0.2;
	drawText(window, text, "Grid size", pos, 30, sf::Text::Regular, sf::Color::White);
	this->size_slider.draw(window, text, texture_manager);

	pos.y = win_size.y * 0.4;
	drawText(window, text, "Number of sessions", pos, 30, sf::Text::Regular, sf::Color::White);
	this->sessions_slider.draw(window, text, texture_manager);

	pos.y = win_size.y * 0.8;
	drawText(window, text, "Min time per AI move", pos, 30, sf::Text::Regular, sf::Color::White);
	this->move_time_slider.draw(window, text, texture_manager);
	pos.y = win_size.y * 0.95;
	drawText(window, text, "Seconds", pos, 30, sf::Text::Regular, sf::Color::White);
}


void	Menu::tick(Environment &env, Mouse &mouse, sf::RenderWindow &window)
{
	this->play_button.tick(mouse);
	this->AI_button.tick(mouse);
	this->quit_button.tick(mouse);
	this->size_slider.tick(mouse, window);
	this->sessions_slider.tick(mouse, window);
	this->move_time_slider.tick(mouse, window);

	if (this->quit_button.getPressed())
		env.close();
	else if (this->play_button.getPressed())
	{
		std::cout << "play" << std::endl;
	}
	else if (this->AI_button.getPressed())
	{
		std::cout << "AI" << std::endl;
	}
}
