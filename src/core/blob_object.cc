#include "blob_object.h"
#include "../utils/file_utils.h"

#include <sstream>

BlobObject::BlobObject()
    : content_(), valid_(false) {}

BlobObject::BlobObject(const std::string &content)
    : content_(content), valid_(true) {}

bool BlobObject::LoadFromFile(const std::string &path)
{
    if (!PathExists(path))
    {
        valid_ = false;
        return false;
    }

    content_ = ReadFile(path);
    valid_ = true;
    return true;
}

std::string BlobObject::Serialize() const
{
    std::ostringstream header;
    header << "blob " << content_.size();

    std::string result = header.str();
    result += '\0';
    result += content_;

    return result;
}

std::string BlobObject::GetType() const
{
    return "blob";
}

std::string BlobObject::GetContent() const
{
    return content_;
}

size_t BlobObject::GetSize() const
{
    return content_.size();
}