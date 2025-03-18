#include <Visual/Visual.hpp>
#include <Environment/Environment.hpp>

Visual::Visual(flags &launch_flags) : text(this->font, "", 35), menu(launch_flags)
{
	sf::Vector2u win_size(864, 480);

	this->window = sf::RenderWindow(sf::VideoMode({win_size.x, win_size.y}), "I'M A SNAKE!", sf::Style::Close);
	this->window.setFramerateLimit(MAX_FPS);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	sf::Vector2i windowPosition((desktop.size.x - window.getSize().x) / 2, (desktop.size.y - window.getSize().y) / 2);

	this->window.setPosition(windowPosition);
	this->window.setKeyRepeatEnabled(false);

	try
	{
		this->texture_manager.loadTextures();
		if (!this->font.openFromFile("data/SquadaOne.ttf"))
			throw std::invalid_argument("");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		window.close();
		exit(EXIT_FAILURE);
	}
	this->text = sf::Text(this->font, "", 35);
	this->state = MENU;
	this->menu.visualInit(win_size, this->texture_manager);
}


Visual::~Visual()
{
}


sf::RenderWindow &Visual::getWin()
{
	return (this->window);
}


gameState	&Visual::getState()
{
	return (this->state);
}


void	Visual::setState(gameState state)
{
	this->state = state;
}


void	Visual::render(s_player &player, std::vector<s_apple> &apples,
						gameInfos &infos)
{
	this->window.clear();

	switch (this->state)
	{
		case MENU:
			this->menu.render(this->window, this->text, this->texture_manager);
			break;
		case GAME:
			this->game_screen.render(this->window, this->text, this->texture_manager,
									player, apples, infos);
			break;
		case GAMEOVER:
			this->game_over_screen.render(this->window, this->text, this->texture_manager);
			break;
	}

	this->window.display();
}


void	Visual::tick(Environment &env, Mouse &mouse)
{
	s_settings	settings;
	switch (this->state)
	{
		case MENU:
			this->menu.tick(env, mouse, this->window);
			settings = this->menu.getSettings();
			if (settings.start)
			{
				this->state = GAME;

				this->game_screen.visualInit(this->window, this->texture_manager,
											settings.size + 2);
				env.startGame(settings);
			}
			//TODO: add ai play
			break;
		case GAME:
			this->game_screen.tick(mouse);
			if (this->game_screen.BackToMenu())
			{
				this->state = MENU;
				this->menu.getSettings().start = false;
				this->resetWindow();
				env.changeWin();
			}
			break;
		case GAMEOVER:
			this->game_over_screen.tick(mouse);
			if (this->game_over_screen.backToMenu())
			{
				this->state = MENU;
				this->menu.getSettings().start = false;
				this->resetWindow();
				env.changeWin();
			}
			else if (this->game_over_screen.getQuit())
				env.close();
			break;
	}
}


void	Visual::gameOverInit(gameInfos &infos)
{
	this->game_over_screen.init(infos, this->window, this->texture_manager);
}




void	Visual::resetWindow()
{
	sf::Vector2u win_size(864, 480);

	window.create(sf::VideoMode({win_size.x, win_size.y}), "I'M A SNAKE!", sf::Style::Close);
	window.setFramerateLimit(MAX_FPS);
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i windowPosition((desktop.size.x - win_size.x) / 2, (desktop.size.y - win_size.y) / 2);
	window.setPosition(windowPosition);
	window.setKeyRepeatEnabled(false);
}
