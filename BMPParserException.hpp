#pragma once
#include <exception>

namespace BMPParser
{
	class InvalidFileHeaderException : std::exception
	{
		const char* what() const override
		{
			return "Invalid BitMapFileHeader format\n";
		}
	};

	class InvalidInfoHeaderException : std::exception
	{
		const char* what() const override
		{
			return "Invalid BitMapInfoHeader format\n";
		}
	};

	class InvalidFilePathException : std::exception
	{
		const char* what() const override
		{
			return "Invalid file path\n";
		}
	};
}