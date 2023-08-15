//
// Created by Niels Turley on 9/24/21.
//

#include "Rule.h"

Rule::Rule(Predicate *headPredicate, std::vector<Predicate *> bodyPredicates) {
	this->headPredicate = headPredicate;
	this->bodyPredicates = bodyPredicates;
}

Rule::~Rule() {
	for (Predicate* predicate : bodyPredicates) {
		delete predicate;
	}
	bodyPredicates.clear();
	delete headPredicate;
}
