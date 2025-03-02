#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <Visual/Visual.hpp>
#include <utils/enums.hpp>


class Environment;


class InputManager
{
	public:
		InputManager();
		~InputManager();

		void	manageInput(Environment &env, Visual &visual, gameState state);

	private:
		bool buttonPressed;

		void manageKeyboard(Environment &env, Visual &visual);
		void manageMouse(Environment &env, Visual &visual);
};


#endif //INPUTMANAGER_HPP
