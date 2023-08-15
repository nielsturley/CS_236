//
// Created by Niels Turley on 9/24/21.
//

#include "Parser.h"
#include <iostream>

Parser::Parser() {

}

Parser::~Parser() {
	for (Token* token : tokens) {
		delete token;
	}
	tokens.clear();
}

void Parser::parse(std::vector<Token*> inTokens) {
	try {
		this->tokens = inTokens;

		while (index != tokens.size()) {
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::SCHEMES);
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::COLON);
			parseScheme();
			parseSchemeList();
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::FACTS);
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::COLON);
			parseFactList();
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::RULES);
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::COLON);
			parseRuleList();
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::QUERIES);
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::COLON);
			parseQuery();
			parseQueryList();
			tokenChecker(tokens.at(index)->getTokenType(), TokenType::EOF_TYPE);
			datalog.setSchemes(schemes);
			datalog.setFacts(facts);
			datalog.setRules(rules);
			datalog.setQueries(queries);
			datalog.setDomain(domain);
		}
	}
	catch (Token* error) { std::cout << "Failure!" << std::endl << "  " << *error << std::endl; }

}

void Parser::parseScheme() {
	std::string id = tokens.at(index)->getTokenString();
	std::vector<Parameter*> parameters;
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::LEFT_PAREN);
	Parameter* parameter = new Parameter(tokens.at(index)->getTokenString(), tokens.at(index)->getTokenType());
	parameters.push_back(parameter);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::RIGHT_PAREN)) {
		parseIdList(parameters);
	}
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::RIGHT_PAREN);
	Predicate* scheme = new Predicate(id, parameters);
	schemes.push_back(scheme);
	/**
	for (Parameter* param : parameters) {
		delete param;
	}
	parameters.clear();
	*/
}

void Parser::parseIdList(std::vector<Parameter*> &parameters) {
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::COMMA);
	Parameter* parameter = new Parameter(tokens.at(index)->getTokenString(), tokens.at(index)->getTokenType());
	parameters.push_back(parameter);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::RIGHT_PAREN)) {
		parseIdList(parameters);
	}
}

void Parser::parseSchemeList() {
	if (descend(tokens.at(index)->getTokenType(), TokenType::ID, TokenType::FACTS)) {
		parseScheme();
		parseSchemeList();
	}
}

void Parser::parseFactList() {
	if (descend(tokens.at(index)->getTokenType(), TokenType::ID, TokenType::RULES)) {
		parseFact();
		parseFactList();
	}
}

void Parser::parseFact() {
	std::string id = tokens.at(index)->getTokenString();
	std::vector<Parameter*> parameters;
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::LEFT_PAREN);
	Parameter* parameter = new Parameter(tokens.at(index)->getTokenString(), tokens.at(index)->getTokenType());
	parameters.push_back(parameter);
	domain.insert(tokens.at(index)->getTokenString());
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::STRING);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::RIGHT_PAREN)) {
		parseStringList(parameters);
	}
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::RIGHT_PAREN);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::PERIOD);
	Predicate* fact = new Predicate(id, parameters);
	facts.push_back(fact);
	/**
	for (Parameter* param : parameters) {
		delete param;
	}
	parameters.clear();
	*/
}

void Parser::parseStringList(std::vector<Parameter*> &parameters) {
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::COMMA);
	Parameter* parameter = new Parameter(tokens.at(index)->getTokenString(), tokens.at(index)->getTokenType());
	parameters.push_back(parameter);
	domain.insert(tokens.at(index)->getTokenString());
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::STRING);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::RIGHT_PAREN)) {
		parseStringList(parameters);
	}
}

void Parser::parseRuleList() {
	if (descend(tokens.at(index)->getTokenType(), TokenType::ID, TokenType::QUERIES)) {
		parseRule();
		parseRuleList();
	}
}

