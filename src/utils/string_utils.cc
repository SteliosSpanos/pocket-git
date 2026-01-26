#include "string_utils.h"

#include <cstdio>

std::string HexToBytes(const std::string &hex)
{
    std::string result;
    result.reserve(hex.size() / 2);

    for (size_t i = 0; i < hex.size(); i += 2)
    {
        unsigned int byte;
        sscanf(hex.c_str() + i, "%02x", &byte);
        result += static_cast<char>(byte);
    }

    return result;
}

std::string BytesToHex(const unsigned char *data, size_t len)
{
    std::string result;
    result.reserve(len * 2);

    for (size_t i = 0; i < len; ++i)
    {
        char buf[3];
        sprintf(buf, "%02x", data[i]);
        result += buf;
    }

    return result;
}