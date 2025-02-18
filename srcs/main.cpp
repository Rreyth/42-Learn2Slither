#include "parser.hpp"
#include "Environment/Environment.hpp"


int main(int argc, char **argv)
{
	flags launch_flags = parse_flags(argc, argv);

	if (launch_flags.invalid)
		return (EXIT_FAILURE);

	Environment env(launch_flags);
	env.run();

	return (EXIT_SUCCESS);
}
