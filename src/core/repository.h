#ifndef POCKET_GIT_CORE_REPOSITORY_H_
#define POCKET_GIT_CORE_REPOSITORY_H_

#include <string>

class Repository
{
private:
    std::string root_path_;
    std::string git_dir_;

    bool CreateDirectoryStructure();
    bool WriteInitialFiles();

public:
    explicit Repository(const std::string &path);

    bool Init();

    bool IsValid();

    std::string GetRoot() const;
    std::string GetGitDir() const;
    std::string GetObjectsDir() const;
    std::string GetRefsDir() const;
    std::string GetHeadPath() const;
};

#endif