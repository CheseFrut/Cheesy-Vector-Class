#pragma once

#include "defines.h"
#include "FastInvSqrt.h"
#include <array>
#include <cmath>
#include <cstdarg>
#include <ostream>
#include <type_traits>
#include <utility>

namespace Vectors {

	// The memory structure allows you to for example make a vector3 structure that unions the data array with struct { T x, y, z; }
	// Any custom memory structure requires a member data of type std::array<T, Dim>
	template<typename T, uint Dim>
	struct DEFAULT_MEMORY_STRUCTURE {
		std::array<T, Dim> data{ };
	};

template <typename T = double, uint Dim = 3, class MEMORY_STRUCTURE = DEFAULT_MEMORY_STRUCTURE<T, Dim>> 
struct Vector : public MEMORY_STRUCTURE {

private:

	#define THIS_TYPE Vector<T, Dim, MEMORY_STRUCTURE>

	using MEMORY_STRUCTURE::data;

	// variadic handlers

	constexpr void set_at(uint idx, const T& value) {
		this->data[idx] = value;
	}

	template<uint... idx, typename... Args>
	constexpr void set_from_variadic_indexer(std::index_sequence<idx...>, Args... args) {
		((set_at(idx, args)), ...);
	}

	template<typename... Args>
	constexpr void set_from_variadic(Args&&... args) {
		set_from_variadic_indexer(std::make_index_sequence<sizeof ... (Args)>{}, std::forward<Args>(args)...);
	}

	// check if MEMORY_STRUCTURE has a member std::array<T, Dim> called name

	template <typename = void>
	struct DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY 
		: std::false_type { };

	template <>
	struct DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY<std::void_t<decltype(std::declval<std::array<T, Dim>>().data)>>
		: std::true_type { };

public:

	static_assert(std::is_arithmetic<T>::value,
		"T must be an arithmetic type.");

	static_assert(Dim > 0,
		"Vector cannot have 0 dimensions.");

	static_assert(DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY::value,
		"Memory structure requires the following member: \nstd::array<typename T, std::size_t Dim> data");

	using valueType = T;
	static constexpr uint dimensionCount = Dim;

	explicit constexpr Vector(T value = T{}) { data.fill(value); }

	template<typename... Args> requires ( // Variadic constructor is used if:
		(sizeof...(Args) > 0) &&			// - number of args is greater than 1 (including initial arg).
		(sizeof...(Args) + 1 <= Dim) &&		// - number of args is less than or equal two number of stated dimensions.
		(std::conjunction_v<std::is_convertible<Args, T>...>)) // - if all of the given parameters are convertible to a numeric type.
	constexpr Vector(T t, Args... args) : Vector() {
		set_from_variadic(t, args...);
	}

	// Converts to a vector with more or an equal number of dimensions. 
	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1> requires (Dim1 <= Dim)
	constexpr Vector(const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) : Vector() {

		for (uint i = 0; i < Dim1; i++) {
			data[i] = static_cast<T>(other[i]);
		}
	}

	// Converts to a vector with less dimensions. This is explicit to avoid implicit loss of data.
	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1> requires (Dim1 > Dim)
	explicit constexpr Vector(const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) : Vector() {

		for (uint i = 0; i < Dim; i++) {
			data[i] = static_cast<T>(other[i]);
		}
	}

	T& at(const uint idx) {
		return data.at(idx);
	}

	const T& at(const uint idx) const {
		return data.at(idx);
	}

	T& operator [] (const uint idx) {
		return at(idx);
	}

	const T& operator [] (const uint idx) const {
		return at(idx);
	}

	constexpr operator bool() const {
		for (uint i = 0; i < Dim; i++)
			if (data[i]) return true;

		return false;
	}

