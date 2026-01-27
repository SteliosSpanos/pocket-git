#include "init.h"
#include "../core/repository.h"

#include <cstdio>

int CmdInit(const std::string &path)
{
    Repository repo(path);

    if (repo.IsValid())
    {
        fprintf(stderr, "Reinitialized existing Git repository in %s/.git/\n", path.c_str());
        return 0;
    }

    if (!repo.Init())
    {
        fprintf(stderr, "Failed to initialize repository\n");
        return 1;
    }

    printf("Initialized empty Git repository in %s/.git/\n", path.c_str());
    return 0;
}