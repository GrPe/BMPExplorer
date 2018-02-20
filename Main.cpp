#include <iostream>
#include "Parser.hpp"
#include "BMPParserException.hpp"


int main(int argc, char** argv)
{
	if (argc <2) return 1;

	std::string path{argv[1]};
	BMPParser::BMPParser parser;
	parser.Read(path);

	return 0;
}