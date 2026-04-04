#pragma once

enum InvSqrtPrecision : const unsigned int {
	LOW = 1,
	MEDIUM = 2,
	HIGH = 3,
};

/// <summary>
/// Uses the Quake III fast inverse square root equation to approximate 1/sqrt(x). <br/>
/// Iterated upon the algorithm given in this Stack Overflow post: https://stackoverflow.com/a/1349572.
/// </summary>
/// <param name="x">The input number</param>
/// <param name="iteration_count">The number of iterations to perform. A higher number such as 8 gives a very accurate result. However a value of 1 is perfectly reasonable for things like graphics calculations. </param>
/// <returns>An approximation of 1/sqrt(x)</returns>
extern inline constexpr float FastInvSqrt(float value, unsigned int iteration_count = 1);