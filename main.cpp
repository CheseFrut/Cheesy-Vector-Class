#include "Colour.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "UnitTests.cpp"

int main(int argc, char** argv) {

	// ----- Tests ----- //

	Vector3 test = Vector3::One;

	StartUnitTests(false);

	PerformUnitTest(test + Vector3(1), { 2, 1, 1 });
	PerformUnitTest(test + Vector2(1.0f, 1), { 2, 2, 1 });

	PerformUnitTest(test * Vector4::Fill(-2.0f), { -2, -2, -2, -2 });
	PerformUnitTest(Vector4::Fill(-2.0) * test, { -2, -2, -2, -2 });

	PerformUnitTest(test / (Vector4::One * 2), { 0.5, 0.5, 0.5 });
	PerformUnitTest(test / 2, { 0.5, 0.5, 0.5 });

	PerformUnitTest((Vector2)test, { 1, 1 });
	PerformUnitTest((Vector4)test, { 1, 1, 1, 0 });

	// Magnitude

	PerformUnitTest(Vector4(5,5,5,5).Magnitude(), 10); // 9

	// Normalizing

	PerformUnitTest((test * 0.00000009943243545).Normalised(), { 0.577, 0.577, 0.577}, 0.005);
	PerformUnitTest((test * 99432).Normalised(), { 0.577, 0.577, 0.577 }, 0.005);
	PerformUnitTest((test * 9947478732).Normalised(), { 0.577, 0.577, 0.577 }, 0.005);
	PerformUnitTest((test * 994219645747549532).Normalised(), { 0.577, 0.577, 0.577 }, 0.005);
	PerformUnitTest(Vector3(1,2,3).Normalised(), { 0.267, 0.535, 0.802 }, 0.005);

	PerformUnitTest(Vector3(Vector::_VectorT<float, 100>::Fill(1).Normalised()), { 0.1, 0.1, 0.1 }, 0.005);
	PerformUnitTest(Vector3(Vector::_VectorT<float, 100>::Fill(92565.1).Normalised()), { 0.1, 0.1, 0.1 }, 0.005);

	// Dot product

	PerformUnitTest(test.Dot(Vector3::One * 3), 9);
	PerformUnitTest(Vector3::Left.Dot(Vector::One<3> * 3), -3);

	// Equality

	PerformUnitTest(Vector3(0, 1, 0) == Vector::Up, 1);
	PerformUnitTest(Vector::Up == Vector3(1, 1, 1), 0);

	EndUnitTests();
	
	return 0;
}