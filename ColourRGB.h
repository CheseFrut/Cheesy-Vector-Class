#pragma once

#pragma once
#include "Vector.h"

#define uint unsigned int
#define SELF (*this)

#define N_DIMS 3

template<typename T>
struct _COLOUR3_MEM_STRUCT {
	union {
		struct { T r, g, b; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_TYPE Vector::_VectorT<T, N_DIMS, _COLOUR3_MEM_STRUCT<T>>

template<typename T>
struct _Colour3T : public THIS_TYPE {

	using type = THIS_TYPE;

	using type::_VectorT;

	_Colour3T(THIS_TYPE other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS >= nDim1)
		explicit _Colour3T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < nDim1; i++) {
			SELF[i] = other[i];
		}

		for (uint i = nDim1; i < N_DIMS; i++) {
			SELF[i] = T{};
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS < nDim1)
		explicit _Colour3T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static constexpr const THIS_TYPE Red	{ 1, 0, 0 };
	static constexpr const THIS_TYPE Green	{ 0, 1, 0 };
	static constexpr const THIS_TYPE Blue	{ 0, 0, 1 };

	static constexpr const THIS_TYPE Yellow	{ 1, 1, 0 };
	static constexpr const THIS_TYPE Cyan	{ 0, 1, 1 };
	static constexpr const THIS_TYPE Magenta{ 1, 0, 1 };

	static constexpr const THIS_TYPE White	{ 1, 1, 1 };
	static constexpr const THIS_TYPE Black	{ 0, 0, 0 };

	/// <summary>
	/// Returns the cross product of the LHS and RHS vectors.
	/// </summary>
	static constexpr const THIS_TYPE Cross(const THIS_TYPE& lhs, const THIS_TYPE& rhs) {
		THIS_TYPE return_value;

		return_value.r = lhs.g * rhs.b - rhs.g * lhs.b;
		return_value.g = lhs.r * rhs.b - rhs.r * lhs.b;
		return_value.b = lhs.r * rhs.g - rhs.r * lhs.g;

		return return_value;
	}
};

#undef THIS_TYPE
#undef N_DIMS

#undef uint
#undef SELF

typedef _Colour3T <float> ColourRGB;
typedef _Colour3T <uint8_t> ColourRGB255;
