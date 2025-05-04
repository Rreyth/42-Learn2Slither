#include <Visual/Screen/AIGameScreen.hpp>
#include <utils/functions.hpp>


AIGameScreen::AIGameScreen()
{
	this->tiles_nb = 12;
	this->back = false;
	this->next_step = false;
}


AIGameScreen::~AIGameScreen()
{
}


bool	AIGameScreen::BackToMenu() const
{
	return this->back;
}


bool	AIGameScreen::isNextStep() const
{
	return this->next_step;
}


void	AIGameScreen::visualInit(sf::RenderWindow &window, TextureManager &texture_manager,
								int tiles_nb)
{
	this->back = false;
	this->next_step = false;
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

	int x, y, w, h, x2;
	if (tiles_nb - 2 <= 13)
	{
		x = win_size.x * 0.9;
		x2 = win_size.x * 0.6;
		y = win_size.y * 0.9;
	}
	else if (tiles_nb - 2 <= 17)
	{
		x = win_size.x * 0.93;
		x2 = win_size.x * 0.57;
		y = win_size.y * 0.93;
	}
	else
	{
		x = win_size.x * 0.95;
		x2 = win_size.x * 0.55;
		y = win_size.y * 0.95;
	}
	w = 120;
	h = 40;
	this->back_button = RoundButton("Back to menu", 20, sf::Color::White,
						{x, y}, {w, h}, 10, sf::Color(200, 200, 200),
						sf::Color(100, 100, 100), sf::Color::White);

	this->step_button = RoundButton("Next step", 20, sf::Color::White,
						{x2, y}, {w, h}, 10, sf::Color(200, 200, 200),
						sf::Color(100, 100, 100), sf::Color::White);
}


void	AIGameScreen::tick(Mouse &mouse)
{
	this->back = false;
	this->next_step = false;

	this->back_button.tick(mouse);
	this->step_button.tick(mouse);

	if (this->back_button.getPressed())
		this->back = true;
	if (this->step_button.getPressed())
		this->next_step = true;
}


void	AIGameScreen::render(sf::RenderWindow &window, sf::Text &text,
							TextureManager &texture_manager, s_player &player,
							std::vector<s_apple> &apples, gameInfos &infos,
							float &move_time, visualModAiStep &ai_step)
{
	// background
	this->gameBackground(window, texture_manager);

	// left side
	this->drawGrid(window, texture_manager);
	this->drawElements(window, texture_manager, player, apples);

	// right side
	this->displayInfos(window, text, infos, move_time, ai_step);

	this->back_button.draw(window, text);
	this->step_button.draw(window, text);
}


void	AIGameScreen::gameBackground(sf::RenderWindow &window, TextureManager &texture_manager)
{
	drawBackground(window, texture_manager);
	sf::RectangleShape darkLayer(sf::Vector2f(window.getSize()));
	darkLayer.setFillColor(sf::Color(0, 0, 0, 200));

	window.draw(darkLayer);
}


void	AIGameScreen::drawGrid(sf::RenderWindow &window, TextureManager &texture_manager)
{
	sprite_name		sprite;
	sf::Vector2f	pos(this->grid_pos.x + 16, this->grid_pos.y + 16);

	for (int i = 0; i < this->tiles_nb; i++)
	{
		for (int j = 0; j < this->tiles_nb; j++)
		{
			if (i == this->tiles_nb - 1 || j == this->tiles_nb - 1
				|| i == 0 || j == 0)
				sprite = SPRITE_WALL;
			else
				sprite = SPRITE_GROUND;
			texture_manager.drawTexture(window, sprite, pos);
			pos.y += TILE_SIZE;
		}
		pos.x += TILE_SIZE;
		pos.y = this->grid_pos.y + 16;
	}
}


