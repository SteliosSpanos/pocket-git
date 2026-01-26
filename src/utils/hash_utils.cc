#include "hash_utils.h"
#include "string_utils.h"

#include <openssl/sha.h>

std::string Sha256Hash(const std::string &data)
{
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA256(
        reinterpret_cast<const unsigned char *>(data.c_str()),
        data.size(),
        hash);

    return std::string(reinterpret_cast<char *>(hash), SHA_DIGEST_LENGTH);
}

std::string Sha256HashHex(const std::string &data)
{
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA256(
        reinterpret_cast<const unsigned char *>(data.c_str()),
        data.size(),
        hash);

    return BytesToHex(hash, SHA_DIGEST_LENGTH);
}