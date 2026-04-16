#pragma once

#include "Vector.h"

#define N_DIMS 3

template<typename T>
struct _VEC3_MEM_STRUCT {
	union {
		struct { T x, y, z; };
		struct { T r, g, b; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_TYPE Vector::_VectorT<T, N_DIMS, _VEC3_MEM_STRUCT<T>>

template<typename T>
struct _Vector3T : public THIS_TYPE {

	using THIS_TYPE::_VectorT;

	constexpr _Vector3T(THIS_TYPE other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	static const _Vector3T Left;
	static const _Vector3T Right;
	static const _Vector3T Up;
	static const _Vector3T Down;
	static const _Vector3T Back;
	static const _Vector3T Forward;
	static const _Vector3T One;
	static const _Vector3T Zero;

	/// <summary>
	/// Returns the cross product of the LHS and RHS vectors.
	/// </summary>
	static constexpr const THIS_TYPE Cross(const THIS_TYPE& lhs, const THIS_TYPE& rhs) {
		THIS_TYPE return_value;

		return_value.x = lhs.y * rhs.z - rhs.y * lhs.z;
		return_value.y = lhs.x * rhs.z - rhs.x * lhs.z;
		return_value.z = lhs.x * rhs.y - rhs.x * lhs.y;

		return return_value;
	}
};

template<typename T> inline const _Vector3T<T> _Vector3T<T>::Left		(-1,  0,  0);
template<typename T> inline const _Vector3T<T> _Vector3T<T>::Right		( 1,  0,  0);
template<typename T> inline const _Vector3T<T> _Vector3T<T>::Up			( 0,  1,  0);
template<typename T> inline const _Vector3T<T> _Vector3T<T>::Down		( 0, -1,  0);
template<typename T> inline const _Vector3T<T> _Vector3T<T>::Back		( 0,  0, -1);
template<typename T> inline const _Vector3T<T> _Vector3T<T>::Forward	( 0,  0,  1);
template<typename T> inline const _Vector3T<T> _Vector3T<T>::One		( 1,  1,  1);
template<typename T> inline const _Vector3T<T> _Vector3T<T>::Zero		( 0,  0,  0);

#undef THIS_TYPE
#undef N_DIMS

typedef _Vector3T <double> Vector3D;
typedef _Vector3T <float> Vector3;
typedef _Vector3T <long> Vector3L;
typedef _Vector3T <int> Vector3I;
typedef _Vector3T <short> Vector3S;