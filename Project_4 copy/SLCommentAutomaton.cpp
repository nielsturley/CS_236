//
// Created by Niels Turley on 9/15/21.
//

#include "SLCommentAutomaton.h"

void SLCommentAutomaton::S0(const std::string &input) {
	if (input[index] == '#') {
		inputRead++;
		index++;
		S1(input);
	}
	else {
		Serr();
	}
}

void SLCommentAutomaton::S1(const std::string& input) {
	if (input[index] == '|') {
		inputRead++;
		index++;
		S2(input);
	}
	else if (input[index] != '\n') {
		inputRead++;
		index++;
		S1(input);
	}
}

void SLCommentAutomaton::S2(const std::string &input) {
	if (input[index] == '|') {
		inputRead++;
		index++;
		S3(input);
	}
	else if (input[index] != '\n') {
		inputRead++;
		index++;
		S1(input);
	}

}

void SLCommentAutomaton::S3(const std::string &input) {
	if (input[index] == '#') {
		Serr();
	}
	else if (input[index] != '\n') {
		inputRead++;
		index++;
		S1(input);
	}
}
