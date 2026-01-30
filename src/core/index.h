#ifndef POCKET_GIT_CORE_INDEX_H_
#define POCKET_GIT_CORE_INDEX_H_

#include <string>
#include <vector>

class Repository;

struct IndexEntry
{
    std::string mode;
    std::string hash;
    std::string path;

    IndexEntry(const std::string &m, const std::string &h, const std::string &p)
        : mode(m), hash(h), path(p) {}
};

class Index
{
private:
    std::vector<IndexEntry> entries_;

    void SortEntries();

public:
    bool Load(const Repository &repo);

    bool Save(const Repository &repo) const;

    void AddEntry(const std::string &mode,
                  const std::string &hash,
                  const std::string &path);

    const std::vector<IndexEntry> &GetEntries() const;
};

#endif