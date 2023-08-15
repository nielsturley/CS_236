#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
	int lineNumber = 0;
	int maxRead = 0;
	int inputRead = 0;
	Automaton* maxAutomaton;
	Token* newToken;

    void CreateAutomata();

    // TODOne: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);

	friend std::ostream& operator<< (std::ostream& os, const Lexer& lexer) {
		os << lexer.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		for (size_t i = 0; i < tokens.size(); ++i) {
			out << *tokens.at(i) << std::endl;
		}
		out << "Total Tokens = " << tokens.size();
		return out.str();
	}

    
    // TODO: add other public methods here

	std::vector<Token *> GetTokens();
};

#endif // LEXER_H