void Parser::parseRule() {
	Predicate* headPredicate = nullptr;
	std::vector<Predicate*> bodyPredicates;
	parseHeadPredicate(headPredicate);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::COLON_DASH);
	std::string id;
	std::vector<Parameter*> parameters;
	parsePredicate(id, parameters);
	Predicate* predicate = new Predicate(id, parameters);
	bodyPredicates.push_back(predicate);
	/*
	for (Parameter* param : parameters) {
		delete param;
	}
	parameters.clear();
	 */
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::PERIOD)) {
		parsePredicateList(bodyPredicates);
	}
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::PERIOD);
	Rule* newRule = new Rule(headPredicate, bodyPredicates);
	rules.push_back(newRule);
}

void Parser::parseHeadPredicate(Predicate* &headPredicate) {
	std::string id = tokens.at(index)->getTokenString();
	std::vector<Parameter*> parameters;
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::LEFT_PAREN);
	Parameter* parameter = new Parameter(tokens.at(index)->getTokenString(), tokens.at(index)->getTokenType());
	parameters.push_back(parameter);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::RIGHT_PAREN)) {
		parseIdList(parameters);
	}
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::RIGHT_PAREN);
	headPredicate = new Predicate(id, parameters);
	/*
	for (Parameter* param : parameters) {
		delete param;
	}
	parameters.clear();
	 */
}

void Parser::parsePredicate(std::string &id, std::vector<Parameter*> &parameters) {
	id = tokens.at(index)->getTokenString();
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::LEFT_PAREN);
	parseParameter(parameters);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::RIGHT_PAREN)) {
		parseParameterList(parameters);
	}
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::RIGHT_PAREN);
}

void Parser::parseParameter(std::vector<Parameter*> &parameters) {
	Parameter* parameter = new Parameter(tokens.at(index)->getTokenString(), tokens.at(index)->getTokenType());
	parameters.push_back(parameter);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::ID, TokenType::STRING);
}

void Parser::parseParameterList(std::vector<Parameter*> &parameters) {
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::COMMA);
	parseParameter(parameters);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::RIGHT_PAREN)) {
		parseParameterList(parameters);
	}
}

void Parser::parsePredicateList(std::vector<Predicate*> &bodyPredicates) {
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::COMMA);
	std::string id;
	std::vector<Parameter*> parameters;
	parsePredicate(id, parameters);
	Predicate* predicate = new Predicate(id, parameters);
	bodyPredicates.push_back(predicate);
	if (descend(tokens.at(index)->getTokenType(), TokenType::COMMA, TokenType::PERIOD)) {
		parsePredicateList(bodyPredicates);
	}
	/*
	for (Parameter* param : parameters) {
		delete param;
	}
	parameters.clear();
	 */
}

void Parser::parseQuery() {
	std::string id;
	std::vector<Parameter*> parameters;
	parsePredicate(id, parameters);
	tokenChecker(tokens.at(index)->getTokenType(), TokenType::Q_MARK);
	Predicate* query = new Predicate(id, parameters);
	queries.push_back(query);
	/*
	for (Parameter* param : parameters) {
		delete param;
	}
	parameters.clear();
	 */
}

void Parser::parseQueryList() {
	if (descend(tokens.at(index)->getTokenType(), TokenType::ID, TokenType::EOF_TYPE)) {
		parseQuery();
		parseQueryList();
	}
}


void Parser::tokenChecker(TokenType type, TokenType matchType) {
	if (type == matchType) {
		index++;
	}
	else { throw tokens.at(index); }
}

void Parser::tokenChecker(TokenType type, TokenType matchType, TokenType secondMatchType) {
	if (type == matchType || type == secondMatchType) {
		index++;
	}
	else { throw tokens.at(index); }
}



bool Parser::descend(TokenType type, TokenType descendType, TokenType followType) {
	if (type == descendType) {
		return true;
	}
	else if (type == followType) {
		return false;
	}
	else { throw tokens.at(index); }
}









