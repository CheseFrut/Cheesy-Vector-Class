#include "Vector.h"
#include <iostream>

int main(int argc, char** argv) {

	Vector3<float> test1 = Vector3<>::One * 3;
	std::cout << test1 - Vectors::One<3> << std::endl;

	test1.y += 4;
	std::cout << test1 << std::endl;

	Vector4<> e = Vector4<>::One + test1;

	std::cout << e << std::endl;

	return 0;
}