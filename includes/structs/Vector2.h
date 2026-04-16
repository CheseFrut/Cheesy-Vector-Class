#pragma once

#include "Vector.h"

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

	using THIS_TYPE::_VectorT;

	constexpr _Vector2T(THIS_TYPE other) {
		for (unsigned int i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	static const _Vector2T Left;
	static const _Vector2T Right;
	static const _Vector2T Up;
	static const _Vector2T Down;
	static const _Vector2T One;
	static const _Vector2T Zero;
};

template<typename T> inline const _Vector2T<T> _Vector2T<T>::Left	(-1,  0);
template<typename T> inline const _Vector2T<T> _Vector2T<T>::Right	( 1,  0);
template<typename T> inline const _Vector2T<T> _Vector2T<T>::Up		( 0,  1);
template<typename T> inline const _Vector2T<T> _Vector2T<T>::Down	( 0, -1);
template<typename T> inline const _Vector2T<T> _Vector2T<T>::One	( 1,  1);
template<typename T> inline const _Vector2T<T> _Vector2T<T>::Zero	( 0,  0);

#undef THIS_TYPE
#undef N_DIMS

typedef _Vector2T <double> Vector2D;
typedef _Vector2T <float> Vector2;
typedef _Vector2T <long> Vector2L;
typedef _Vector2T <int> Vector2I;
typedef _Vector2T <short> Vector2S;