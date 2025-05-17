set(INCLUDE_DIR ../include)
set(SOURCE_LIST 
    core/VImage.cpp
    core/VImageReader.cpp
    core/VImageWriter.cpp
    core/VLayouter.cpp
    core/VPacker.cpp
    core/VProfileReader.cpp
    core/VProfileWriter.cpp
    core/VScanner.cpp
    core/VUnpacker.cpp
    data/data.cpp
    impl/DefaultProfileReader.cpp
    impl/DefaultProfileWriter.cpp
    impl/DefaultScanner.cpp
    impl/Image.cpp
    impl/ImageReader.cpp
    impl/ImageWriter.cpp
    impl/Packer.cpp
    impl/ScaledLayouter.cpp
    impl/Unpacker.cpp
    raii/CharBuffer.cpp
    raii/FilePtr.cpp
    util/Bitmap.cpp
)

include_directories(${INCLUDE_DIR})

add_library(packer
    ${SOURCE_LIST}
)