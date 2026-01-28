#include <cstring>
#include <string>
#include <cstdio>

#include "commands/init.h"
#include "commands/hash_object.h"
#include "commands/cat_file.h"

void PrintUsage(const char *program)
{
	fprintf(stderr, "Usage: %s <command> [<args>]\n\n", program);
	fprintf(stderr, "Commands:\n");
	fprintf(stderr, "   init [path]                        Initialize a new repository\n");
	fprintf(stderr, "   hash-object [-w] [--stdin] <file>  Compute object hash\n");
	fprintf(stderr, "   cat-file (-p|-t|-s|-e) <hash>    Show object info\n");
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
	if (command == "hash-object")
	{
		return CmdHashObject(argc - 2, argv + 2);
	}
	if (command == "cat-file")
	{
		return CmdCatFile(argc - 2, argv + 2);
	}

	fprintf(stderr, "Unknown command: %s\n", command.c_str());
	PrintUsage(argv[0]);
	return 1;
}
