#pragma once

#include "Vector.h"

#define N_DIMS 4

template<typename T>
struct _VEC4_MEM_STRUCT {
	union {
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_TYPE Vector::_VectorT<T, N_DIMS, _VEC4_MEM_STRUCT<T>>

template<typename T>
struct _Vector4T : public THIS_TYPE {

	using THIS_TYPE::_VectorT;

	constexpr _Vector4T(THIS_TYPE other) {
		for (unsigned int i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	static const _Vector4T Left;
	static const _Vector4T Right;
	static const _Vector4T Up;
	static const _Vector4T Down;
	static const _Vector4T Back;
	static const _Vector4T Forward;
	static const _Vector4T Ana;
	static const _Vector4T Kata;
	static const _Vector4T One;
	static const _Vector4T Zero;
};

template<typename T> inline const _Vector4T<T> _Vector4T<T>::Left		(-1,  0,  0,  0);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Right		( 1,  0,  0,  0);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Up			( 0,  1,  0,  0);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Down		( 0, -1,  0,  0);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Back		( 0,  0, -1,  0);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Forward	( 0,  0,  1,  0);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Ana		( 0,  0,  0,  1);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Kata		( 0,  0,  0, -1);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::One		( 1,  1,  1,  1);
template<typename T> inline const _Vector4T<T> _Vector4T<T>::Zero		( 0,  0,  0,  0);

#undef THIS_TYPE
#undef N_DIMS

typedef _Vector4T <double> Vector4D;
typedef _Vector4T <float> Vector4;
typedef _Vector4T <long> Vector4L;
typedef _Vector4T <int> Vector4I;
typedef _Vector4T <short> Vector4S;