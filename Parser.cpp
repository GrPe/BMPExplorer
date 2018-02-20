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
	data = new uint8_t[sizeOfData];
	bmpFile.read(reinterpret_cast<char*>(data), sizeof(uint8_t)*sizeOfData);
	if (data == nullptr)
	{
		bmpFile.clear();
		throw InvalidDataFormatException();
	}
	if (bmpFile.fail())
	{
		if (data != nullptr) delete[] data;
		bmpFile.clear();
		throw InvalidDataFormatException();
	}
}

BMPParser::BMPParser::~BMPParser()
{
	if (data != nullptr) delete[] data;
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