#ifndef POCKET_GIT_CORE_OBJECT_H_
#define POCKET_GIT_CORE_OBJECT_H_

#include <string>

class Repository;

class Object
{
public:
    virtual ~Object() {}

    virtual std::string Serialize() const = 0;

    virtual std::string GetType() const = 0;

    std::string ComputeHash() const;

    std::string Write(const Repository &repo) const;
};

#endif