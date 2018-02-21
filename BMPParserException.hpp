#pragma once
#include <exception>

namespace BMPParser
{
	class InvalidFileHeaderException : std::exception
	{
		const char* what() const override
		{
			return "Invalid BitMapFileHeader Format\n";
		}
	};

	class InvalidInfoHeaderException : std::exception
	{
		const char* what() const override
		{
			return "Invalid BitMapInfoHeader Format\n";
		}
	};

	class InvalidFilePathException : std::exception
	{
		const char* what() const override
		{
			return "Invalid File Path\n";
		}
	};

	class InvalidDataFormatException : std::exception
	{
		const char* what() const override
		{
			return "Invalid Data Format\n";
		}
	};

	class SurfaceException : std::exception
	{
		const char* what() const override
		{
			return "Failed to create an RGB surface\n";
		}
	};
}