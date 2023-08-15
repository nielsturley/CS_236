//
// Created by Niels Turley on 10/26/21.
//

#ifndef PROJECT_3_RELATION_H
#define PROJECT_3_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>
#include <sstream>
#include <map>
#include <iostream>


class Relation {
private:
	std::set<Tuple> tuples;
	std::string name;
	Header header;

public:
	Relation() {}
	Relation(std::string name, Header header) {
		this->name = name;
		this->header = header;
	}
	~Relation() {}

	void addTuple (Tuple tuple) {
		tuples.insert(tuple);
	}

	Header getHeader() const {
		return header;
	}

	size_t numTuples() const {
		return tuples.size();
	}

	Relation* select(int index, int indexTwo) {
		Relation* r = new Relation(name, header);
		for (Tuple t : tuples) {
			if (t.getValues().at(index) == t.getValues().at(indexTwo)) {
				r->addTuple(t);
			}
		}
		return r;
	}

	Relation* select(int index, std::string value) {
		Relation* r = new Relation(name, header);
		for (Tuple t : tuples) {
			if (t.getValues().at(index) == value) {
				r->addTuple(t);
			}
		}
		return r;
	}

	Relation* project(std::vector<std::string> columns, bool isRule = false) {
		std::vector<std::string> attributes;
		std::vector<int> indices;
		if (!isRule) {
			for (size_t i = 0; i < columns.size(); ++i) {
				bool isNotADuplicate = true;
				for (size_t p = 0; p < i; ++p) {
					if (columns.at(p) == columns.at(i)) {
						isNotADuplicate = false;
						break;
					}
				}
				if (columns.at(i).at(0) != '\'' && isNotADuplicate) {
					attributes.push_back(header.getAttributes().at(i));
					indices.push_back(i);
				}
			}
		}
		else {
			for (std::string s : columns) {
				for (size_t i = 0; i < header.getAttributes().size(); ++i) {
					if (header.getAttributes().at(i) == s) {
						attributes.push_back(header.getAttributes().at(i));
						indices.push_back(i);
						break;
					}
				}
			}
		}
		Relation* r = new Relation(name, Header(attributes));
		for (Tuple t : tuples) {
			std::vector<std::string> newValues;
			for (size_t i = 0; i < indices.size(); ++i) {
				newValues.push_back(t.getValues().at(indices.at(i)));
			}
			Tuple tNew = Tuple(newValues);
			r->addTuple(tNew);
		}
		return r;
	}

	Relation* rename(std::vector<std::string> columns) {
		std::vector<std::string> attributes;
		for (size_t i = 0; i < columns.size(); ++i) {
			bool isNotADuplicate = true;
			for (size_t p = 0; p < attributes.size(); ++p) {
				if (attributes.at(p) == columns.at(i)) {
					isNotADuplicate = false;
				}
			}
			if (columns.at(i).at(0) != '\'' && isNotADuplicate) {
				attributes.push_back(columns.at(i));
			}
		}
		Relation* r = new Relation(name,Header(attributes));
		for (Tuple t : tuples) {
			r->addTuple(t);
		}
		return r;
	}

	Relation* join(Relation *inputRel) {
		std::vector<std::string> newAttributes = header.getAttributes();
		std::map<int, int> matchingAttributes;
		std::vector<size_t> columnsToSkip;
		for (size_t i = 0; i < newAttributes.size(); ++i) {
			for (size_t j = 0; j < inputRel->header.getAttributes().size(); ++j) {
				if (newAttributes.at(i) == inputRel->header.getAttributes().at(j)) {
					matchingAttributes.insert(std::pair<int,int>(i,j));
					columnsToSkip.push_back(j);
				}
			}
		}
		for (size_t i = 0; i < inputRel->header.getAttributes().size(); ++i) {
			bool addAttribute = true;
			for (size_t col : columnsToSkip) {
				if (i == col) {
					addAttribute = false;
					break;
				}
			}
			if (addAttribute) {
				newAttributes.push_back(inputRel->header.getAttributes().at(i));
			}
		}
		std::string newName = name + " |x| " + inputRel->name;
		Relation* r = new Relation(newName, Header(newAttributes));
		for (const Tuple& tupleOne : tuples) {
			for (const Tuple& tupleTwo : inputRel->tuples) {
				std::vector<std::string> newValues = tupleOne.getValues();
				bool canJoin = true;
				for (auto attribute : matchingAttributes) {
					if (tupleOne.getValues().at(attribute.first) != tupleTwo.getValues().at(attribute.second)) {
						canJoin = false;
						break;
					}
				}
				if (canJoin) {
					for (size_t i = 0; i < tupleTwo.getValues().size(); ++i) {
						if (columnsToSkip.empty()) {
							newValues.push_back(tupleTwo.getValues().at(i));
						}
						else {
							bool dontSkip = true;
							for (size_t col: columnsToSkip) {
								if (i == col) {
									dontSkip = false;
									break;
								}
							}
							if (dontSkip) {
								newValues.push_back(tupleTwo.getValues().at(i));
							}
						}
					}
					Tuple t = Tuple(newValues);
					r->addTuple(t);
				}
			}
		}

		return r;
	}

	bool unionize(Relation* rel) {
		bool changeOccured = false;
		for (const Tuple& t : rel->tuples) {
			if (tuples.insert(t).second) {
				changeOccured = true;
				unsigned int i = 0;
				for (std::string attribute : header.getAttributes()) {
					if (i == 0) { std::cout << "  " << attribute << "=" << t.getValues().at(i); }
					else { std::cout << ", " << attribute << "=" << t.getValues().at(i); }
					++i;
				}
				if (i != 0) { std::cout << std::endl; }
			}
		}
		return changeOccured;
	}

	friend std::ostream& operator<< (std::ostream& os, const Relation& relation) {
		os << relation.toString();
		return os;
	}

	std::string toString() const {
		std::ostringstream out;
		for (Tuple t : tuples) {
			unsigned int i = 0;
			for (std::string attribute : header.getAttributes()) {
				if (i == 0) { out << "  " << attribute << "=" << t.getValues().at(i); }
				else { out << ", " << attribute << "=" << t.getValues().at(i); }
				++i;
			}
			if (i != 0) { out << std::endl; }
		}
		return out.str();
	}
};


#endif //PROJECT_3_RELATION_H
