#include <Visual/Screen/Menu.hpp>
#include <utils/functions.hpp>
#include <Environment/Environment.hpp>


Menu::Menu(const flags &launch_flags)
{
	this->settings = {launch_flags.size,
					launch_flags.sessions,
					!launch_flags.dontlearn,
					launch_flags.stepmode,
					false,
					false,
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

	x = win_size.x * 0.1;
	y = win_size.y * 0.885;
	w = 100;
	h = 40;
	this->quit_button = Button("Quit", 25, sf::Color::White, x, y, w, h,
						SPRITE_BUTTON_ON, SPRITE_BUTTON_OFF, texture_manager);

	x = win_size.x * 3/4;
	y = win_size.y * 0.25;
	w = 200;
	h = 6;
	this->size_slider = Slider(10, 25, this->settings.size, "int", {x, y}, {w, h},
						SPRITE_CIRCLE_ON, SPRITE_CIRCLE_OFF, texture_manager);

	y = win_size.y * 0.85;
	this->move_time_slider = Slider(0.1, 2, this->settings.move_time, "float", {x, y}, {w, h},
						SPRITE_CIRCLE_ON, SPRITE_CIRCLE_OFF, texture_manager);

	y = win_size.y * 0.45;
	w = 250;
	this->sessions_slider = Slider(1, 1000, this->settings.sessions, "int", {x, y}, {w, h},
						SPRITE_CIRCLE_ON, SPRITE_CIRCLE_OFF, texture_manager);

	x = win_size.x * 0.65;
	y = win_size.y * 0.62;
	w = 40;
	h = 40;
	this->learn_toggle = ToggleButton(x, y, w, h, SPRITE_VALID_CHECK, SPRITE_EMPTY_CHECK, texture_manager);
	this->learn_toggle.setToggled(this->settings.learn);


	x = win_size.x * 0.85;
	w = 40;
	h = 40;
	this->step_toggle = ToggleButton(x, y, w, h, SPRITE_VALID_CHECK, SPRITE_EMPTY_CHECK, texture_manager);
	this->step_toggle.setToggled(this->settings.step_mode);
}



void Menu::render(sf::RenderWindow &window, sf::Text &text, TextureManager &texture_manager)
{
	sf::Vector2f win_size(window.getSize());

	//background
	this->drawBackground(window, texture_manager);

	//title
	sf::Vector2f pos(win_size.x / 2, win_size.y * 0.1);
	drawText(window, text, "Learn2Slither", pos, 50, sf::Text::Bold, sf::Color::White);

	//buttons
	this->play_button.draw(window, text, texture_manager);
	this->AI_button.draw(window, text, texture_manager);
	this->quit_button.draw(window, text, texture_manager);

	//settings
	pos.x = win_size.x * 3/4;
	pos.y = win_size.y * 0.15;
	drawText(window, text, "Grid size", pos, 30, sf::Text::Regular, sf::Color::White);
	this->size_slider.draw(window, text, texture_manager);

	pos.y = win_size.y * 0.35;
	drawText(window, text, "Number of sessions", pos, 30, sf::Text::Regular, sf::Color::White);
	this->sessions_slider.draw(window, text, texture_manager);

	pos.x = win_size.x * 0.65;
	pos.y = win_size.y * 0.52;
	drawText(window, text, "AI learn", pos, 30, sf::Text::Regular, sf::Color::White);
	this->learn_toggle.draw(window, texture_manager);

	pos.x = win_size.x * 0.85;
	drawText(window, text, "Step-by-step", pos, 30, sf::Text::Regular, sf::Color::White);
	this->step_toggle.draw(window, texture_manager);

	pos.x = win_size.x * 3/4;
	pos.y = win_size.y * 0.75;
	drawText(window, text, "Min time per AI move", pos, 30, sf::Text::Regular, sf::Color::White);
	this->move_time_slider.draw(window, text, texture_manager);
	pos.y = win_size.y * 0.90;
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
	this->learn_toggle.tick(mouse);
	this->step_toggle.tick(mouse);

	this->saveSettings();
	if (this->quit_button.getPressed())
		env.close();
	else if (this->play_button.getPressed())
	{
		this->settings.start = true;
	}
	else if (this->AI_button.getPressed())
	{
		this->settings.start = true;
		this->settings.AI_play = true;
	}
}


void	Menu::saveSettings()
{
	this->settings.size = this->size_slider.getValue();
	this->settings.sessions = this->sessions_slider.getValue();
	this->settings.learn = this->learn_toggle.isToggled();
	this->settings.step_mode = this->step_toggle.isToggled();
	this->settings.move_time = this->move_time_slider.getValue();
}


void	Menu::drawBackground(sf::RenderWindow &window, TextureManager &texture_manager)
{
	sf::Vector2f win_size(window.getSize());
	for (int y = 16; y < win_size.y; y+=32)
	{
		for (int x = 16; x < win_size.x; x+=32)
		{
			if (x == 16 || x == win_size.x - 16
				|| y == 16 || y == win_size.y - 16)
				texture_manager.drawTexture(window, SPRITE_WALL, sf::Vector2f(x, y));
			else
			{
				texture_manager.drawTexture(window, SPRITE_GROUND, sf::Vector2f(x, y));
			}
			if (y == 48 && (x == 48 || x == win_size.x - 48))
				texture_manager.drawTexture(window, SPRITE_GREEN_APPLE, sf::Vector2f(x, y));
			else if (y == win_size.y - 48 && (x == 48 || x == win_size.x - 48))
				texture_manager.drawTexture(window, SPRITE_RED_APPLE, sf::Vector2f(x, y));
		}
		if (y >= win_size.y * 0.2 && y <= win_size.y * 0.85)
		{
			if (y <= win_size.y * 0.25)
				texture_manager.drawTexture(window, SPRITE_SNAKE_HEAD, sf::Vector2f(win_size.x / 2, y));
			else if (y >= win_size.y * 0.8)
				texture_manager.drawTexture(window, SPRITE_SNAKE_TAIL, sf::Vector2f(win_size.x / 2, y));
			else
				texture_manager.drawTexture(window, SPRITE_SNAKE_BODY, sf::Vector2f(win_size.x / 2, y));
		}
	}
}
