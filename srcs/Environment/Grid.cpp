#include "Grid.hpp"

#include <random>
#include <iostream>

Grid::Grid(const int &size)
{
	this->size = size + 2;
	this->initPlayer();
	this->initApples();
	this->initGrid();
}


 Grid::~Grid()
{}


static sf::Vector2i	positionBody(const sf::Vector2i &prev_pos, const player_dir &dir)
{
	sf::Vector2i	body_pos;
	switch (dir)
	{
		case UP:
			body_pos.x = prev_pos.x;
			body_pos.y = prev_pos.y + 1;
			break;
		case DOWN:
			body_pos.x = prev_pos.x;
			body_pos.y = prev_pos.y - 1;
			break;
		case LEFT:
			body_pos.x = prev_pos.x + 1;
			body_pos.y = prev_pos.y;
			break;
		case RIGHT:
			body_pos.x = prev_pos.x - 1;
			body_pos.y = prev_pos.y;
			break;
		default:
			break;
	}
	return body_pos;
}


static bool hasEnoughSpace(const sf::Vector2i &head_pos, const player_dir &dir, const int &size)
{
	switch (dir)
	{
		case UP:
			return head_pos.y + 2 <= size - 2;
		case DOWN:
			return head_pos.y - 2 >= 1;
		case LEFT:
			return head_pos.x + 2 <= size - 2;
		case RIGHT:
			return head_pos.x - 2 >= 1;
		default:
			return false;
	}
}


void	Grid::initPlayer()
{
	std::random_device	rd;
	std::mt19937		gen(rd());

	std::uniform_int_distribution<int> int_dist(1, this->size - 2);
	this->player.head_pos.x = int_dist(gen);
	this->player.head_pos.y = int_dist(gen);

	std::uniform_int_distribution dir_dist(0, 3);

	this->player.dir = static_cast<player_dir>(dir_dist(gen));

	while (!hasEnoughSpace(this->player.head_pos, this->player.dir, this->size))
		this->player.dir = static_cast<player_dir>(dir_dist(gen));

	sf::Vector2i	body1, body2;

	body1 = positionBody(this->player.head_pos, this->player.dir);
	body2 = positionBody(body1, this->player.dir);

	this->player.body_pos.insert(this->player.body_pos.end(), {body1, body2});
}


bool	Grid::occupiedByPlayer(const sf::Vector2i &pos)
{
	if (pos == this->player.head_pos)
		return true;

	for (const sf::Vector2i &body : this->player.body_pos)
	{
		if (pos == body)
			return true;
	}
	return false;
}


void	Grid::initApples()
{
	s_apple	bonus1{true},
			bonus2{true},
			malus{false};

	std::random_device	rd;
	std::mt19937		gen(rd());

	std::uniform_int_distribution int_dist(1, this->size - 2);

	bonus1.pos.x = int_dist(gen);
	bonus1.pos.y = int_dist(gen);
	while (this->occupiedByPlayer(bonus1.pos))
	{
		bonus1.pos.x = int_dist(gen);
		bonus1.pos.y = int_dist(gen);
	}

	bonus2.pos.x = int_dist(gen);
	bonus2.pos.y = int_dist(gen);
	while (bonus2.pos == bonus1.pos || this->occupiedByPlayer(bonus2.pos))
	{
		bonus2.pos.x = int_dist(gen);
		bonus2.pos.y = int_dist(gen);
	}

	malus.pos.x = int_dist(gen);
	malus.pos.y = int_dist(gen);
	while (this->occupiedByPlayer(malus.pos) || malus.pos == bonus1.pos || malus.pos == bonus2.pos)
	{
		malus.pos.x = int_dist(gen);
		malus.pos.y = int_dist(gen);
	}

	this->apples.insert(this->apples.end(), {bonus1, bonus2, malus});
}


bool	Grid::occupiedByApples(const sf::Vector2i &pos)
{
	for (const s_apple &apple : this->apples)
	{
		if (pos == apple.pos)
			return true;
	}
	return false;
}


void Grid::initGrid()
{
	sf::Vector2i	test_pos(0, 0);

	this->grid = "";

	for (int y = 0; y <= this->size - 1; y++)
	{
		test_pos.y = y;
		for (int x = 0; x <= this->size - 1; x++)
		{
			test_pos.x = x;
			if (y == 0 || y == this->size - 1 || x == 0 || x == this->size - 1)
				this->grid += "W";
			else if (this->occupiedByPlayer(test_pos))
			{
				if (this->player.head_pos == test_pos)
					this->grid += "H";
				else
					this->grid += "S";
			}
			else if (this->occupiedByApples(test_pos))
			{
				for (const s_apple &apple : this->apples)
				{
					if (test_pos == apple.pos)
					{
						if (apple.bonus)
							this->grid += 'G';
						else
							this->grid += 'R';
					}
				}
			}
			else
				this->grid += "0";
		}
	}

	//TODO RM

	std::cout << "player pos : " << this->player.head_pos.x << ", " << this->player.head_pos.y << std::endl;
	std::cout << "game map:" << std::endl;
	for (int i = 0; i <= this->grid.length(); i++)
	{
		if (i % this->size == 0)
			std::cout << std::endl;
		std::cout << this->grid[i];
	}
	std::cout << std::endl;
}


void	Grid::movePlayer(const player_dir &dir) // TODO
{
	// move to inv of old dir not possible
	// move head and body parts
	// if move in wall or in body part -> dead
}


std::string	Grid::getAgentView() const
{
	std::string	agent_view = "";

	int			y = this->player.head_pos.x;
	while (y <= this->grid.length())
	{
		agent_view += this->grid[y];
		y += this->size;
	}

	int	x = 0;
	y = this->player.head_pos.y;
	while (x < this->size)
	{
		agent_view += this->grid[(y * this->size) + x];
		x++;
	}

	return (agent_view);
}


s_player&	Grid::getPlayer()
{
	return (this->player);
}


std::vector<s_apple>&	Grid::getApples()
{
	return (this->apples);
}


std::string	&Grid::getGrid()
{
	return (this->grid);
}
