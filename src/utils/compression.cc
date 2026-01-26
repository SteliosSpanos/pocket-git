#include "compression.h"

#include <zlib.h>
#include <vector>

std::string ZlibCompress(const std::string &data)
{
    uLongf compressed_size = compressBound(data.size());
    std::vector<unsigned char> buffer(compressed_size);

    int result = compress(
        &buffer[0],
        &compressed_size,
        reinterpret_cast<const unsigned char *>(data.c_str()),
        data.size());

    if (result != Z_OK)
    {
        return "";
    }

    return std::string(reinterpret_cast<char *>(&buffer[0]), compressed_size);
}

std::string ZlibDecompress(const std::string &data)
{
    std::vector<unsigned char> buffer(data.size() * 4);
    uLongf decompressed_size = buffer.size();

    int result = uncompress(
        &buffer[0],
        &decompressed_size,
        reinterpret_cast<const unsigned char *>(data.c_str()),
        data.size());

    while (result == Z_BUF_ERROR)
    {
        buffer.resize(buffer.size() * 2);
        decompressed_size = buffer.size();

        result = uncompress(
            &buffer[0],
            &decompressed_size,
            reinterpret_cast<const unsigned char *>(data.c_str()),
            data.size());
    }

    if (result != Z_OK)
    {
        return "";
    }

    return std::string(reinterpret_cast<char *>(&buffer[0]), decompressed_size);
}