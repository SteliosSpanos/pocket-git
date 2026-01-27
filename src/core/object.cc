#include "object.h"
#include "repository.h"
#include "../utils/hash_utils.h"
#include "../utils/compression.h"
#include "../utils/file_utils.h"

std::string Object::ComputeHash() const
{
    return Sha256HashHex(Serialize());
}

std::string Object::Write(const Repository &repo) const
{
    std::string serialized = Serialize();
    std::string hash = Sha256HashHex(serialized);
    std::string compressed = ZlibCompress(serialized);

    if (compressed.empty())
    {
        return "";
    }

    std::string dir = repo.GetObjectsDir() + "/" + hash.substr(0, 2);
    std::string path = dir + "/" + hash.substr(2);

    if (PathExists(path))
    {
        return hash;
    }

    if (!PathExists(dir))
    {
        if (!CreateDirectory(dir))
        {
            return "";
        }
    }

    if (!WriteFile(path, compressed))
    {
        return "";
    }

    return hash;
}