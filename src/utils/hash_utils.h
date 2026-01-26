#ifndef POCKET_GIT_UTILS_HASH_UTILS_H_
#define POCKET_GIT_UTILS_HASH_UTILS_H_

#include <string>

std::string Sha256Hash(const std::string &data);

std::string Sha256HashHex(const std::string &data);

#endif