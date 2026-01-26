#include "file_utils.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <sstream>

bool PathExists(const std::string &path)
{
    struct stat st;
    return stat(path.c_str(), &st) == 0;
}

bool IsDirectory(const std::string &path)
{
    struct stat st;

    if (stat(path.c_str(), &st) != 0)
    {
        return false;
    }

    return S_ISDIR(st.st_mode);
}

bool CreateDirectory(const std::string &path)
{
    return mkdir(path.c_str(), 0755) == 0;
}

bool CreateDirectories(const std::string &path)
{
    std::string current;

    for (size_t i = 0; i < path.size(); ++i)
    {
        current += path[i];

        if (path[i] == '/' || i == path.size() - 1)
        {
            if (!current.empty() && current != "/")
            {
                if (!PathExists(current))
                {
                    if (!CreateDirectory(current))
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

std::string ReadFile(const std::string &path)
{
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file)
    {
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool WriteFile(const std::string &path, const std::string &content)
{
    std::ofstream file(path.c_str(), std::ios::binary);
    if (!file)
    {
        return false;
    }

    file.write(content.c_str(), content.size());
    return file.good();
}