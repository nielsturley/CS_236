//
// Created by Niels Turley on 9/24/21.
//

#include "Predicate.h"

Predicate::Predicate(std::string id, std::vector<Parameter *> parameters) {
	this->id = id;
	this->parameters = parameters;
}

Predicate::~Predicate() {
	for (Parameter* parameter : parameters) {
		delete parameter;
	}
	parameters.clear();
}
