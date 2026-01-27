#include "repository.h"
#include "../utils/file_utils.h"

Repository::Repository(const std::string &path)
    : root_path_(path), git_dir_(path + "/.git") {}

bool Repository::Init()
{
    if (PathExists(git_dir_))
    {
        return false;
    }

    if (!CreateDirectoryStructure())
    {
        return false;
    }

    if (!WriteInitialFiles())
    {
        return false;
    }

    return true;
}

bool Repository::CreateDirectoryStructure()
{
    if (!CreateDirectories(git_dir_))
    {
        return false;
    }

    if (!CreateDirectories(git_dir_ + "/objects"))
    {
        return false;
    }

    if (!CreateDirectories(git_dir_ + "/refs/heads"))
    {
        return false;
    }

    if (!CreateDirectories(git_dir_ + "/refs/tags"))
    {
        return false;
    }

    return true;
}

bool Repository::WriteInitialFiles()
{
    std::string head_content = "ref: refs/head/main\n";
    if (!WriteFile(git_dir_ + "/HEAD", head_content))
    {
        return false;
    }

    std::string config_content =
        "[core]\n"
        "\trepositoryformatversion = 0\n"
        "\tfilemode = true\n"
        "\tbare = false\n";

    if (!WriteFile(git_dir_ + "/config", config_content))
    {
        return false;
    }

    return true;
}

bool Repository::IsValid()
{
    return PathExists(git_dir_) &&
           IsDirectory(git_dir_) &&
           PathExists(git_dir_ + "/HEAD") &&
           PathExists(git_dir_ + "/objects") &&
           PathExists(git_dir_ + "/refs");
}

std::string Repository::GetRoot() const
{
    return root_path_;
}

std::string Repository::GetGitDir() const
{
    return git_dir_;
}

std::string Repository::GetObjectsDir() const
{
    return git_dir_ + "/objects";
}

std::string Repository::GetRefsDir() const
{
    return git_dir_ + "/refs";
}

std::string Repository::GetHeadPath() const
{
    return git_dir_ + "/HEAD";
}