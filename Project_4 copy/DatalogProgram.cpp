//
// Created by Niels Turley on 9/24/21.
//

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {

}

DatalogProgram::~DatalogProgram() {
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

