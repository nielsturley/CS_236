//
// Created by Niels Turley on 9/24/21.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H

#include "Predicate.h"


class Rule {
private:
	Predicate* headPredicate;
	std::vector<Predicate*> bodyPredicates;

public:
	Rule(Predicate* headPredicate, std::vector<Predicate*> bodyPredicates);
	~Rule();

	friend std::ostream& operator<< (std::ostream& os, const Rule& rule) {
		os << rule.toString();
		return os;
	}

	Predicate* getHeadPredicate() const {
		return headPredicate;
	}

	std::vector<Predicate*> getBodyPredicates() const {
		return bodyPredicates;
	}

	std::string toString() const {
		std::ostringstream out;
		out << *headPredicate << " :- ";
		for (size_t i = 0; i < bodyPredicates.size(); ++i) {
			if (i == 0) {
				out << *bodyPredicates.at(i);
			}
			else {
				out << "," << *bodyPredicates.at(i);
			}
		}
		return out.str();
	}
};


#endif //PROJECT_1_RULE_H
