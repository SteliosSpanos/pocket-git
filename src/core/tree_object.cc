#include "tree_object.h"
#include "../utils/string_utils.h"

#include <algorithm>
#include <sstream>

static bool CompareEntries(const TreeEntry &entry_a, const TreeEntry &entry_b)
{
    return entry_a.name < entry_b.name;
}

TreeObject::TreeObject() {}

void TreeObject::AddEntry(const std::string &mode,
                          const std::string &name,
                          const std::string &hash)
{
    entries_.push_back(TreeEntry(mode, name, hash));
}

std::string TreeObject::Serialize() const
{
    std::string content;

    std::vector<TreeEntry> sorted = entries_;
    std::sort(sorted.begin(), sorted.end(), CompareEntries);

    for (size_t i = 0; i < sorted.size(); ++i)
    {
        content += sorted[i].mode;
        content += ' ';
        content += sorted[i].name;
        content += '\0';
        content += HexToBytes(sorted[i].hash);
    }

    std::ostringstream header;
    header << "tree " << content.size();

    std::string result = header.str();
    result += '\0';
    result += content;

    return result;
}

std::string TreeObject::GetType() const
{
    return "tree";
}

const std::vector<TreeEntry> &TreeObject::GetEntries() const
{
    return entries_;
}