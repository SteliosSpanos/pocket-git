#ifndef POCKET_GIT_UTILS_FILE_UTILS_H_
#define POCKET_GIT_UTILS_FILE_UTILS_H_

#include <string>

bool PathExists(const std::string &path);

bool IsDirectory(const std::string &path);

bool CreateDirectory(const std::string &path);

bool CreateDirectories(const std::string &path);

std::string ReadFile(const std::string &path);

bool WriteFile(const std::string &path, const std::string &content);

#endif