//
// Created by Niels Turley on 9/14/21.
//

#include "Right_ParenAutomaton.h"

void Right_ParenAutomaton::S0(const std::string& input) {
	if (input[index] == ')') {
		inputRead = 1;
	}
	else {
		Serr();
	}
}