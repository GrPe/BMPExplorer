#include "Parser.hpp"

#define SHOWVAR(a) std::cerr<<(a)<<'\n';

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
}

void BMPParser::BMPParser::Read(std::string filePath)
{
	bmpFile.open(filePath, std::ios::in | std::ios::binary);
	if (!bmpFile)
	{
		SHOWVAR("PROBLEM WITH OPEN FILE");
		bmpFile.clear();
		throw InvalidFilePathException();
	}
	SHOWVAR("OPEN FILE");

	try
	{
		ReadFileHeader();
		ReadInfoHeader();
		ReadData();
	}
	catch (std::exception& exp)
	{
		SHOWVAR("EXCEPTION IN READ()");
		throw exp;
	}
	isDataRead = true;
}

#undef SHOWVAR