void AIGameScreen::drawElements(sf::RenderWindow &window, TextureManager &texture_manager, s_player &player,
								std::vector<s_apple> &apples)
{
	sf::Vector2f visual_pos(this->grid_pos.x + 16, this->grid_pos.y + 16);
	const float	 angle[] = {0, 180, -90, 90};

	// Draw player head
	visual_pos.x += player.head_pos.x * TILE_SIZE;
	visual_pos.y += player.head_pos.y * TILE_SIZE;
	texture_manager.rotateDraw(window, SPRITE_SNAKE_HEAD, visual_pos, sf::degrees(angle[player.dir]));

	// Draw player body parts
	for (int i = 0; i < player.body_parts.size(); i++)
	{
		s_body	  &actual = player.body_parts[i];
		player_dir dir = actual.dir;

		visual_pos.x = this->grid_pos.x + 16 + actual.pos.x * TILE_SIZE;
		visual_pos.y = this->grid_pos.y + 16 + actual.pos.y * TILE_SIZE;
		if (i == player.body_parts.size() - 1)
			texture_manager.rotateDraw(window, SPRITE_SNAKE_TAIL, visual_pos, sf::degrees(angle[dir]));
		else
		{
			sf::Vector2i next_pos = player.body_parts[i + 1].pos;
			sf::Vector2i prev_pos = player.head_pos;
			if (i != 0)
				prev_pos = player.body_parts[i - 1].pos;

			if (this->isAngle(actual.pos, prev_pos, next_pos))
			{
				dir = this->getAngleDir(actual.pos, prev_pos, next_pos);
				texture_manager.rotateDraw(window, SPRITE_SNAKE_BODY_ANGLE, visual_pos, sf::degrees(angle[dir]));
			}
			else
				texture_manager.rotateDraw(window, SPRITE_SNAKE_BODY, visual_pos, sf::degrees(angle[dir]));
		}
	}

	// Draw apples
	for (auto [bonus, pos]: apples)
	{
		visual_pos.x = this->grid_pos.x + 16 + pos.x * TILE_SIZE;
		visual_pos.y = this->grid_pos.y + 16 + pos.y * TILE_SIZE;
		if (bonus)
			texture_manager.drawTexture(window, SPRITE_GREEN_APPLE, visual_pos);
		else
			texture_manager.drawTexture(window, SPRITE_RED_APPLE, visual_pos);
	}
}
void AIGameScreen::displayInfos(sf::RenderWindow &window, sf::Text &text, gameInfos &infos, float &move_time,
								visualModAiStep &ai_step)
{
	int							i;
	float						y_mult, y_init, x_sec, text_size;
	sf::Vector2f				pos;
	std::vector<std::string>	all_str = {"Time per move:", std::to_string(move_time),
							"Last reward:", std::to_string(infos.last_reward),
							"Nb steps:", std::to_string(ai_step.step_count),
							"Max steps:", std::to_string(ai_step.max_step),
							"Current size:", std::to_string(ai_step.curr_len),
							"Max size:", std::to_string(ai_step.max_len),
							"Green apples (this session):", std::to_string(ai_step.bonus_count),
							"Max green apples:", std::to_string(ai_step.max_bonus),
							"Red apples (this session):", std::to_string(ai_step.malus_count),
							"Max red apples:", std::to_string(ai_step.max_malus),
							"Session:", std::to_string(ai_step.session_count), "/", std::to_string(ai_step.total_sessions)};

	y_init = window.getSize().y;
	y_mult = 0.05;
	pos.x = window.getSize().x * 0.675;
	x_sec = window.getSize().x * 0.875;
	text_size = window.getSize().y * 0.05;
	i = 0;

	while (i < all_str.size() - 4)
	{
		pos.y = y_init * y_mult;
		drawText(window, text, all_str[i], pos, text_size,
						sf::Text::Bold, sf::Color::White);
		drawText(window, text, all_str[i + 1], {x_sec, pos.y},
					text_size, sf::Text::Bold, sf::Color::White);
		y_mult += 0.075;
		i += 2;
	}
	pos.y = y_init * y_mult;
	drawText(window, text, all_str[i], pos, text_size, sf::Text::Bold, sf::Color::White);
	pos.x = window.getSize().x * 0.83;
	drawText(window, text, all_str[i + 1], pos, text_size, sf::Text::Bold, sf::Color::White);
	drawText(window, text, all_str[i + 2], {x_sec, pos.y}, text_size, sf::Text::Bold, sf::Color::White);
	pos.x = window.getSize().x * 0.915;
	drawText(window, text, all_str[i + 3], pos, text_size, sf::Text::Bold, sf::Color::White);
}


bool	AIGameScreen::isAngle(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos)
{
	return  !((actual_pos.x == prev_pos.x && actual_pos.x == next_pos.x) ||
		(actual_pos.y == prev_pos.y && actual_pos.y == next_pos.y));
}


player_dir	AIGameScreen::getAngleDir(sf::Vector2i actual_pos, sf::Vector2i prev_pos, sf::Vector2i next_pos)
{
	if ((prev_pos.x == actual_pos.x + 1 && next_pos.y == actual_pos.y - 1) ||
		(prev_pos.y == actual_pos.y - 1 && next_pos.x == actual_pos.x + 1))
		return UP;

	if ((prev_pos.x == actual_pos.x - 1 && next_pos.y == actual_pos.y + 1) ||
		(prev_pos.y == actual_pos.y + 1 && next_pos.x == actual_pos.x - 1))
		return DOWN;

	if ((prev_pos.x == actual_pos.x - 1 && next_pos.y == actual_pos.y - 1) ||
		(prev_pos.y == actual_pos.y - 1 && next_pos.x == actual_pos.x - 1))
		return LEFT;

	return RIGHT;
}
