#include "hash_object.h"
#include "../core/repository.h"
#include "../core/blob_object.h"
#include "../utils/file_utils.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>

static std::string ReadStdin()
{
    std::ostringstream buffer;
    buffer << std::cin.rdbuf();
    return buffer.str();
}

int CmdHashObject(int argc, char *argv[])
{
    bool write_object = false;
    bool use_stdin = false;
    std::string filepath;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-w") == 0)
        {
            write_object = true;
        }
        else if (strcmp(argv[i], "--stdin") == 0)
        {
            use_stdin = true;
        }
        else if (argv[i][0] != '-')
        {
            filepath = argv[i];
        }
    }

    std::string content;

    if (use_stdin)
    {
        content = ReadStdin();
    }
    else if (!filepath.empty())
    {
        content = ReadFile(filepath);
        if (content.empty() && !PathExists(filepath))
        {
            fprintf(stderr, "fatal: could not open: '%s'\n", filepath.c_str());
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "fatal: no file specified\n");
        return 1;
    }

    BlobObject blob(content);

    if (write_object)
    {
        Repository repo(".");
        if (!repo.IsValid())
        {
            fprintf(stderr, "fatal: not a git repository\n");
            return 1;
        }

        std::string hash = blob.Write(repo);
        if (hash.empty())
        {
            fprintf(stderr, "fatal: failed to write object\n");
            return 1;
        }

        printf("%s\n", hash.c_str());
    }
    else
    {
        printf("%s\n", blob.ComputeHash().c_str());
    }

    return 0;
}