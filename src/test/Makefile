TestPacker:
	g++ -g -O2 -o TestPacker -I ../../include TestPacker.cpp ../core/VImage.cpp ../core/VImageReader.cpp ../core/VImageWriter.cpp ../core/Vlayouter.cpp ../core/VPacker.cpp ../core/VUnpacker.cpp ../core/VProfileReader.cpp ../core/VProfileWriter.cpp ../core/VScanner.cpp ../data/data.cpp ../impl/DefaultProfileReader.cpp ../impl/DefaultProfileWriter.cpp ../impl/DefaultScanner.cpp ../impl/Image.cpp ../impl/ImageReader.cpp ../impl/ImageWriter.cpp ../impl/Packer.cpp ../impl/Unpacker.cpp ../impl/ScaledLayouter.cpp ../raii/CharBuffer.cpp ../raii/RgbaBuffer.cpp ../raii/FilePtr.cpp ../util/Bitmap.cpp

TestProfile:
	g++ -O2 -o TestProfile -I ../../include TestProfile.cpp ../impl/DefaultProfileReader.cpp ../impl/DefaultProfileWriter.cpp ../raii/CharBuffer.cpp ../raii/FilePtr.cpp ../core/VProfileReader.cpp ../core/VProfileWriter.cpp ../data/data.cpp
TestLayouter:
	g++ -O2 -o TestLayouter -I ../../include TestLayouter.cpp ../impl/ScaledLayouter.cpp ../util/Bitmap.cpp ../data/data.cpp  ../core/Vlayouter.cpp
TestImage:
	g++ -O2 -o TestImage -I ../../include TestImage.cpp ../impl/Image.cpp ../impl/ImageReader.cpp ../impl/ImageWriter.cpp ../core/VImage.cpp ../core/VImageReader.cpp ../core/VImageWriter.cpp ../data/data.cpp
TestBitmap:
	g++ -O2 -o TestBitmap -I ../../include TestBitmap.cpp ../util/Bitmap.cpp