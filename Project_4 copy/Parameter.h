//
// Created by Niels Turley on 9/24/21.
//

#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H

#include <string>
#include <sstream>
#include "Token.h"

class Parameter {
private:
	std::string id; //TODO Label the parameter as an id or a string
	TokenType type = TokenType::ID;
	bool isConstant = false;

public:
	Parameter(std::string id, TokenType type);
	~Parameter();

	bool getConst() const;

	friend std::ostream& operator<< (std::ostream& os, const Parameter& parameter) {
		os << parameter.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		out << id;
		return out.str();
	}
};


#endif //PROJECT_1_PARAMETER_H
