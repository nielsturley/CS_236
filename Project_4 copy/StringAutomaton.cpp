//
// Created by Niels Turley on 9/14/21.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string &input) {
	if (input[index] == '\'') {
		inputRead++;
		index++;
		S1(input);
	}
	else {
		Serr();
	}
}

void StringAutomaton::S1(const std::string &input) {
	if (input[index] == '\'') {
		inputRead++;
		index++;
		S2(input);
	}
	else if (index == input.size()) {
		Serr();
	}
	else {
		if (input[index] == '\n') {
			newLines++;
		}
		inputRead++;
		index++;
		S1(input);
	}
}

void StringAutomaton::S2(const std::string &input) {
	if (input[index] == '\'') {
		inputRead++;
		index++;
		S1(input);
	}
}
