#include "Colour.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <iostream>

int main(int argc, char** argv) {

	// Simple tests

	Vector3 test = Vector3(1, 1.0, 1.0f);

	std::cout << "Value    " << "\t" << "|   Wanted Value" << std::endl << std::endl;

	std::cout << test + Vector3(1) << "\t" << ":   (2, 1, 1)" << std::endl;
	std::cout << test + Vector2(1.0f, 1) << "\t" << ":   (2, 2, 1)" << std::endl;
	std::cout << test * Vector4(-2, 4.5, 2.5f) << "\t" << ":   (-2, 4.5, 2.5, 0)" << std::endl;
	std::cout << test / (Vector4::One * 2) << "\t" << ":   (0.5, 0.5, 0.5)" << std::endl;
	std::cout << (Vector2)test << "  \t" << ":   (1, 1)" << std::endl;
	std::cout << (Vector4)test << "\t" << ": (1, 1, 1, 0)" << std::endl;
	

	return 0;
}