	friend std::ostream& operator << (std::ostream& ostream, const THIS_TYPE& vector) {
		ostream << '(';

		for (uint i = 0; i < vector.dimensionCount; i++) {
			if (i == 0)
				ostream << vector[i];
			else
				ostream << ", " << vector[i];
		}
		ostream << ')';

		return ostream;
	}

	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1>
	constexpr THIS_TYPE operator *= (const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < std::min(Dim, Dim1); i++) {
			this->data[i] *= other[i];
		}
		return SELF;
	}

	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1>
	constexpr THIS_TYPE operator /= (const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < std::min(Dim, Dim1); i++) {
			this->data[i] /= other[i];
		}
		return SELF;
	}

	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1>
	constexpr THIS_TYPE operator += (const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < std::min(Dim, Dim1); i++) {
			this->data[i] += other[i];
		}
		return SELF;
	}

	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1>
	constexpr THIS_TYPE operator -= (const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		for (uint i = 0; i < std::min(Dim, Dim1); i++) {
			this->data[i] -= other[i];
		}
		return SELF;
	}


	template <typename T1>
	constexpr THIS_TYPE operator *= (const T1& other) {
		
		static_assert(std::is_arithmetic<T>::value,
			"Vector *= operator: RHS must be an arithmetic type or Vector type.");

		for (uint i = 0; i < Dim; i++) {
			this->data[i] *= other;
		}
		return SELF;
	}

	template <typename T1>
	constexpr THIS_TYPE operator /= (const T1& other) {

		static_assert(std::is_arithmetic<T>::value,
			"Vector /= operator: RHS must be an arithmetic type or Vector type.");

		for (uint i = 0; i < Dim; i++) {
			this->data[i] /= other;
		}
		return SELF;
	}

	// +

	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1> requires (Dim >= Dim1)
	friend constexpr const THIS_TYPE operator + (const THIS_TYPE& first, const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		return THIS_TYPE(first) += other;
	}

	// -

	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1> requires (Dim >= Dim1)
	friend constexpr const THIS_TYPE operator - (const THIS_TYPE& first, const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		return THIS_TYPE(first) -= other;
	}

	// *


	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1> requires (Dim >= Dim1)
	friend constexpr const THIS_TYPE operator * (const THIS_TYPE& first, const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		return THIS_TYPE(first) *= other;
	}

	template <typename T1, uint Dim1, typename MEMORY_STRUCTURE1>
	friend constexpr const THIS_TYPE operator / (const THIS_TYPE& first, const Vector<T1, Dim1, MEMORY_STRUCTURE1>& other) {
		return THIS_TYPE(first) /= other;
	}

	template <typename T1>
	friend constexpr const THIS_TYPE operator * (const THIS_TYPE& first, const T1& other) {
		return THIS_TYPE(first) *= other;
	}

	template <typename T1>\
	friend constexpr const THIS_TYPE operator / (const THIS_TYPE& first, const T1& other) {
		return THIS_TYPE(first) /= other;
	}

	constexpr const THIS_TYPE operator - () const {
		return THIS_TYPE( T{} ) - SELF;
	}

	constexpr const T SquaredMagnitude() const {

		T return_value = 0;
		for (uint i = 0; i < Dim; i++) {
			return_value += (data[i] * data[i]);
		}
		return return_value;
	}

	constexpr const T Magnitude() const {

		if (sizeof(T) >= sizeof(long double))
			return static_cast<T>(std::sqrtl(SquaredMagnitude()));

		else if (sizeof(T) >= sizeof(double))
			return static_cast<T>(std::sqrt(SquaredMagnitude()));

		else
			return static_cast<T>(std::sqrtf(SquaredMagnitude()));
	}
	
	inline constexpr THIS_TYPE& Normalise() {
		T inv_magnitude = static_cast<T>(FastInvSqrt(SquaredMagnitude()));
		for (uint i = 0; i < Dim; i++) {
			data[i] *= inv_magnitude;
		}
		return SELF;
	}
	
	inline constexpr const THIS_TYPE Normalised() const {
		return THIS_TYPE(SELF).Normalise();
	}

	inline constexpr const THIS_TYPE Abs() const {
		THIS_TYPE return_vector = THIS_TYPE(SELF);

		for (uint i = 0; i < Dim; i++) {
			if (return_vector.data[i] < T(0))
				return_vector.data[i] = -return_vector.data[i];
		}
		return return_vector;
	}

	template <typename T1>
	inline constexpr T Dot(const Vector<T1, Dim>& rhs) {
		T return_value = T(0);

		for (uint i = 0; i < Dim; i++) {
			return_value += data[i] * rhs[i];
		}
		return return_value;
	}

	template <typename T1>
	inline constexpr const THIS_TYPE Fill(const T1 value) {

		static_assert(std::is_arithmetic<T>::value,
			"Vector.Fill(): value must be an arithmetic type.");

		data.fill(value);
		return SELF;
	}

	/// TODO: move all long functions to .cpp file

};

inline constexpr Vector <int,1> Left {-1};
inline constexpr Vector Right {1, 0, 0};

inline constexpr Vector Up{0, 1};
inline constexpr Vector Down{0, -1};

inline constexpr Vector Back = Vector{0, 0, -1};
inline constexpr Vector Forward = Vector{0, 0, 1};

inline constexpr Vector<int, 4> Ana{0, 0, 0, 1};
inline constexpr Vector<int, 4> Kata{0, 0, 0, -1};


inline constexpr Vector Zero = Vector(0);

inline constexpr Vector One = Vector(1);

} // namespace Vectors

template<typename T>
struct VEC3_MEM_STRUCT {
	union {
		struct { T x, y, z; };
		std::array<T, 3> data { };
	};
};

template<typename T = double>
struct Vector3 : Vectors::Vector<T, 3, VEC3_MEM_STRUCT<T>> {

	using type = Vectors::Vector<T, 3, VEC3_MEM_STRUCT<T>>;

public:

	using type::Vector;

};

template<typename T>
struct VEC4_MEM_STRUCT {
	union {
		struct { T x, y, z, w; };
		std::array<T, 4> data { };
	};
};

template<typename T = double>
struct Vector4 : Vectors::Vector<T, 4, VEC4_MEM_STRUCT<T>> {

	using type = Vectors::Vector<T, 4, VEC4_MEM_STRUCT<T>>;

public:

	using type::Vector;

};