#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <Visual/Visual.hpp>
#include <utils/Mouse.hpp>
#include <utils/enums.hpp>


class Environment;


class InputManager
{
	public:
		InputManager();
		~InputManager();

		void	manageInput(Environment &env, Visual &visual, gameState state);

	private:
		Mouse	mouse;

		void manageKeyboard(Environment &env, const std::optional<sf::Event> &event);
		void manageMouse(Environment &env, Visual &visual, const std::optional<sf::Event> &event);
};


#endif //INPUTMANAGER_HPP
