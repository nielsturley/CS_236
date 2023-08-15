//
// Created by Niels Turley on 9/24/21.
//

#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H

#include <vector>
#include "Parameter.h"


class Predicate {
private:
	std::string id;
	std::vector<Parameter*> parameters;

public:
	Predicate(std::string id, std::vector<Parameter*> parameters);
	~Predicate();

	void setID(std::string newId) {
		id = newId;
	}

	void setParameters(std::vector<Parameter*> newParameters) {
		for (Parameter* parameter : parameters) {
			delete parameter;
		}
		parameters.clear();
		parameters = newParameters;
	}

	std::string getID() const {
		return id;
	}

	std::vector<Parameter*> getParameters() const {
		return parameters;
	}

	friend std::ostream& operator<< (std::ostream& os, const Predicate& predicate) {
		os << predicate.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		out << id << "(";
		for (size_t i = 0; i < parameters.size(); ++i) {
			if (i == 0) {
				out << *parameters.at(i);
			}
			else {
				out << "," << *parameters.at(i);
			}
		}
		out << ")";
		return out.str();
	}
};


#endif //PROJECT_1_PREDICATE_H
