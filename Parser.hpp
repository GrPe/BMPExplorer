//Works only with 24bit RGB bitmap

#pragma once

#include <SDL.h>

#include "BMPParserException.hpp"

#include <cstdint>
#include <fstream>
#include <string>
#include <cmath>
#include <memory>

namespace BMPParser
{
	using WORD = uint16_t;
	using DWORD = uint32_t;
	using LONG = int32_t;

	struct  BITMAPFILEHEADER
	{
		WORD bfType;
		DWORD bfSize;
		WORD bfReserved1;
		WORD bfReserved2;
		DWORD bfOffBits;
	};

	struct  BITMAPINFOHEADER
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
	};

	class BMPParser
	{
	private:

		//handles:
		std::fstream bmpFile;
		bool isDataRead{ false };
		unsigned int sizeOfData{};
		uint8_t* data{ nullptr };
		SDL_Surface* surface;

		//BitMap Headers:
		BITMAPFILEHEADER bitMapFileHeader;
		BITMAPINFOHEADER bitMapInfoHeader;

		void ReadFileHeader();
		void ReadInfoHeader();
		void ReadData();

	public:
		BMPParser() = default;
		~BMPParser();
		BMPParser(BMPParser&) = delete;
		BMPParser(BMPParser&&) = delete;

		void Read(std::string filePath);
		SDL_Surface* GetSurface();
	};
}