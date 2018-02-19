#pragma once
#include <cstdint>

namespace BMPParser
{
	using WORD = uint8_t;
	using DWORD = uint16_t;

	class BMPParser
	{
	private:
		BITMAPFILEHEADER bitMapFileHeader;

		


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
}