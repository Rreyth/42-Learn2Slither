#include <Environment/InputManager.hpp>
#include <Environment/Environment.hpp>

#include <iostream>


InputManager::InputManager()
{
}


 InputManager::~InputManager()
{
}


void	InputManager::manageKeyboard(Environment &env, const std::optional<sf::Event> &event)
{
	if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
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


void	InputManager::manageMouse(Environment &env, Visual &visual, const std::optional<sf::Event> &event)
{
	if (const auto* pressedBtn = event->getIf<sf::Event::MouseButtonPressed>())
	{
		if (pressedBtn->button == sf::Mouse::Button::Left)
		{
			mouse.updateMbutton(MBUT_LEFT, true);
		}
	}
	else if (const auto* releasedBtn = event->getIf<sf::Event::MouseButtonReleased>())
	{
		if (releasedBtn->button == sf::Mouse::Button::Left)
		{
			mouse.updateMbutton(MBUT_LEFT, false);
		}
	}
}


void	InputManager::manageInput(Environment &env, Visual &visual, gameState state)
{
	sf::RenderWindow	&win = visual.getWin();
	while (const std::optional event = win.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			env.close();
		this->manageMouse(env, visual, event);
		if (state == GAME)
			this->manageKeyboard(env, event);
	}
}