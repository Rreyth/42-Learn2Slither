#include "Visual.hpp"

Visual::Visual(const int &tiles)
{
	this->tiles_nb = tiles + 2;
	sf::Vector2u win_size(this->tiles_nb * TILE_SIZE * 2, this->tiles_nb * TILE_SIZE);
	this->grid_pos = sf::Vector2i(win_size.x * 0.5 - win_size.y,
		win_size.y * 0.5 - this->tiles_nb * 0.5 * TILE_SIZE);

	this->window = sf::RenderWindow(sf::VideoMode({win_size.x, win_size.y}),
		"I'M A SNAKE!", sf::Style::Close);
	this->window.setFramerateLimit(MAX_FPS);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	sf::Vector2i windowPosition(
		(desktop.size.x - window.getSize().x) / 2,
		(desktop.size.y - window.getSize().y) / 2
	);

	this->window.setPosition(windowPosition);
	this->window.setKeyRepeatEnabled(false);
}


Visual::~Visual()
{
}


sf::RenderWindow &Visual::getWin()
{
	return (this->window);
}


void	Visual::drawGrid()
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
				rect.setOutlineThickness(0);
			}
			else
			{
				rect.setFillColor(sf::Color::Transparent);
				rect.setOutlineThickness(-2);
			}
			rect.setPosition(sf::Vector2f(this->grid_pos.x + TILE_SIZE * i,
				this->grid_pos.y + TILE_SIZE * j));
			this->window.draw(rect);
		}
	}
}


void	Visual::drawElements(s_player &player, std::vector<s_apple> &apples)
{
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE - 4, TILE_SIZE - 4));

	// Draw player head
	rect.setFillColor(sf::Color(24, 135, 191));
	rect.setPosition(sf::Vector2f(this->grid_pos.x + player.head_pos.x * TILE_SIZE + 2,
		this->grid_pos.y + player.head_pos.y * TILE_SIZE + 2));
	this->window.draw(rect);

	// Draw player body parts
	rect.setFillColor(sf::Color(10, 87, 126));
	for (const sf::Vector2i body : player.body_pos)
	{
		rect.setPosition(sf::Vector2f(this->grid_pos.x + body.x * TILE_SIZE + 2,
			this->grid_pos.y + body.y * TILE_SIZE + 2));
		this->window.draw(rect);
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
		this->window.draw(rect);
	}
}


void	Visual::render(s_player &player, std::vector<s_apple> &apples)
{
	//TODO : replace rect with sprites
	this->window.clear();
	this->drawGrid();
	this->drawElements(player, apples);
	this->window.display();
}
