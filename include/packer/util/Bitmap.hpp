#ifndef PACKER_BITMAP_HPP
#define PACKER_BITMAP_HPP

#include <cstdint>
namespace packer{


class Bitmap{
public:
    Bitmap(int size=16);
    Bitmap(const Bitmap &oth) =delete;
    ~Bitmap();
    Bitmap& operator=(const Bitmap &rhs) =delete;

    void set(int pos);
    void unset(int pos);
    bool test(int pos);
    void expand(int value);
    int size();
    void clear();

private:
    int m_size;
    int m_realSize;
    uint8_t *m_ptr;
};


}
#endif