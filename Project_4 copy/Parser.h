//
// Created by Niels Turley on 9/24/21.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H


#include "DatalogProgram.h"
#include "Token.h"

class Parser {
private:
	std::vector<Token*> tokens;
	size_t index = 0;
	DatalogProgram datalog;

	std::vector<Predicate*> schemes;
	std::vector<Predicate*> facts;
	std::vector<Predicate*> queries;
	std::vector<Rule*> rules;
	std::set<std::string> domain;

public:
	Parser();
	~Parser();

	void parse(std::vector<Token*> inTokens);

	void parseSchemeList();
	void parseFactList();
	void parseRuleList();
	void parseQueryList();
	void parseScheme();
	void parseFact();
	void parseRule();
	void parseQuery();
	void parseHeadPredicate(Predicate* &headPredicate);
	void parsePredicate(std::string &id, std::vector<Parameter*> &parameters);
	void parsePredicateList(std::vector<Predicate*> &bodyPredicates);
	void parseParameterList(std::vector<Parameter*> &parameters);
	void parseStringList(std::vector<Parameter*> &parameters);
	void parseIdList(std::vector<Parameter*> &parameters);
	void parseParameter(std::vector<Parameter*> &parameters);
	void tokenChecker(TokenType type, TokenType matchType);
	void tokenChecker(TokenType type, TokenType matchType, TokenType secondMatchType);
	bool descend(TokenType type, TokenType descendType, TokenType followType);

	friend std::ostream& operator<< (std::ostream& os, const Parser& parser) {
		os << parser.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		out << datalog;
		return out.str();
	}

	std::vector<Predicate*> getSchemes() const {
		return datalog.getSchemes();
	}
	std::vector<Predicate*> getFacts() const {
		return datalog.getFacts();
	}
	std::vector<Rule*> getRules() const {
		return datalog.getRules();
	}
	std::vector<Predicate*> getQueries() const {
		return datalog.getQueries();
	}

};


#endif //PROJECT_1_PARSER_H
