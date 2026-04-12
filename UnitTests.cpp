
#include "Vector.h"
#include <initializer_list>
#include <iostream>
#include <string>

#define uint unsigned int
#define SELF (*this)

static uint current_unit_test_number;
static uint total_failures;
static bool unit_tests_active;
static bool showing_successful_tests;

constexpr static void StartUnitTests(bool show_successful_tests = true) {
	current_unit_test_number = 0;
	total_failures = 0;
	unit_tests_active = true;

	showing_successful_tests = show_successful_tests;
}

template <typename T, uint nDim, typename MEMORY_STRUCTURE, typename T1> requires (std::is_arithmetic<T1>::value)
constexpr static void PerformUnitTest(const Vector::_VectorT<T, nDim, MEMORY_STRUCTURE>& input, const std::initializer_list<T1>& desired_result, double error_margin = 0) {
	current_unit_test_number++;

	if (!unit_tests_active) {
		std::cerr << "[!] ERROR: PLEASE RUN StartUnitTests() BEFORE PerformUnitTest()" << std::endl;
		return;
	}

	bool success = true;

	if (nDim != desired_result.size()) success = false;

	for (uint i = 0; i < desired_result.size(); i++) {
		if (std::abs(input[i] - static_cast<T>(desired_result.begin()[i])) > error_margin) success = false;
	}

	if (success) {
		if (showing_successful_tests)
			std::cout << current_unit_test_number << '\t' << "[O] :\t GOT " << input << std::endl;
	}
	else {
		std::cout << std::endl << current_unit_test_number << '\t' << "[X] : WANTED (";
		for (uint i = 0; i < desired_result.size(); i++) {
			if (i != desired_result.size() - 1)
				std::cout << std::to_string(desired_result.begin()[i]) << ", ";
			else
				std::cout << std::to_string(desired_result.begin()[i]) << ')';
		}

		std::cout << "\n\t\t" << " GOT " << input << std::endl << std::endl;

		total_failures++;
	}
}

template <typename T, typename T1>
	requires (std::is_convertible<T1, T>::value&& std::is_convertible<double, T>::value)
constexpr static void PerformUnitTest(const T& input, const T1& desired_result, double error_margin = 0) {
	current_unit_test_number++;

	if (!unit_tests_active) {
		std::cerr << "[!] ERROR: PLEASE RUN StartUnitTests() BEFORE PerformUnitTest()" << std::endl;
		return;
	}

	bool success = (std::abs(input - static_cast<T>(desired_result)) <= error_margin);

	if (success) {
		if (showing_successful_tests)
			std::cout << current_unit_test_number << '\t' << "[O] :\t GOT " << input << std::endl;
	}
	else
		std::cout << std::endl << current_unit_test_number << '\t' << "[X] : WANTED " << desired_result << "\n\t\t" << " GOT " << input << std::endl << std::endl;
}

constexpr static void EndUnitTests() {

	if (!unit_tests_active) {
		std::cerr << "[!] ERROR: PLEASE RUN StartUnitTests() BEFORE EndUnitTests()" << std::endl;
		return;
	}

	std::cout << std::endl << current_unit_test_number - total_failures << " / " << current_unit_test_number << " Successful tests" << std::endl;

	std::cout << std::endl;

	if (total_failures > 0)
		std::cout << "[!] UNIT TEST FAILIER [!]" << std::endl;
	else
		std::cout << "No Errors Found (YAY!!!)" << std::endl;

	unit_tests_active = false;
}

#undef uint
#undef SELF