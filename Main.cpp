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
	char* rawData = parser.GetRawData();
	viewer.LoadBitMap(rawData);
	viewer.ShowBitMap();

	return 0;
}