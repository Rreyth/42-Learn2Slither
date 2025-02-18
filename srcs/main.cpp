#include "parser.hpp"


int main(int argc, char **argv)
{
	flags launch_flags = parse_flags(argc, argv);

	if (launch_flags.invalid)
		return (EXIT_FAILURE);


	//TODO: launch env with flags
	//MVC pattern ?
}


// # print if no visual
// # load msg
// # Training...
// # Session X / nb session (rewrite each loop)
// # end message with max life time and max length


// VISUAL
// sf::RenderWindow window(sf::VideoMode({1600, 900}), "I'M A SNAKE!");
// // sf::CircleShape shape(100.f);
// // shape.setFillColor(sf::Color::Green);
//
// while (window.isOpen())
// {
// 	while (const std::optional event = window.pollEvent())
// 	{
// 		if (event->is<sf::Event::Closed>())
// 			window.close();
// 	}
//
// 	window.clear();
// 	// window.draw(shape);
// 	window.display();
// }





// AGENT
// # Q = {}
// # init q table +- -> dict {state : [up, down, left, right]}
// # Q[state][action]
//
// # closer to bonus + 1
// # take bonus + 30
// # take malus -30
// # dead -100
//
// # chose move + update q table (or create entry for the first encounter)
//
// # chose move without learn