#include "Parser.hpp"

void BMPParser::BMPParser::ReadFileHeader()
{
	char buffer[4]{};

	bmpFile.read(buffer, sizeof(WORD));
	if (buffer[0] != 'B' || buffer[1] != 'M')
		throw InvalidFileHeaderException();
	std::memcpy(&bitMapFileHeader.bfType, buffer, sizeof(WORD));

	bmpFile.read(buffer, sizeof(DWORD));
	std::memcpy(&bitMapFileHeader.bfSize, buffer, sizeof(DWORD));
	
	bmpFile.read(buffer, sizeof(WORD));
	std::memcpy(&bitMapFileHeader.bfReserved1, buffer, sizeof(WORD));
	if (bitMapFileHeader.bfReserved1 != 0) throw InvalidFileHeaderException();

	bmpFile.read(buffer, sizeof(WORD));
	std::memcpy(&bitMapFileHeader.bfReserved2, buffer, sizeof(WORD));
	if (bitMapFileHeader.bfReserved2 != 0) throw InvalidFileHeaderException();

	bmpFile.read(buffer, sizeof(DWORD));
	std::memcpy(&bitMapFileHeader.bfOffBits, buffer, sizeof(DWORD));
}

void BMPParser::BMPParser::ReadInfoHeader()
{
	char buffer[4]{};

	bmpFile.read(buffer, sizeof(DWORD));
	std::memcpy(&bitMapInfoHeader.biSize, buffer, sizeof(DWORD));

	bmpFile.read(buffer, sizeof(LONG));
	std::memcpy(&bitMapInfoHeader.biWidth, buffer, sizeof(LONG));

	bmpFile.read(buffer, sizeof(LONG));
	std::memcpy(&bitMapInfoHeader.biHeight, buffer, sizeof(LONG));

	bmpFile.read(buffer, sizeof(WORD));
	std::memcpy(&bitMapInfoHeader.biPlanes, buffer, sizeof(WORD));
	if (bitMapInfoHeader.biPlanes != 1) throw InvalidInfoHeaderException();

	bmpFile.read(buffer, sizeof(WORD));
	std::memcpy(&bitMapInfoHeader.biBitCount, buffer, sizeof(WORD));

	bmpFile.read(buffer, sizeof(DWORD));
	std::memcpy(&bitMapInfoHeader.biCompression,buffer, sizeof(DWORD));

	bmpFile.read(buffer, sizeof(DWORD));
	std::memcpy(&bitMapInfoHeader.biSizeImage, buffer, sizeof(DWORD));

	bmpFile.read(buffer, sizeof(LONG));
	std::memcpy(&bitMapInfoHeader.biXPelsPerMeter, buffer, sizeof(LONG));

	bmpFile.read(buffer, sizeof(LONG));
	std::memcpy(&bitMapInfoHeader.biYPelsPerMeter, buffer, sizeof(LONG));

	bmpFile.read(buffer, sizeof(DWORD));
	std::memcpy(&bitMapInfoHeader.biClrUsed, buffer, sizeof(DWORD));

	bmpFile.read(buffer,sizeof(DWORD));
	std::memcpy(&bitMapInfoHeader.biClrImportant, buffer, sizeof(DWORD));
}

void BMPParser::BMPParser::ReadData()
{
	sizeOfData = abs(bitMapInfoHeader.biWidth*bitMapInfoHeader.biHeight*(bitMapInfoHeader.biBitCount / 8));
	surface = SDL_CreateRGBSurface(0, bitMapInfoHeader.biWidth, bitMapInfoHeader.biHeight, bitMapInfoHeader.biBitCount,
		0xff0000, 0x00ff00, 0x0000ff, 0);
	if (surface == NULL) throw SurfaceException();

	if (static_cast<int>(bmpFile.tellg()) != bitMapFileHeader.bfOffBits) 
		bmpFile.seekg(bitMapFileHeader.bfOffBits, SEEK_SET);

	uint32_t y = 0;
	int32_t dy = 1;
	if (bitMapInfoHeader.biHeight < 0)
	{
		y = 0;
		dy = 1;
	}
	else
	{
		y = bitMapInfoHeader.biHeight - 1;
		dy = -1;
	}

	auto buffer = new char[sizeOfData];

	while (y >= 0 && y < bitMapInfoHeader.biHeight)
	{
		bmpFile.read(&buffer[y*surface->pitch],bitMapInfoHeader.biWidth*3);
		y += dy;
	}

	std::memcpy(surface->pixels, buffer, sizeOfData);
	delete[] buffer;
}

BMPParser::BMPParser::~BMPParser()
{
	if (surface != NULL)
	{
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	if (data != nullptr) delete[] data;
	if (bmpFile.is_open()) bmpFile.close();
}

void BMPParser::BMPParser::Read(std::string filePath)
{
	bmpFile.open(filePath, std::ios::in | std::ios::binary);
	if (!bmpFile)
	{
		bmpFile.clear();
		throw InvalidFilePathException();
	}

	try
	{
		ReadFileHeader();
		ReadInfoHeader();
		ReadData();
	}
	catch (std::exception& exp)
	{
		bmpFile.close();
		isDataRead = false;
		throw exp;
	}
	isDataRead = true;

	bmpFile.close();
}

SDL_Surface * BMPParser::BMPParser::GetSurface()
{
	return surface;
}