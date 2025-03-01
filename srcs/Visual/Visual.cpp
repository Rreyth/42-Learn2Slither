#include "Visual.hpp"

Visual::Visual(const int &grid_size)
{
	this->grid_visual_size = grid_size + 2;
	this->window = sf::RenderWindow(sf::VideoMode({1600, 900}), "I'M A SNAKE!", sf::Style::Close);
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

	for (int i = 0; i < this->grid_visual_size; i++)
	{
		for (int j = 0; j < this->grid_visual_size; j++)
		{
			if (i == this->grid_visual_size - 1 || j == this->grid_visual_size - 1
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
			rect.setPosition(sf::Vector2f(TILE_SIZE * i, TILE_SIZE * j));
			this->window.draw(rect);
		}
	}
}


void	Visual::drawElements(s_player &player, std::vector<s_apple> &apples)
{
	sf::RectangleShape	rect(sf::Vector2f(TILE_SIZE - 4, TILE_SIZE - 4));

	// Draw player head
	rect.setFillColor(sf::Color(24, 135, 191));
	rect.setPosition(sf::Vector2f(player.head_pos.x * TILE_SIZE + 2, player.head_pos.y * TILE_SIZE + 2));
	this->window.draw(rect);

	// Draw player body parts
	rect.setFillColor(sf::Color(10, 87, 126));
	for (const sf::Vector2i body : player.body_pos)
	{
		rect.setPosition(sf::Vector2f(body.x * TILE_SIZE + 2, body.y * TILE_SIZE + 2));
		this->window.draw(rect);
	}

	// Draw apples
	for (auto [bonus, pos] : apples)
	{
		if (bonus)
			rect.setFillColor(sf::Color::Green);
		else
			rect.setFillColor(sf::Color::Red);
		rect.setPosition(sf::Vector2f(pos.x * TILE_SIZE + 2, pos.y * TILE_SIZE + 2));
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
