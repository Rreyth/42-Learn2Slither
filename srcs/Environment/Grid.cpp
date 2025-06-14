#include <Environment/Grid.hpp>
#include <iostream>
#include <random>


Grid::Grid(const int &size)
{
	this->size = size + 2;
	this->initPlayer();
	this->initApples();
	this->closer = false;
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

	this->player.body_parts.clear();
	while (!hasEnoughSpace(this->player.head_pos, this->player.dir, this->size))
		this->player.dir = static_cast<player_dir>(dir_dist(gen));

	sf::Vector2i	pos1, pos2;

	pos1 = positionBody(this->player.head_pos, this->player.dir);
	pos2 = positionBody(pos1, this->player.dir);

	s_body body1 = {pos1, this->player.dir};
	s_body body2 = {pos2, this->player.dir};

	this->player.body_parts.insert(this->player.body_parts.end(), {body1, body2});
}


bool	Grid::occupiedByPlayer(const sf::Vector2i &pos)
{
	if (pos == this->player.head_pos)
		return true;

	for (const s_body &body : this->player.body_parts)
	{
		if (pos == body.pos)
			return true;
	}
	return false;
}


bool	Grid::occupiedByBody(const sf::Vector2i &pos)
{
	for (const s_body &body : this->player.body_parts)
	{
		if (pos == body.pos)
			return true;
	}
	return false;
}


