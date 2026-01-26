#ifndef POCKET_GIT_UTILS_STRINGS_H_
#define POCKET_GIT_UTILS_STRINGS_H_

#include <string>

std::string BytesToHex(const unsigned char *data, size_t len);

std::string HexToBytes(const std::string &hex);

#endif