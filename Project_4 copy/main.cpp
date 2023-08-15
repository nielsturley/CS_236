#include "Parser.h"
#include "Lexer.h"
#include "Interpreter.h"
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>


int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "usage: " << argv[0] << " input_file" << std::endl;
		return 1;
	}

	// open file
	std::string fileName = argv[1];
	std::ifstream input(fileName);
	if (!input.is_open()) {
		std::cout << "File " << fileName << " could not be found or opened." << std::endl;
		return 1;
	}

	std::stringstream buffer;
	buffer << input.rdbuf();

	std::string contents(buffer.str());

    Lexer* lexer = new Lexer();
	lexer->Run(contents);


	Parser* parser = new Parser();
	parser->parse(lexer->GetTokens());

	Interpreter* interpreter = new Interpreter(parser->getSchemes(), parser->getFacts(), parser->getQueries(), parser->getRules());
	interpreter->run();

    delete lexer;

    return 0;
}