#include <Environment/InputManager.hpp>
#include <Environment/Environment.hpp>

#include <iostream>


InputManager::InputManager()
{
	this->buttonPressed = false;
}


 InputManager::~InputManager()
{
}


void	InputManager::manageKeyboard(Environment &env, Visual &visual)
{
	sf::RenderWindow	&win = visual.getWin();
	while (const std::optional event = win.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			env.close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->code == sf::Keyboard::Key::Escape)
				env.close();
			else if (keyPressed->code == sf::Keyboard::Key::Up)
			{
				env.setMove(true);
				env.getGrid().movePlayer(UP);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Down)
			{
				env.setMove(true);
				env.getGrid().movePlayer(DOWN);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Left)
			{
				env.setMove(true);
				env.getGrid().movePlayer(LEFT);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Right)
			{
				env.setMove(true);
				env.getGrid().movePlayer(RIGHT);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Space)
			{
				env.reset();
			}
		}
	}
}


void	InputManager::manageMouse(Environment &env, Visual &visual)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(visual.getWin());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->buttonPressed)
	{
		this->buttonPressed = true;
		std::cout << "CLICK" << std::endl;
		//visual.click(mousePos) -> check if mouse on button -> return button ?
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->buttonPressed)
	{
		this->buttonPressed = false;
		std::cout << "RELEASE" << std::endl;
	}
}


void	InputManager::manageInput(Environment &env, Visual &visual, gameState state)
{
	if (state == GAME)
		this->manageKeyboard(env, visual);
	this->manageMouse(env, visual);
}