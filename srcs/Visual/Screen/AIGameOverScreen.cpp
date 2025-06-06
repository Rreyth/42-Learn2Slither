#include <Visual/Screen/AIGameOverScreen.hpp>
#include <utils/functions.hpp>


AIGameOverScreen::AIGameOverScreen()
{
	this->back = false;
	this->quit = false;
}


AIGameOverScreen::~AIGameOverScreen()
{
}


void	AIGameOverScreen::init(sf::RenderWindow &window)
{
	this->back = false;
	this->quit = false;

	sf::Vector2u win_size = window.getSize();
	int	x, y, w, h;

	x = win_size.x / 3;
	y = win_size.y * 0.9;
	w = 140;
	h = 40;

	this->quit_button = RoundButton("Quit", 25, sf::Color::White,
						{x, y}, {w, h}, 10, sf::Color(200, 200, 200),
						sf::Color(100, 100, 100), sf::Color::White);

	x = win_size.x / 3 * 2;

	this->menu_button = RoundButton("Back to menu", 25, sf::Color::White,
						{x, y}, {w, h}, 10, sf::Color(200, 200, 200),
						sf::Color(100, 100, 100), sf::Color::White);
}


void	AIGameOverScreen::tick(Mouse &mouse)
{
	this->menu_button.tick(mouse);
	this->quit_button.tick(mouse);

	if (this->menu_button.getPressed())
		this->back = true;
	if (this->quit_button.getPressed())
		this->quit = true;
}


void	AIGameOverScreen::render(sf::RenderWindow &window, sf::Text &text,
				TextureManager &texture_manager, visualModAiStep &ai_step)
{
	// background
	drawBackground(window, texture_manager);
	sf::RectangleShape darkLayer(sf::Vector2f(window.getSize()));
	darkLayer.setFillColor(sf::Color(0, 0, 0, 200));
	window.draw(darkLayer);

	// title
	sf::Vector2u win_size = window.getSize();
	sf::Vector2f pos(win_size.x / 2, win_size.y * 0.1);
	drawText(window, text, "GAME OVER", pos, 50, sf::Text::Bold, sf::Color::White);

	// infos
	this->displayInfos(window, text, ai_step);

	// buttons
	this->quit_button.draw(window, text);
	this->menu_button.draw(window, text);
}


bool	AIGameOverScreen::getQuit()
{
	return this->quit;
}


bool	AIGameOverScreen::backToMenu()
{
	return this->back;
}


void	AIGameOverScreen::displayInfos(sf::RenderWindow &window, sf::Text &text,
				visualModAiStep &ai_step)
{
	std::string		all_str[] = {"Played " + std::to_string(ai_step.total_sessions) + " sessions",
							"Max green apples", std::to_string(ai_step.max_bonus),
							"Max red apples", std::to_string(ai_step.max_malus),
							"Max lifetime (steps)", std::to_string(ai_step.max_step),
							"Max size", std::to_string(ai_step.max_len)};

	sf::Vector2u	win_size = window.getSize();
	sf::Vector2f	pos;
	int				font_size = win_size.y * 0.07;

	// sessions
	pos.x = win_size.x / 2;
	pos.y = win_size.y * 0.225;
	drawText(window, text, all_str[0], pos, font_size, sf::Text::Bold, sf::Color::White);

	// green apples
	pos.x = win_size.x / 3;
	pos.y = win_size.y * 0.34;
	drawText(window, text, all_str[1], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.44;
	drawText(window, text, all_str[2], pos, font_size, sf::Text::Bold, sf::Color::White);

	// red apples
	pos.x = win_size.x / 3 * 2;
	pos.y = win_size.y * 0.34;
	drawText(window, text, all_str[3], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.44;
	drawText(window, text, all_str[4], pos, font_size, sf::Text::Bold, sf::Color::White);

	// steps
	pos.x = win_size.x / 3;
	pos.y = win_size.y * 0.60;
	drawText(window, text, all_str[5], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.70;
	drawText(window, text, all_str[6], pos, font_size, sf::Text::Bold, sf::Color::White);

	// size
	pos.x = win_size.x / 3 * 2;
	pos.y = win_size.y * 0.60;
	drawText(window, text, all_str[7], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.70;
	drawText(window, text, all_str[8], pos, font_size, sf::Text::Bold, sf::Color::White);
}
