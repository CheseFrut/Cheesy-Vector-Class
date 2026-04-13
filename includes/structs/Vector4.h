#pragma once
#include "Vector.h"

#define uint unsigned int
#define SELF (*this)

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

	using type = THIS_TYPE;

	using type::_VectorT;

	_Vector4T(THIS_TYPE other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS >= nDim1)
	explicit _Vector4T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < nDim1; i++) {
			SELF[i] = other[i];
		}

		for (uint i = nDim1; i < N_DIMS; i++) {
			SELF[i] = T{};
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS < nDim1)
	explicit _Vector4T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static constexpr const Vector::_VectorT<T, N_DIMS> Left{ -1, 0, 0, 0 };
	static constexpr const Vector::_VectorT<T, N_DIMS> Right{ 1, 0, 0, 0 };

	static constexpr const Vector::_VectorT<T, N_DIMS> Up{ 0,  1, 0, 0 };
	static constexpr const Vector::_VectorT<T, N_DIMS> Down{ 0, -1, 0, 0 };

	static constexpr const Vector::_VectorT<T, N_DIMS> Back{ 0, 0, -1 };
	static constexpr const Vector::_VectorT<T, N_DIMS> Forward{ 0, 0,  1 };

	static constexpr const Vector::_VectorT<T, N_DIMS> Ana{ 0, 0, 0,  1 };
	static constexpr const Vector::_VectorT<T, N_DIMS> Kata{ 0, 0, 0, -1 };

	static constexpr const Vector::_VectorT<T, N_DIMS> One = Vector::_VectorT<T, N_DIMS>::Fill(1);
	static constexpr const Vector::_VectorT<T, N_DIMS> Zero = Vector::_VectorT<T,N_DIMS>::Fill(0);
};

#undef THIS_TYPE
#undef N_DIMS

#undef uint
#undef SELF

typedef _Vector4T <double> Vector4D;
typedef _Vector4T <float> Vector4;
typedef _Vector4T <long> Vector4L;
typedef _Vector4T <int> Vector4I;
typedef _Vector4T <short> Vector4S;