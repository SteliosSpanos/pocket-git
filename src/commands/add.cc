#include "add.h"
#include "../core/repository.h"
#include "../core/blob_object.h"
#include "../core/index.h"
#include "../utils/file_utils.h"

#include <cstdio>

int CmdAdd(int argc, char *argv[])
{
    if (argc < 1)
    {
        fprintf(stderr, "Usage: pocket-git add <file> ...\n");
        return 1;
    }

    Repository repo(".");
    if (!repo.IsValid())
    {
        fprintf(stderr, "fatal: not a git repository\n");
        return 1;
    }

    Index index;
    if (!index.Load(repo))
    {
        fprintf(stderr, "fatal: could not read index\n");
        return 1;
    }

    for (int i = 0; i < argc; ++i)
    {
        std::string filepath = argv[i];

        if (!PathExists(filepath))
        {
            fprintf(stderr, "fatal: path '%s' didnt match any files\n", filepath.c_str());
            return 1;
        }

        std::string content = ReadFile(filepath);
        BlobObject blob(content);

        std::string hash = blob.Write(repo);
        if (hash.empty())
        {
            fprintf(stderr, "fatal: failed to write object for 's'\n", filepath.c_str());
            return 1;
        }

        index.AddEntry("100644", hash, filepath);
    }

    if (!index.Save(repo))
    {
        fprintf(stderr, "fatal: could not write index\n");
        return 1;
    }

    return 0;
}