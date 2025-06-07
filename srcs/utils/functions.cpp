#include <utils/functions.hpp>
#include <cmath>
#include <iostream>

void	drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					int x, int y, int fontSize, sf::Text::Style style, sf::Color color)
{
	float w, h;

	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setStyle(style);
	w = text.getLocalBounds().size.x;
	h = text.getLocalBounds().size.y + fontSize / 2;

	sf::Vector2f pos(x - w / 2, y - h / 2);

	text.setPosition(pos);

	text.setFillColor(color);
	window.draw(text);
}


void	drawText(sf::RenderWindow &window, sf::Text &text, std::string str,
					sf::Vector2f pos, int fontSize, sf::Text::Style style, sf::Color color)
{
	float w, h;

	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setStyle(style);
	w = text.getLocalBounds().size.x;
	h = text.getLocalBounds().size.y + fontSize / 2;

	sf::Vector2f accurate_pos(pos.x - w / 2, pos.y - h / 2);

	text.setPosition(accurate_pos);

	text.setFillColor(color);
	window.draw(text);
}


bool	isInt(float x)
{
	return (x == std::trunc(x));
}


std::string	formatFloat(float x)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << x;
	std::string s = oss.str();
	return s;
}


void	drawBackground(sf::RenderWindow &window, TextureManager &texture_manager)
{
	sf::Vector2f win_size(window.getSize());
	bool	head = false, tail = false;
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
		if (y >= win_size.y * 0.2 && y <= win_size.y * 0.85 && !tail)
		{
			if (y <= win_size.y * 0.25 && !head)
			{
				texture_manager.drawTexture(window, SPRITE_SNAKE_HEAD, sf::Vector2f(win_size.x / 2, y));
				head = true;
			}
			else if (y >= win_size.y * 0.8)
			{
				texture_manager.drawTexture(window, SPRITE_SNAKE_TAIL, sf::Vector2f(win_size.x / 2, y));
				tail = true;
			}
			else
				texture_manager.drawTexture(window, SPRITE_SNAKE_BODY, sf::Vector2f(win_size.x / 2, y));
		}
	}
}


void	waitForUser()
{
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
}


void	printStepInfos(const int &session_counter, const int &step_counter,
				const player_dir &action, const learnStep &learn_step)
{
	std::string actions[] = {"up", "down", "left", "right"};

	std::cout << "Step infos:" << std::endl
	<< "session number: " << session_counter << std::endl
	<< "step number: " << step_counter << std::endl
	<< "action: " << actions[action] << std::endl
	<< "reward: " << learn_step.reward << std::endl << std::endl;
}


void	printSessionInfos(const int &session_counter, const int &session_total, const int &step_counter,
				const int &len, const int &bonus_counter, const int &malus_counter)
{
	std::string actions[] = {"up", "down", "left", "right"};

	std::cout << "End of session " << session_counter << " / " << session_total << std::endl
	<< "life time (steps): " << step_counter << std::endl
	<< "final length: " << len << std::endl
	<< "green apples eaten:\t" << bonus_counter << std::endl
	<< "red apples eaten:\t" << malus_counter << std::endl << std::endl;
}