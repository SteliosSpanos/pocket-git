#ifndef POCKET_GIT_CORE_TREE_OBJECT_H_
#define POCKET_GIT_CORE_TREE_OBJECT_H_

#include "object.h"
#include <vector>
#include <string>

struct TreeEntry
{
    std::string mode;
    std::string name;
    std::string hash;

    TreeEntry(const std::string &m, const std::string &n, const std::string &h)
        : mode(m), name(n), hash(h) {}
};

class TreeObject : public Object
{
private:
    std::vector<TreeEntry> entries_;

public:
    TreeObject();

    void AddEntry(const std::string &mode,
                  const std::string &name,
                  const std::string &hash);

    std::string Serialize() const;
    std::string GetType() const;

    const std::vector<TreeEntry> &GetEntries() const;
};

#endif