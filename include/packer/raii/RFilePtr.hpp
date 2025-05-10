#ifndef PACKER_RFILEPTR_HPP
#define PACKER_RFILEPTR_HPP

#include "cstdio"
#include "packer/packer.hpp"
PACKER_BEGIN

class RFilePtr{
public:
    RFilePtr();
    RFilePtr(const char *path, const char *mode);
    RFilePtr(const RFilePtr &oth) = delete;
    RFilePtr(RFilePtr &&) noexcept;
    ~RFilePtr();

    FILE* use();

    operator bool();
    RFilePtr& operator=(RFilePtr &rhs) =delete;
    RFilePtr& operator=(RFilePtr &&rhs) noexcept;

private:
    FILE* m_ptr;
};

PACKER_END
#endif