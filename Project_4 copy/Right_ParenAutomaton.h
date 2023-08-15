//
// Created by Niels Turley on 9/14/21.
//

#ifndef PROJECT_1_RIGHT_PARENAUTOMATON_H
#define PROJECT_1_RIGHT_PARENAUTOMATON_H

#include "Automaton.h"

class Right_ParenAutomaton : public Automaton {
public:
	Right_ParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}

	void S0(const std::string& input);
};


#endif //PROJECT_1_RIGHT_PARENAUTOMATON_H
