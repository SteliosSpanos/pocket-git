#ifndef POCKET_GIT_CORE_OBJECT_H_
#define POCKET_GIT_CORE_OBJECT_H_

#include <string>

class Repository;

struct ObjectData
{
    std::string type;
    size_t size;
    std::string content;
    bool valid;

    ObjectData() : size(0), valid(false) {}
};
class Object
{
public:
    virtual ~Object() {}

    virtual std::string Serialize() const = 0;

    virtual std::string GetType() const = 0;

    std::string ComputeHash() const;

    std::string Write(const Repository &repo) const;

    static ObjectData Read(const Repository &repo, const std::string &hash);
};

#endif