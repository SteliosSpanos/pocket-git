#include "blob_object.h"
#include "../utils/file_utils.h"

#include <sstream>

BlobObject::BlobObject(const std::string &content)
    : content_(content) {}

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

BlobObject *BlobObject::FromFile(const std::string &path)
{
    std::string content = ReadFile(path);
    if (content.empty() && !PathExists(path))
    {
        return NULL;
    }

    return new BlobObject(content);
}