#ifndef PARSER_HPP
# define PARSER_HPP
# include <string>


struct flags
{
	bool		invalid = false;
	bool		help = false;
	bool		visual = false;
	bool		save  = false;
	bool		load  = false;
	bool		dontlearn = false;
	bool		stepmode = false;
	std::string	savefile = "";
	std::string	loadfile = "";
	int			size  = 10;
	int			sessions = 100;
};

flags parse_flags(int argc, char **argv);

#endif
