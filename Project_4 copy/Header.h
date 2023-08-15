//
// Created by Niels Turley on 10/26/21.
//

#ifndef PROJECT_3_HEADER_H
#define PROJECT_3_HEADER_H

#include <vector>
#include <string>

class Header {
private:
	std::vector<std::string> attributes;
public:
	Header() {}
	Header(std::vector<std::string> attributes) {
		this->attributes = attributes;
	}
	~Header() {}

	std::vector<std::string> getAttributes() const {
		return attributes;
	}

};


#endif //PROJECT_3_HEADER_H
