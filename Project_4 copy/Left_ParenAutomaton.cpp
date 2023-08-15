//
// Created by Niels Turley on 9/14/21.
//

#include "Left_ParenAutomaton.h"

void Left_ParenAutomaton::S0(const std::string &input) {
	if (input[index] == '(') {
		inputRead = 1;
	}
	else {
		Serr();
	}
}
