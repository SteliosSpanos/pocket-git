#include <cstring>
#include <string>
#include <cstdio>

#include "commands/init.h"

void PrintUsage(const char *program)
{
	fprintf(stderr, "Usage: %s <command> [<args>]\n\n", program);
	fprintf(stderr, "Commands:\n");
	fprintf(stderr, "  init [path]     Initialize a new repository\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	std::string command = argv[1];

	if (command == "init")
	{
		std::string path;
		if (argc >= 3)
		{
			path = argv[2];
		}
		else
		{
			path = ".";
		}

		return CmdInit(path);
	}

	fprintf(stderr, "Unknown command: %s\n", command.c_str());
	PrintUsage(argv[0]);
	return 1;
}
