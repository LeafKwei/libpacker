#ifndef PACKER_GAPIMAGE_HPP
#define PACKER_GAPIMAGE_HPP

#include "packer/packer.hpp"
#include "packer/core/VImage.hpp"
PACKER_BEGIN

class GapImage : public VImage{
public:
    GapImage(int width, int height);
    ~GapImage() override;
    int width() const override;
    int height() const override;
    RGBA access(int x, int y) const override;
    void place(int x, int y, const RGBA &rgb) override;;
    void placeRect(int x, int y, const VImage &src, const Rect &rect) override;
    const RGBA* accessAll() override;

protected:
    GapImage();
    void custom();
    virtual void readRawImage();
    virtual int customedWidth() const;
    virtual int customedHeight() const;
    virtual void fillData(int x, int y, RGBA &rgb);

private:
    int m_width;
    int m_height;
    RGBA *m_data;

    void createBuffer(int width, int height);
};

PACKER_END
#endif