//
// Created by Niels Turley on 9/14/21.
//

#ifndef PROJECT_1_LEFT_PARENAUTOMATON_H
#define PROJECT_1_LEFT_PARENAUTOMATON_H

#include "Automaton.h"

class Left_ParenAutomaton : public Automaton {
public:
	Left_ParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}

	void S0(const std::string& input);
};


#endif //PROJECT_1_LEFT_PARENAUTOMATON_H
