#pragma once

#include <iostream>
#include "Parser.hpp"
#include "BMPParserException.hpp"
#include "BMPViewer.hpp"


int main(int argc, char** argv)
{
	if (argc <2) return 1;

	std::string path{argv[1]};
	BMPParser::BMPParser parser;
	parser.Read(path);

	BMPViewer::BMPViewer viewer;
	viewer.LoadBitMap(parser.GetRawData(),parser.GetXSize(),parser.GetYSize());
	viewer.ShowBitMap();

	int x;
	std::cin >> x;
	return 0;
}