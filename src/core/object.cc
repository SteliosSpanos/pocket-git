#include "object.h"
#include "repository.h"
#include "../utils/hash_utils.h"
#include "../utils/compression.h"
#include "../utils/file_utils.h"

#include <sstream>

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

ObjectData Object::Read(const Repository &repo, const std::string &hash)
{
    ObjectData data;

    std::string path = repo.GetObjectsDir() + "/" + hash.substr(0, 2) + "/" + hash.substr(2);
    if (!PathExists(path))
    {
        return data;
    }

    std::string compressed = ReadFile(path);
    if (compressed.empty())
    {
        return data;
    }

    std::string decompressed = ZlibDecompress(compressed);
    if (decompressed.empty())
    {
        return data;
    }

    size_t null_pos = decompressed.find('\0');
    if (null_pos == std::string::npos)
    {
        return data;
    }

    std::string header = decompressed.substr(0, null_pos);
    std::istringstream iss(header);

    iss >> data.type >> data.size;

    data.content = decompressed.substr(null_pos + 1);

    if (data.content.size() != data.size)
    {
        return data;
    }

    data.valid = true;
    return data;
}