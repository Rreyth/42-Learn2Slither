#include <Visual/Screen/GameOverScreen.hpp>
#include <utils/functions.hpp>


GameOverScreen::GameOverScreen()
{
	this->back = false;
	this->quit = false;
}


GameOverScreen::~GameOverScreen()
{
}


void	GameOverScreen::init(gameInfos &infos, sf::RenderWindow &window,
							TextureManager &texture_manager)
{
	this->back = false;
	this->quit = false;
	this->infos = infos;

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


void	GameOverScreen::tick(Mouse &mouse)
{
	this->menu_button.tick(mouse);
	this->quit_button.tick(mouse);

	if (this->menu_button.getPressed())
		this->back = true;
	if (this->quit_button.getPressed())
		this->quit = true;
}


void	GameOverScreen::render(sf::RenderWindow &window, sf::Text &text, TextureManager &texture_manager)
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
	this->displayInfos(window, text);

	// buttons
	this->quit_button.draw(window, text);
	this->menu_button.draw(window, text);
}


bool	GameOverScreen::getQuit()
{
	return this->quit;
}


bool	GameOverScreen::backToMenu()
{
	return this->back;
}


void	GameOverScreen::displayInfos(sf::RenderWindow &window, sf::Text &text)
{
	std::string		all_str[] = {"Nb moves", std::to_string(this->infos.nb_moves),
							"Time played", "TODO",
							"End size", std::to_string(this->infos.current_size),
							"Max size", std::to_string(this->infos.max_size)};

	sf::Vector2u	win_size = window.getSize();
	sf::Vector2f	pos;
	int				font_size = win_size.y * 0.07;

	pos.x = win_size.x / 3;
	pos.y = win_size.y * 0.33;
	drawText(window, text, all_str[0], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.43;
	drawText(window, text, all_str[1], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.60;
	drawText(window, text, all_str[2], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.70;
	drawText(window, text, all_str[3], pos, font_size, sf::Text::Bold, sf::Color::White);

	pos.x = win_size.x / 3 * 2;
	pos.y = win_size.y * 0.33;
	drawText(window, text, all_str[4], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.43;
	drawText(window, text, all_str[5], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.60;
	drawText(window, text, all_str[6], pos, font_size, sf::Text::Bold, sf::Color::White);
	pos.y = win_size.y * 0.70;
	drawText(window, text, all_str[7], pos, font_size, sf::Text::Bold, sf::Color::White);
}
