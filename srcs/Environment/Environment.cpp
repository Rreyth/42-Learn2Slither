#include "Environment.hpp"

Environment::Environment(const flags &launch_flags) : grid(launch_flags.size)
{
	this->env_flags = launch_flags;

	// TODO: if visual init visual
	// TODO: init agent with sessions and dontlearn
}


Environment::~Environment()
{
}


void Environment::run()
{

}




// # print if no visual
// # load msg
// # Training...
// # Session X / nb session (rewrite each loop)
// # end message with max life time and max length