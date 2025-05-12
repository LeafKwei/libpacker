#ifndef PACKER_FILEPTR_HPP
#define PACKER_FILEPTR_HPP

#include "cstdio"
#include "packer/packer.hpp"
PACKER_BEGIN

class FilePtr{
public:
    FilePtr();
    FilePtr(const char *path, const char *mode);
    FilePtr(const FilePtr &oth) = delete;
    FilePtr(FilePtr &&) noexcept;
    ~FilePtr();

    FILE* use();

    operator bool();
    FilePtr& operator=(FilePtr &rhs) =delete;
    FilePtr& operator=(FilePtr &&rhs) noexcept;

private:
    FILE* m_ptr;
};

PACKER_END
#endif