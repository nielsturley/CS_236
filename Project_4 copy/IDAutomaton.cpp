//
// Created by Niels Turley on 9/15/21.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string &input) {
	if (std::isalpha(input[index])) {
		inputRead++;
		index++;
		S1(input);
	}
}

void IDAutomaton::S1(const std::string &input) {
	if (std::isalnum(input[index])) {
		inputRead++;
		index++;
		S1(input);
	}
}