void	Grid::initApples()
{
	this->apples.clear();
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


void	Grid::movePlayer(const player_dir &dir)
{
	// move head
	s_body	old_pos, tmp;
	old_pos.pos = this->player.head_pos;
	old_pos.dir = this->player.dir;
	this->closer = this->moveInBonusDir(old_pos.pos, dir);
	switch (dir)
	{
		case UP:
			this->player.head_pos.y--;
			break;
		case DOWN:
			this->player.head_pos.y++;
			break;
		case LEFT:
			this->player.head_pos.x--;
			break;
		case RIGHT:
			this->player.head_pos.x++;
	}
	this->player.dir = dir;
	if (this->occupiedByBody(this->player.head_pos))
		return;
	// move body parts
	int i = 0;
	while (i < this->player.body_parts.size())
	{
		tmp = this->player.body_parts[i];
		this->player.body_parts[i] = old_pos;
		old_pos = tmp;
		i++;
	}
	if (this->player.body_parts.size() > 1)
		this->player.body_parts.back().dir = this->player.body_parts[i - 2].dir;
	else if (this->player.body_parts.size() == 1)
		this->player.body_parts.back().dir = this->player.dir;

	this->next_body_part = old_pos;
}


State	Grid::getAgentState()
{
	return State(this->getBonusDir(),
				this->getDangerDist(UP),
				this->getDangerDist(DOWN),
				this->getDangerDist(LEFT),
				this->getDangerDist(RIGHT),
				this->getMalusDist(UP),
				this->getMalusDist(DOWN),
				this->getMalusDist(LEFT),
				this->getMalusDist(RIGHT));
}


void	Grid::printAgentView()
{
	const sf::Vector2i	head_pos = this->player.head_pos;
	sf::Vector2i	pos = head_pos;
	char			view;
	for (int y = 0; y < this->size; y++)
	{
		pos.y = y;
		if (pos.y == head_pos.y)
		{
			for (int x = 0; x < this->size; x++)
			{
				pos.x = x;
				if (x == 0 || x == this->size - 1)
					view = 'W';
				else if (this->occupiedByApples(pos))
				{
					if (this->occupiedByMalus(pos))
						view = 'R';
					else
						view = 'G';
				}
				else if (this->occupiedByBody(pos))
					view = 'S';
				else if (pos == head_pos)
					view = 'H';
				else
					view = '0';
				std::cout << view;
			}
			std::cout << std::endl;
			continue;
		}
		if (y == 0 || y == this->size - 1)
			view = 'W';
		else if (this->occupiedByApples(pos))
		{
			if (this->occupiedByMalus(pos))
				view = 'R';
			else
				view = 'G';
		}
		else if (this->occupiedByBody(pos))
			view = 'S';
		else
			view = '0';

		std::cout << std::string(head_pos.x, ' ') << view << std::endl;
	}
}


s_player&	Grid::getPlayer()
{
	return (this->player);
}


std::vector<s_apple>&	Grid::getApples()
{
	return (this->apples);
}


s_apple&	Grid::getAppleByPos(const sf::Vector2i &pos)
{
	for (s_apple &apple : this->apples)
	{
		if (pos == apple.pos)
			return (apple);
	}
	return s_apple() = {};
}


bool	Grid::wallHit(const sf::Vector2i &pos)
{
	return (pos.x == 0 || pos.y == 0
		|| pos.x == this->size - 1 || pos.y == this->size - 1);
}


void	Grid::moveApple(s_apple &apple)
{
	std::random_device	rd;
	std::mt19937		gen(rd());

	std::uniform_int_distribution int_dist(1, this->size - 2);

	sf::Vector2i	pos;
	pos.x = int_dist(gen);
	pos.y = int_dist(gen);
	while (this->occupiedByApples(pos) || this->occupiedByPlayer(pos))
	{
		pos.x = int_dist(gen);
		pos.y = int_dist(gen);
	}
	apple.pos = pos;
}


bool	Grid::moveInBonusDir(const sf::Vector2i &pos, player_dir dir)
{
	for (s_apple &apple : this->apples)
	{
		if (!apple.bonus)
			continue;
		if ((dir == UP && (pos.y > apple.pos.y && pos.x == apple.pos.x))
			|| (dir == DOWN && (pos.y < apple.pos.y && pos.x == apple.pos.x))
			|| (dir == LEFT && (pos.x > apple.pos.x && pos.y == apple.pos.y))
			|| (dir == RIGHT && (pos.x < apple.pos.x && pos.y == apple.pos.y)))
			return true;
	}
	return false;
}


bool	Grid::isCloserMove() const
{
	return (this->closer);
}


void	Grid::playerGrow()
{
	this->player.body_parts.push_back(this->next_body_part);
	if (this->player.body_parts.size() == 1)
		this->player.body_parts.back().dir = this->player.dir;
}


int	Grid::playerShrink()
{
	if (this->player.body_parts.empty())
		return -1;
	this->player.body_parts.pop_back();

	int size = this->player.body_parts.size();
	if (size > 1)
		this->player.body_parts.back().dir = this->player.body_parts[size - 2].dir;
	else if (size == 1)
		this->player.body_parts.back().dir = this->player.dir;
	return 1;
}


int Grid::getPlayerLen() const
{
	return this->player.body_parts.size() + 1; //body + head
}


void	Grid::reset()
{
	this->initPlayer();
	this->initApples();
	this->closer = false;
}

void	Grid::start(int size)
{
	this->size = size + 2;
	this->initPlayer();
	this->initApples();
	this->closer = false;
}


int	Grid::getBonusDir()
{
	// 0 = none, 1 = up, 2 = down, 3 = left, 4 = right
	const sf::Vector2i pos = this->player.head_pos;
	for (s_apple &apple : this->apples)
	{
		if (!apple.bonus)
			continue;
		if (pos.y > apple.pos.y && pos.x == apple.pos.x)
			return 1;
		if (pos.y < apple.pos.y && pos.x == apple.pos.x)
			return 2;
		if (pos.x > apple.pos.x && pos.y == apple.pos.y)
			return 3;
		if (pos.x < apple.pos.x && pos.y == apple.pos.y)
			return 4;
	}
	return 0;
}


int	Grid::getDangerDist(const player_dir dir)
{
	// danger = wall or body part
	// distance from 0 (no danger) to 4

	sf::Vector2i test_pos = this->player.head_pos;

	for (int dist = 1; dist < 5; dist++)
	{
		switch (dir)
		{
			case UP:
				test_pos.y -= 1;
				break;
			case DOWN:
				test_pos.y += 1;
				break;
			case LEFT:
				test_pos.x -= 1;
				break;
			case RIGHT:
				test_pos.x += 1;
				break;
		}
		if (this->occupiedByBody(test_pos) || this->wallHit(test_pos))
			return dist;
	}
	return 0;
}


int	Grid::getMalusDist(const player_dir dir)
{
	// red apple check
	// distance from 0 (no malus) to 4

	sf::Vector2i test_pos = this->player.head_pos;

	for (int dist = 1; dist < 5; dist++)
	{
		switch (dir)
		{
			case UP:
				test_pos.y -= 1;
			break;
			case DOWN:
				test_pos.y += 1;
			break;
			case LEFT:
				test_pos.x -= 1;
			break;
			case RIGHT:
				test_pos.x += 1;
			break;
		}
		if (this->occupiedByMalus(test_pos))
			return dist;
	}
	return 0;
}


bool	Grid::occupiedByMalus(const sf::Vector2i &pos)
{
	for (const s_apple &apple : this->apples)
	{
		if (apple.bonus)
			continue;
		if (pos == apple.pos)
			return true;
	}
	return false;
}
