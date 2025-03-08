#include <utils/parser.hpp>
#include <getopt.h>
#include <iostream>

flags parse_flags(int argc, char **argv)
{
	flags		parsed_flags;
	std::string	help;
	int			opt;
	int			option_index = 0;
	int			test_int;

	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"visual", no_argument, 0, 'v'},
		{"save", required_argument, 0, 's'},
		{"load", required_argument, 0, 'l'},
		{"dontlearn", no_argument, 0, 'd'},
		{"stepmode", no_argument, 0, 'z'},
		{"size", required_argument, 0, 'n'},
		{"sessions", required_argument, 0, 'r'},
		{0, 0, 0, 0}
	};

	help = "usage: ./snake [-h/--help] [-v/--visual] [-s/--save {filename}] "
		"[-l/--load {filename}] [--dontlearn] [--stepmode] "
		"[-n/--size {10 <= int <= 25}] [--sessions {int > 0}]]"
		"\n\noptions:\n"
		"  -h, --help\t\tShow this help message\n"
		"  -v, --visual\t\tTurn on visual output\n"
		"  -s, --save {file}\tSave Q table to file\n"
		"  -l, --load {file}\tLoad Q table from file\n"
		"  --dontlearn\t\tRun without learning\n"
		"  --stepmode\t\tRun in step-by-step mode\n"
		"  -n, --size {int}\tSize of the game grid between 10 and 25\n"
		"  --sessions\t\tNumber of sessions Agent will run\n";

	while ((opt = getopt_long(argc, argv, "hvs:l:n:r:", long_options, &option_index)) != -1)
	{
		switch (opt)
		{
			case 'h':
				std::cout << help << std::endl;
				parsed_flags.help = true;
				break;
			case 'v':
				parsed_flags.visual = true;
				break;
			case 's':
				parsed_flags.save = true;
				parsed_flags.savefile = optarg;
				break;
			case 'l':
				parsed_flags.load = true;
				parsed_flags.loadfile = optarg;
				break;
			case 'd':
				parsed_flags.dontlearn = true;
				break;
			case 'z':
				parsed_flags.stepmode = true;
				break;
			case 'n':
				test_int = atoi(optarg);
				if (test_int < 10 || test_int > 25)
				{
					parsed_flags.invalid = true;
					std::cerr << "Invalid size: " << test_int << " | size must be between 10 and 25" << std::endl;
				}
				parsed_flags.size = test_int;
				break;
			case 'r':
				test_int = atoi(optarg);
				if (test_int <= 0)
				{
					parsed_flags.invalid = true;
					std::cerr << "Invalid number of sessions: " << test_int << " | number of sessions must be positive" << std::endl;
				}
				parsed_flags.sessions = test_int;
				break;
			case '?':
				parsed_flags.invalid = true;
				std::cerr << "Try './snake --help' for more information." << std::endl;
				break;
			default:
				parsed_flags.invalid = true;
		}
	}

	return (parsed_flags);
}