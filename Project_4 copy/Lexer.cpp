#include "AddAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "FactsAutomaton.h"
#include "IDAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Lexer.h"
#include "MLCommentAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "QueriesAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "SLCommentAutomaton.h"
#include "StringAutomaton.h"
#include "UndefinedAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
	for (Automaton* automaton : automata) {
		delete automaton; //error here before declared virtual destructor
	}
	automata.clear();
	for (Token* token : tokens) {
		delete token;
	}
	tokens.clear();
    // TODOne: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
	automata.push_back(new AddAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
	automata.push_back(new CommaAutomaton());
	automata.push_back(new FactsAutomaton());
	automata.push_back(new Left_ParenAutomaton());
	automata.push_back(new MLCommentAutomaton());
	automata.push_back(new MultiplyAutomaton());
	automata.push_back(new PeriodAutomaton());
	automata.push_back(new Q_MarkAutomaton());
	automata.push_back(new QueriesAutomaton());
	automata.push_back(new Right_ParenAutomaton());
	automata.push_back(new RulesAutomaton());
	automata.push_back(new SchemesAutomaton());
	automata.push_back(new SLCommentAutomaton());
	automata.push_back(new StringAutomaton());
	automata.push_back(new UndefinedAutomaton());
	automata.push_back(new IDAutomaton());
    // TODOne: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    // TODOne: convert this pseudo-code with the algorithm into actual C++ code
    lineNumber = 1;
	while (input.size() > 0) {
		maxRead = 0;
		maxAutomaton = automata.at(0);
		bool eof = false;
		while (isspace(input[0])) { //will this work for multiline?
			if (input[0] == '\n') {
				lineNumber++;
			}
			input.erase(input.begin());
			if (input.size() == 0) {
				eof = true;
				break;
			}
		}
		if (!eof) {
			for (size_t i = 0; i < automata.size(); ++i) {
				inputRead = automata.at(i)->Start(input);
				if (inputRead > maxRead) {
					maxRead = inputRead;
					maxAutomaton = automata.at(i);
				}
			}
			if (maxRead > 0) {
				newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
				lineNumber += maxAutomaton->NewLinesRead();
				if (newToken->getTokenType() != TokenType::COMMENT) {
					tokens.push_back(newToken);
				}
			}
			else {
				maxRead = 1;
				newToken = new Token(TokenType::UNDEFINED, input.substr(0,maxRead), lineNumber);
				tokens.push_back(newToken);
			}
			input.erase(0, maxRead);
		}
	}
	tokens.push_back(new Token(TokenType::EOF_TYPE, std::string(""), lineNumber));
}

std::vector<Token*> Lexer::GetTokens() {
	return tokens;
}
