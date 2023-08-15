//
// Created by Niels Turley on 9/14/21.
//

#ifndef PROJECT_1_STRINGAUTOMATON_H
#define PROJECT_1_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {
private:
	void S1(const std::string &input);
	void S2(const std::string &input);


public:
	StringAutomaton() : Automaton(TokenType::STRING) {}

	void S0(const std::string& input);


};


#endif //PROJECT_1_STRINGAUTOMATON_H
