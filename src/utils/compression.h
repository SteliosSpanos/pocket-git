#ifndef POCKET_GIT_UTILS_COMPRESSION_H_
#define POCKET_GIT_UTILS_COMPRESSION_H_

#include <string>

std::string ZlibCompress(const std::string &data);

std::string ZlibDecompress(const std::string &data);

#endif