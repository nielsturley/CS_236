//
// Created by Niels Turley on 10/26/21.
//

#include "Interpreter.h"

Interpreter::~Interpreter() {
	for (Predicate* predicate : schemes) {
		delete predicate;
	}
	schemes.clear();
	for (Predicate* predicate : facts) {
		delete predicate;
	}
	facts.clear();
	for (Rule* rule : rules) {
		delete rule;
	}
	rules.clear();
	for (Predicate* predicate : queries) {
		delete predicate;
	}
	queries.clear();
}
