//
// Created by Niels Turley on 10/26/21.
//

#include "Tuple.h"

bool Tuple::operator<(const Tuple &rhs) const {
	return values < rhs.values;
}

