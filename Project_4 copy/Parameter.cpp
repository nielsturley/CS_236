//
// Created by Niels Turley on 9/24/21.
//

#include "Parameter.h"

Parameter::Parameter(std::string id, TokenType type) {
	this->id = id;
	this->type = type;
	if (type != TokenType::ID) {
		isConstant = true;
	}
}

Parameter::~Parameter() {

}

bool Parameter::getConst() const {
	return isConstant;
}
