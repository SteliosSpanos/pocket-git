#ifndef POCKET_GIT_CORE_BLOB_OBJECT_H_
#define POCKET_GIT_CORE_BLOB_OBJECT_H_

#include "object.h"
#include <string>

class BlobObject : public Object
{
private:
    std::string content_;
    bool valid_;

public:
    BlobObject();
    explicit BlobObject(const std::string &content);

    std::string Serialize() const;
    std::string GetType() const;
    std::string GetContent() const;
    size_t GetSize() const;
    bool isValid() const;

    bool LoadFromFile(const std::string &path);
};

#endif