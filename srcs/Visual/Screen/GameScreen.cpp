#include <Visual/Screen/GameScreen.hpp>
#include <utils/functions.hpp>

GameScreen::GameScreen()
{
	this->tiles_nb = 12;
	this->back = false;
}


GameScreen::~GameScreen()
{
}


bool	GameScreen::BackToMenu() const
{
	return this->back;
}


void	GameScreen::visualInit(sf::RenderWindow &window, TextureManager &texture_manager,
								int tiles_nb)
{
	this->back = false;
	this->tiles_nb = tiles_nb;
	sf::Vector2u win_size((tiles_nb + 1) * TILE_SIZE * 2, (tiles_nb + 2) * TILE_SIZE);
	this->grid_pos = sf::Vector2i(win_size.x * 0.5 - this->tiles_nb * TILE_SIZE,
								win_size.y * 0.5 - this->tiles_nb * 0.5 * TILE_SIZE);

	window.create(sf::VideoMode({win_size.x, win_size.y}), "I'M A SNAKE!", sf::Style::Close);
	window.setFramerateLimit(MAX_FPS);
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i windowPosition((desktop.size.x - win_size.x) / 2, (desktop.size.y - win_size.y) / 2);
	window.setPosition(windowPosition);
	window.setKeyRepeatEnabled(false);

	int x, y, w, h;
	if (tiles_nb - 2 <= 13)
	{
		x = win_size.x * 0.9;
		y = win_size.y * 0.9;
	}
	else if (tiles_nb - 2 <= 17)
	{
		x = win_size.x * 0.93;
		y = win_size.y * 0.93;
	}
	else
	{
		x = win_size.x * 0.95;
		y = win_size.y * 0.95;
	}
	w = 120;
	h = 40;
	this->back_button = Button("Back to menu", 20, sf::Color::White, x, y, w, h,
						SPRITE_BUTTON_ON, SPRITE_BUTTON_OFF, texture_manager);
}


void	GameScreen::tick(Mouse &mouse)
{
	this->back_button.tick(mouse);

	if (this->back_button.getPressed())
		this->back = true;
}


void	GameScreen::render(sf::RenderWindow &window, sf::Text &text,
							TextureManager &texture_manager, s_player &player,
							std::vector<s_apple> &apples, int nb_moves, int max_size,
							int reward)
{
	// left side
	this->drawGrid(window);
	this->drawElements(window, player, apples);

	// right side
	// this->displayInfos(window, text, nb_moves, max_size, reward);

	this->back_button.draw(window, text, texture_manager);
}


void	GameScreen::drawGrid(sf::RenderWindow &window)
{
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));

	rect.setOutlineColor(sf::Color(180, 180, 180));

	for (int i = 0; i < this->tiles_nb; i++)
	{
		for (int j = 0; j < this->tiles_nb; j++)
		{
			if (i == this->tiles_nb - 1 || j == this->tiles_nb - 1
				|| i == 0 || j == 0)
			{
				rect.setFillColor(sf::Color(90, 90, 90));
				rect.setOutlineThickness(-1);
			}
			else
			{
				rect.setFillColor(sf::Color::Transparent);
				rect.setOutlineThickness(-2);
			}
			rect.setPosition(sf::Vector2f(this->grid_pos.x + TILE_SIZE * i,
				this->grid_pos.y + TILE_SIZE * j));
			window.draw(rect);
		}
	}
}


void	GameScreen::drawElements(sf::RenderWindow &window, s_player &player,
								std::vector<s_apple> &apples)
{
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE - 4, TILE_SIZE - 4));

	// Draw player head
	rect.setFillColor(sf::Color(24, 135, 191));
	rect.setPosition(sf::Vector2f(this->grid_pos.x + player.head_pos.x * TILE_SIZE + 2,
		this->grid_pos.y + player.head_pos.y * TILE_SIZE + 2));
	window.draw(rect);

	// Draw player body parts
	rect.setFillColor(sf::Color(10, 87, 126));
	for (const sf::Vector2i body : player.body_pos)
	{
		rect.setPosition(sf::Vector2f(this->grid_pos.x + body.x * TILE_SIZE + 2,
			this->grid_pos.y + body.y * TILE_SIZE + 2));
		window.draw(rect);
	}

	// Draw apples
	for (auto [bonus, pos] : apples)
	{
		if (bonus)
			rect.setFillColor(sf::Color::Green);
		else
			rect.setFillColor(sf::Color::Red);
		rect.setPosition(sf::Vector2f(this->grid_pos.x + pos.x * TILE_SIZE + 2,
			this->grid_pos.y + pos.y * TILE_SIZE + 2));
		window.draw(rect);
	}
}


void	GameScreen::displayInfos(sf::RenderWindow &window, sf::Text &text,
								int nb_moves, int max_size, int reward)
{
	float			y_mult, y_init;
	sf::Vector2f	pos;
	std::string		all_str[] = {"Nb moves:", std::to_string(nb_moves),
							"Max size:", std::to_string(max_size),
							"Last reward:", std::to_string(reward)};

	pos.x = window.getSize().x * 3 / 4;
	y_init = window.getSize().y;
	y_mult = 0.1;

	for (std::string str : all_str)
	{
		pos.y = y_init * y_mult;
		drawText(window, text, str, pos, 35,
				sf::Text::Bold, sf::Color::White);
		y_mult += 0.15;
	}
}