//
// Created by Niels Turley on 9/14/21.
//

#ifndef PROJECT_1_ADDAUTOMATON_H
#define PROJECT_1_ADDAUTOMATON_H

#include "Automaton.h"

class AddAutomaton : public Automaton {
public:
	AddAutomaton() : Automaton(TokenType::ADD) {}

	void S0(const std::string& input);
};


#endif //PROJECT_1_ADDAUTOMATON_H
