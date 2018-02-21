#include "Parser.hpp"
#include <iostream>

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
	std::unique_ptr<char[]> buffer(new char[sizeOfData]);
	bmpFile.read(buffer.get(), sizeOfData);
	std::memcpy(data, buffer.get(), sizeOfData);
	//for (int i = 0; i < sizeOfData/3; i ++)
	//{
		//bmpFile.read(buffer.get(), 3);
		//std::memcpy(data + i * 3, buffer.get(), 3);
	//}
	//std::unique_ptr<unsigned char[]> buffer(new unsigned char[sizeOfData]);
	//bmpFile.read(reinterpret_cast<char*>(buffer.get()), sizeOfData);
	//std::memcpy(data, buffer.get(), sizeOfData);
	//std::cerr << std::hex << (int)data[0x222c35-54] << std::endl;
	//std::cerr << bmpFile.tellg() << std::endl;
}

BMPParser::BMPParser::~BMPParser()
{
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

uint8_t * BMPParser::BMPParser::GetRawData()
{
	return data;
}

int BMPParser::BMPParser::GetXSize() const noexcept
{
	if (isDataRead) 
		return bitMapInfoHeader.biWidth;
	else return 0;
}

int BMPParser::BMPParser::GetYSize() const noexcept
{
	if (isDataRead)
		return bitMapInfoHeader.biHeight;
	else return 0;
}
