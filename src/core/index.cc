#include "index.h"
#include "repository.h"
#include "../utils/file_utils.h"

#include <algorithm>
#include <fstream>
#include <sstream>

static bool CompareByPath(const IndexEntry &entry_a, const IndexEntry &entry_b)
{
    return entry_a.path < entry_b.path;
}

bool Index::Load(const Repository &repo)
{
    entries_.clear();

    std::string index_path = repo.GetGitDir() + "/index";

    if (!PathExists(index_path))
    {
        return true;
    }

    std::ifstream file(index_path.c_str());
    if (!file)
    {
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream iss(line);
        std::string mode;
        std::string hash;
        std::string path;

        iss >> mode >> hash >> path;

        if (!mode.empty() && !hash.empty() && !path.empty())
        {
            entries_.push_back(IndexEntry(mode, hash, path));
        }
    }

    return true;
}

bool Index::Save(const Repository &repo) const
{
    std::string index_path = repo.GetGitDir() + "/index";

    std::ostringstream content;

    std::vector<IndexEntry> sorted = entries_;
    std::sort(sorted.begin(), sorted.end(), CompareByPath);

    for (size_t i = 0; i < sorted.size(); ++i)
    {
        content << sorted[i].mode << " "
                << sorted[i].hash << " "
                << sorted[i].path << "\n";
    }

    return WriteFile(index_path, content.str());
}

void Index::AddEntry(const std::string &mode,
                     const std::string &hash,
                     const std::string &path)
{
    for (size_t i = 0; i < entries_.size(); ++i)
    {
        if (entries_[i].path == path)
        {
            entries_[i].mode = mode;
            entries_[i].hash = hash;
            return;
        }
    }

    entries_.push_back(IndexEntry(mode, hash, path));
}

const std::vector<IndexEntry> &Index::GetEntries() const
{
    return entries_;
}

void Index::SortEntries()
{
    std::sort(entries_.begin(), entries_.end(), CompareByPath);
}