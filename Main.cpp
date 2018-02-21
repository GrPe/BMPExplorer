#pragma once

#include <iostream>
#include "Parser.hpp"
#include "BMPParserException.hpp"
#include "BMPViewer.hpp"

#undef main

int main(int argc, char** argv)
{
	if (argc <2) return 1;
	int x;
	std::cin >> x;
	{
		std::string path{ argv[1] };
		BMPParser::BMPParser parser;
		parser.Read(path);

		BMPViewer::BMPViewer viewer;
		viewer.ShowBitMap(parser.GetSurface());

		viewer.ShowBitMap(parser.GetSurface());
	}

	std::cin >> x;
	return 0;
}