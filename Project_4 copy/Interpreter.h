//
// Created by Niels Turley on 10/26/21.
//

#ifndef PROJECT_3_INTERPRETER_H
#define PROJECT_3_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <iostream>

class Interpreter {
private:
	std::vector<Predicate*> schemes;
	std::vector<Predicate*> facts;
	std::vector<Predicate*> queries;
	std::vector<Rule*> rules;
	Database database;
public:
	Interpreter(std::vector<Predicate*> schemes,
				std::vector<Predicate*> facts,
				std::vector<Predicate*> queries,
				std::vector<Rule*> rules) {
		this->schemes = schemes;
		this->facts = facts;
		this->queries = queries;
		this->rules = rules;
	}
	~Interpreter();

	void run() {
		for (Predicate* s : schemes) {
			std::vector<std::string> data;
			for (Parameter* parameter : s->getParameters()) {
				data.push_back(parameter->toString());
			}
			database.addRelation(s->getID(), data);
		}
		for (Predicate* f : facts) {
			std::vector<std::string> data;
			for (Parameter* parameter : f->getParameters()) {
				data.push_back(parameter->toString());
			}
			database.addTuple(f->getID(), data);
		}
		std::cout << "Rule Evaluation" << std::endl;
		int ruleCount = 0;
		bool anyChange = true;
		while (anyChange) {
			anyChange = false;
			for (Rule* r : rules) {
				std::cout << *r << "." << std::endl;
				std::vector<Relation*> bodyRelations;
				size_t numOfRel = 0;
				for (Predicate* p : r->getBodyPredicates()) {
					Relation* newRel = evaluatePredicate(*p);
					bodyRelations.push_back(newRel);
					++numOfRel;
				}
				Relation* finalRelation = bodyRelations.at(0);
				for (size_t i = 1; i < numOfRel; ++i) {
					finalRelation = finalRelation->join(bodyRelations.at(i));
				}
				std::vector<std::string> columns;
				for (Parameter* p : r->getHeadPredicate()->getParameters()) {
					columns.push_back(p->toString());
				}

				Relation* holdRelation;
				holdRelation = finalRelation->project(columns, true);
				delete finalRelation;
				finalRelation = holdRelation;

				Relation* databaseRel = database.getRelation(r->getHeadPredicate()->getID());
				holdRelation = finalRelation->rename(databaseRel->getHeader().getAttributes());
				delete finalRelation;
				finalRelation = holdRelation;
				bool changeOccured = databaseRel->unionize(finalRelation);
				if (changeOccured) {
					anyChange = true;
				}
				//std::cout << *finalRelation << std::endl;
			}
			++ruleCount;
		}
		std::cout << std::endl << "Schemes populated after " << ruleCount << " passes through the Rules." << std::endl << std::endl;
		std::cout << "Query Evaluation" << std::endl;
		for (Predicate* q : queries) {
			std::cout << *q << "? ";
			Relation* r = evaluatePredicate(*q);
			if (r->numTuples() == 0) {
				std::cout << "No" << std::endl;
			}
			else {
				std::cout << "Yes(" << r->numTuples() << ")" << std::endl;
				std::cout << *r;
			}
		}
	}

	friend std::ostream& operator<< (std::ostream& os, const Interpreter& interpreter) {
		os << interpreter.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		out << database;
		return out.str();
	}

	Relation* evaluatePredicate(const Predicate& p) {
		Relation* r = new Relation(*database.getRelation(p.getID()));
		int i = 0;
		std::map<std::string, int> memory;
		std::vector<std::string> variables;
		for (Parameter* parameter : p.getParameters()) {
			if (parameter->getConst()) {
				Relation* rNew;
				rNew = r->select(i, parameter->toString());
				delete r;
				r = rNew;
				variables.push_back(parameter->toString());
			}
			else {
				if (memory.find(parameter->toString()) != memory.end()) {
					Relation *rNew;
					rNew = r->select(memory.at(parameter->toString()), i);
					delete r;
					r = rNew;
					variables.push_back(parameter->toString());
				}
				else {
					memory.insert(std::pair<std::string, int> (parameter->toString(), i));
					variables.push_back(parameter->toString());
				}
			}
			++i;
		}
		Relation* rNew;
		rNew = r->project(variables);
		delete r;
		r = rNew;
		rNew = r->rename(variables);
		delete r;
		r = rNew;
		return r;
	}
};


#endif //PROJECT_3_INTERPRETER_H
