#ifndef PROJECT_3_DATABASE_H
#define PROJECT_3_DATABASE_H

#include <map>
#include "Relation.h"


class Database {
private:
	std::map<std::string, Relation> relations;

public:
	Database() {}
	~Database() {}
	void addRelation(std::string name, std::vector<std::string> attributes) {
		Header header = Header(attributes);
		Relation relation = Relation(name, header);
		relations.insert(std::pair<std::string, Relation>(name, relation));
	}

	void addTuple(std::string name, std::vector<std::string> values) {
		Tuple tuple = Tuple(values);
		relations.at(name).addTuple(tuple);
	}

	Relation* getRelation(std::string name) {
		return &relations.at(name);
	}

	/*
	std::string printRelation(std::string name) const {
		std::ostringstream out;
		out << relations.at(name);
		return out.str();
	}
	*/

	friend std::ostream& operator<< (std::ostream& os, const Database& database) {
		os << database.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		for (auto iter = relations.begin(); iter != relations.end(); ++iter) {
			out << iter->first << std::endl << iter->second << std::endl;
		}
		return out.str();
	}

};


#endif //PROJECT_3_DATABASE_H
