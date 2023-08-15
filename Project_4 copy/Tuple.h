//
// Created by Niels Turley on 10/26/21.
//

#ifndef PROJECT_3_TUPLE_H
#define PROJECT_3_TUPLE_H

#include <vector>
#include <string>
#include <sstream>


class Tuple {
private:
	std::vector<std::string> values;

public:
	Tuple(std::vector<std::string> values) {
		this->values = values;
	}
	~Tuple() {}
	bool operator<(const Tuple &rhs) const;

	std::vector<std::string> getValues() const {
		return values;
	}


};


#endif //PROJECT_3_TUPLE_H
