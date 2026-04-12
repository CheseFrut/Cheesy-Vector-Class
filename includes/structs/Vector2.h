#pragma once
#include "Vector.h"

#define uint unsigned int
#define SELF (*this)

#define N_DIMS 2

template<typename T>
struct _VEC2_MEM_STRUCT {
	union {
		struct { T x, y; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_TYPE Vector::_VectorT<T, N_DIMS, _VEC2_MEM_STRUCT<T>>

template<typename T>
struct _Vector2T : public THIS_TYPE {

	using type = THIS_TYPE;

	using type::_VectorT;

	_Vector2T(THIS_TYPE other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static constexpr const Vector::_VectorT<T, N_DIMS> Left{ -1, 0 };
	static constexpr const Vector::_VectorT<T, N_DIMS> Right{ 1, 0 };

	static constexpr const Vector::_VectorT<T, N_DIMS> Up{ 0,  1 };
	static constexpr const Vector::_VectorT<T, N_DIMS> Down{ 0, -1 };

	static constexpr const Vector::_VectorT<T, N_DIMS> One = Vector::_VectorT<T, N_DIMS>::Fill(1);
	static constexpr const Vector::_VectorT<T, N_DIMS> Zero = Vector::_VectorT<T, N_DIMS>::Fill(0);
};

#undef THIS_TYPE
#undef N_DIMS

#undef uint
#undef SELF

typedef _Vector2T <double> Vector2D;
typedef _Vector2T <float> Vector2;
typedef _Vector2T <int> Vector2I;
typedef _Vector2T <short> Vector2S;