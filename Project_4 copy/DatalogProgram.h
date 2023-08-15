//
// Created by Niels Turley on 9/24/21.
//

#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H

#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <set>

class DatalogProgram {
private:
	std::vector<Predicate*> schemes;
	std::vector<Predicate*> facts;
	std::vector<Predicate*> queries;
	std::vector<Rule*> rules;
	std::set<std::string> domain;

public:
	DatalogProgram();
	~DatalogProgram();

	void setDomain(std::set<std::string> newDomain) {
		this->domain = newDomain;
	}

	void setSchemes(std::vector<Predicate*> newSchemes) {
		this->schemes = newSchemes;
	}

	void setFacts(std::vector<Predicate*> newFacts) {
		this->facts = newFacts;
	}

	void setQueries(std::vector<Predicate*> newQueries) {
		this->queries = newQueries;
	}

	void setRules(std::vector<Rule*> newRules) {
		this->rules = newRules;
	}

	std::vector<Predicate*> getSchemes() const {
		return schemes;
	}
	std::vector<Predicate*> getFacts() const {
		return facts;
	}
	std::vector<Rule*> getRules() const {
		return rules;
	}
	std::vector<Predicate*> getQueries() const {
		return queries;
	}

	friend std::ostream& operator<< (std::ostream& os, const DatalogProgram& datalogProgram) {
		os << datalogProgram.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		out << "Schemes(" << schemes.size() << "):" << std::endl;
		for (size_t i = 0; i < schemes.size(); ++i) {
			out << "  " << *schemes.at(i) << std::endl;
		}
		out << "Facts(" << facts.size() << "):" << std::endl;
		for (size_t i = 0; i < facts.size(); ++i) {
			out << "  " << *facts.at(i) << "." << std::endl;
		}
		out << "Rules(" << rules.size() << "):" << std::endl;
		for (size_t i = 0; i < rules.size(); ++i) {
			out << "  " << *rules.at(i) << "." << std::endl;
		}
		out << "Queries(" << queries.size() << "):" << std::endl;
		for (size_t i = 0; i < queries.size(); ++i) {
			out << "  " << *queries.at(i) << "?" << std::endl;
		}
		out << "Domain(" << domain.size() << "):" << std::endl;
		for (std::string dom : domain) {
			out << "  " << dom << std::endl;
		}
		return out.str();
	}


};


#endif //PROJECT_1_DATALOGPROGRAM_H
