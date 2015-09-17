#include <iostream>
#include "trivial.h"

int main() {

	primitives p1 = {1, 2.0, {3, 4}};
	std::cout << "p.x has the value: " << p1.x << std::endl;

	return 0;
}

