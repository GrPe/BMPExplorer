#pragma once

#include "BMPParserException.hpp"

#include <cstdint>
#include <fstream>
#include <string>

//debug:
#include <iostream>

namespace BMPParser
{
	using WORD = uint16_t;
	using DWORD = uint32_t;
	using LONG = int32_t;

	class BMPParser
	{
	private:

		//handles:
		std::fstream bmpFile;
		bool isDataRead{false};
		uint8_t* data{nullptr};

		//BitMap Headers:
		BITMAPFILEHEADER bitMapFileHeader;
		BITMAPINFOHEADER bitMapInfoHeader;

		void ReadFileHeader();
		void ReadInfoHeader();
		void ReadData();

	public:
		BMPParser() = default;
		~BMPParser() = default;
		BMPParser(BMPParser&) = default;
		BMPParser(BMPParser&&) = delete;

		void Read(std::string filePath);
	};

	class BITMAPFILEHEADER
	{
		WORD bfType;
		DWORD bfSize;
		WORD bfReserved1;
		WORD bfReserved2;
		DWORD bfOffBits;
		friend class BMPParser;
	};

	class BITMAPINFOHEADER
	{
		DWORD biSize;
		LONG biWidth;
		LONG biHeight;
		WORD biPlanes;
		WORD biBitCount;
		DWORD biCompression;
		DWORD biSizeImage;
		LONG biXPelsPerMeter;
		LONG biYPelsPerMeter;
		DWORD biClrUsed;
		DWORD biClrImportant;
		friend class BMPParser;
	};
}