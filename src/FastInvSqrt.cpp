#include "FastInvSqrt.h"

inline constexpr float FastInvSqrt(float x, unsigned int iteration_count) {

	float xhalf = 0.5f * x;
	int i = *(int*)&x;              // get bits for floating value
	i = 0x5f375a86 - (i >> 1);      // gives initial guess y0
	x = *(float*)&i;                // convert bits back to float

	while (iteration_count--)
		x = x * (1.5f - xhalf * x * x); // Newton approximation equation for 1/sqrt(x)

	return x;
}