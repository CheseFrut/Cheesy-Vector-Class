#include "Vector.h"
#include <iostream>

int main(int argc, char** argv) {

	Vector3<float> test1 = Vector3<>(3);
	std::cout << test1 - Vectors::One;

	test1.y += 4;
	std::cout << test1;

	return 0;
}