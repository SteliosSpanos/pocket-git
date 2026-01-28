#include "cat_file.h"
#include "../core/repository.h"
#include "../core/object.h"

#include <cstdio>
#include <cstring>

int CmdCatFile(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: pocket-git cat-file (-p|-t|-s|e) <hash>\n");
        return 1;
    }

    std::string flag;
    std::string hash;

    for (int i = 0; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            flag = argv[i];
        }
        else
        {
            hash = argv[i];
        }
    }

    if (hash.empty())
    {
        fprintf(stderr, "fatal: no object specified\n");
        return 1;
    }

    Repository repo(".");
    if (!repo.IsValid())
    {
        fprintf(stderr, "fatal: not a git repository\n");
        return 1;
    }

    ObjectData obj = Object::Read(repo, hash);

    if (flag == "-e")
    {
        return obj.valid ? 0 : 1;
    }

    if (!obj.valid)
    {
        fprintf(stderr, "fatal: not a valid object name %s\n", hash.c_str());
        return 1;
    }

    if (flag == "-t")
    {
        printf("%s\n", obj.type.c_str());
    }
    else if (flag == "-s")
    {
        printf("%zu\n", obj.size);
    }
    else if (flag == "-p" || flag.empty())
    {
        fwrite(obj.content.c_str(), 1, obj.content.size(), stdout);
    }
    else
    {
        fprintf(stderr, "fatal: unknown flag %s\n", flag.c_str());
        return 1;
    }

    return 0;
}