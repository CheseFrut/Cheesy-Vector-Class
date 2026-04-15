#pragma once
#include "Vector.h"

#define uint unsigned int
#define SELF (*this)

#define N_DIMS 4

template<typename T>
struct _COLOUR4_MEM_STRUCT {
	union {
		struct { T r, g, b, a; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_TYPE Vector::_VectorT<T, N_DIMS, _COLOUR4_MEM_STRUCT<T>>

template<typename T>
struct _Colour4T : public THIS_TYPE {

	using type = THIS_TYPE;

	using type::_VectorT;

	_Colour4T(THIS_TYPE other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS >= nDim1)
		explicit _Colour4T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < nDim1; i++) {
			SELF[i] = other[i];
		}

		for (uint i = nDim1; i < N_DIMS; i++) {
			SELF[i] = T{};
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS < nDim1)
		explicit _Colour4T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static constexpr const THIS_TYPE Red		{ 1, 0, 0, 1};
	static constexpr const THIS_TYPE Green		{ 0, 1, 0, 1};
	static constexpr const THIS_TYPE Blue		{ 0, 0, 1, 1};

	static constexpr const THIS_TYPE Yellow		{ 1, 1, 0, 1};
	static constexpr const THIS_TYPE Cyan		{ 0, 1, 1, 1};
	static constexpr const THIS_TYPE Magenta	{ 1, 0, 1, 1};

	static constexpr const THIS_TYPE White		{ 1, 1, 1, 1};
	static constexpr const THIS_TYPE Black		{ 0, 0, 0, 1};
	static constexpr const THIS_TYPE Null,Empty	{ 0, 0, 0, 0};
};

#undef THIS_TYPE
#undef N_DIMS

#undef uint
#undef SELF

typedef _Colour4T <float> Colour;
typedef _Colour4T <uint8_t> Colour255;