#pragma once
#include "Vector.h"

#define uint unsigned int
#define SELF (*this)

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

	using type = THIS_TYPE;

	using type::_VectorT;

	_Vector3T(THIS_TYPE other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS >= nDim1)
	explicit _Vector3T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < nDim1; i++) {
			SELF[i] = other[i];
		}

		for (uint i = nDim1; i < N_DIMS; i++) {
			SELF[i] = T{};
		}
	}

	template <typename T1, uint nDim1, typename MEMORY_STRUCTURE1> requires(N_DIMS < nDim1)
	explicit _Vector3T(const Vector::_VectorT<T1, nDim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static constexpr const THIS_TYPE Left{ -1, 0, 0 };
	static constexpr const THIS_TYPE Right{ 1, 0, 0 };

	static constexpr const THIS_TYPE Up{ 0,  1, 0 };
	static constexpr const THIS_TYPE Down{ 0, -1, 0 };

	static constexpr const THIS_TYPE Back{ 0, 0, -1 };
	static constexpr const THIS_TYPE Forward{ 0, 0,  1 };

	static constexpr const THIS_TYPE One = THIS_TYPE::Fill(1);
	static constexpr const THIS_TYPE Zero = THIS_TYPE::Fill(0);

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

#undef THIS_TYPE
#undef N_DIMS

#undef uint
#undef SELF

typedef _Vector3T <double> Vector3D;
typedef _Vector3T <float> Vector3;
typedef _Vector3T <int> Vector3I;
typedef _Vector3T <short> Vector3S;