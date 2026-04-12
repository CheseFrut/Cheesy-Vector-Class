#include "Colour.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <initializer_list>
#include <iostream>
#include <string>

uint current_unit_test_number = 1;

template <typename T, uint nDim, typename MEMORY_STRUCTURE, typename T1> requires (std::is_arithmetic<T1>::value)
void PerformUnitTest(const Vector::_VectorT<T, nDim, MEMORY_STRUCTURE>& input, const std::initializer_list<T1>& desired_result) {
	
	bool success = true;

	if (nDim != desired_result.size()) success = false;

	for (uint i = 0; i < desired_result.size(); i++) {
		if (input[i] != T(desired_result.begin()[i])) success = false;
	}

	std::string result = std::to_string(current_unit_test_number) + ' ';

	if (success)
		result += "[ :) ]";
	else {
		result += "[ X( ] : WANTED (";
		for (uint i = 0; i < desired_result.size(); i++) {
			if (i != desired_result.size() - 1)
				result += std::to_string(desired_result.begin()[i]) + ", ";
			else
				result += std::to_string(desired_result.begin()[i]) + ")";
		}

		result += " ; GOT : ";
		std::cout << result << input << std::endl;
		return;
	}
	std::cout << result << std::endl;

	current_unit_test_number++;
}

int main(int argc, char** argv) {

	// Simple tests

	Vector3 test = Vector3::One;

	std::cout << "Value    " << "\t" << "|   Wanted Value" << std::endl << std::endl;

	PerformUnitTest(test + Vector3(1), { 2, 1, 1 });
	PerformUnitTest(test + Vector2(1.0f, 1), { 2, 2, 1 });

	PerformUnitTest(test * Vector4::Fill(-2.0f), { -2, -2, -2, -2 });
	PerformUnitTest(Vector4::Fill(-2.0) * test, { -2, -2, -2, -2 });

	PerformUnitTest(test / (Vector4::One * 2), { 0.5, 0.5, 0.5 });
	PerformUnitTest(test / 2, { 0.5, 0.5, 0.5 });

	PerformUnitTest((Vector2)test, { 1, 1 });
	PerformUnitTest((Vector4)test, { 1, 1, 1, 0 });

	// Normalizing

	PerformUnitTest((test * 0.000000000000000000001009943243545).Normalised(), {1, 1, 1});
	PerformUnitTest((test * 99432).Normalised(), {1, 1, 1});
	PerformUnitTest((test * 9947478732).Normalised(), {1, 1, 1});
	PerformUnitTest((test * 994219645747549532).Normalised(), {1, 1, 1});

	PerformUnitTest(Vector3(Vector::_VectorT<float, 100>::Fill(1).Normalised()), { 1, 1, 1 });
	PerformUnitTest(Vector3(Vector::_VectorT<float, 100>::Fill(9999937436802576565.1).Normalised()), { 1, 1, 1 });

	// Dot product

	PerformUnitTest(Vector::_VectorT<float, 1>(test.Dot(Vector3::One * 3)), {9});
	
	return 0;
}