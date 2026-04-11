#pragma once

#include "defines.h"
#include "FastInvSqrt.h"
#include <array>
#include <cmath>
#include <cstdarg>
#include <ostream>
#include <type_traits>
#include <utility>

namespace Vector {

	// The memory structure allows you to for example make a vector3 structure that unions the data array with struct { T x, y, z; }
	// Any custom memory structure requires a member data of type std::array<T, nDim>
	template<typename T, uint nDim>
	struct DEFAULT_MEMORY_STRUCTURE {
		std::array<T, nDim> data { };
	};

template <typename T = double, uint nDim = 3, class MEMORY_STRUCTURE = DEFAULT_MEMORY_STRUCTURE<T, nDim>> 
struct _VectorT : public MEMORY_STRUCTURE {

private:

	#define THIS_TYPE _VectorT<T, nDim, MEMORY_STRUCTURE>

	using MEMORY_STRUCTURE::data;

	// Variadic constructor helpers

	constexpr void set_at(uint idx, const T& value) {
		this->data[idx] = value;
	}

	template<uint... idx, typename... Args>
	constexpr void set_from_variadic_indexer(std::index_sequence<idx...>, Args&&... args) {
		((set_at(idx, args)), ...);
	}

	template<typename... Args>
	constexpr void set_from_variadic(Args&&... args) {
		set_from_variadic_indexer(std::make_index_sequence<sizeof ... (Args)>{}, std::forward<Args>(args)...);
	}

	// Check if MEMORY_STRUCTURE has a member std::array<T, nDim> called data

	template <typename = std::void_t<>>
	struct DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY 
		: std::false_type { };

	template <>
	struct DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY<std::void_t<decltype(std::declval<MEMORY_STRUCTURE>().data)>>
		: std::true_type { };

	// Assertion checks

	static_assert(std::is_arithmetic<T>::value,
		"T must be an arithmetic type.");

	static_assert(nDim > 0,
		"Vector cannot have 0 dimensions.");

	static_assert(DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY<>::value,
		"Memory structure requires the following member: \nstd::array<typename T, std::size_t nDim> data");

public:

	using valueType = T;

	static constexpr uint dimensionCount = nDim;

	explicit constexpr _VectorT() = default;

	template<typename... Args> requires ( // Variadic constructor is used if:
		(sizeof...(Args) + 1 <= nDim) &&		// - number of args is less than or equal to number of stated dimensions.
		(std::conjunction_v<std::is_convertible<Args, T>...>)) // - if all of the given parameters are convertible to a numeric type.
	explicit constexpr _VectorT(T first, Args... args) : _VectorT() {
		set_from_variadic(first, args...);
	}

// Defines for readability

#define OTHER_ARITHMETIC_TYPE T1
#define OTHER_ARITHMETIC_TYPE_TEMPLATE template <typename T1> requires (std::is_arithmetic<T1>::value)

#define OTHER_DIMENTION_COUNT nDim1
#define OTHER_MEMORY_STRUCTURE MEMORY_STRUCTURE1

#define OTHER_TYPE _VectorT<T1, nDim1, MEMORY_STRUCTURE1>
#define OTHER_TYPE_TEMPLATE template<typename T1, uint nDim1, typename MEMORY_STRUCTURE1>

	// Converts to a vector with more or an equal number of dimensions. 
	OTHER_TYPE_TEMPLATE requires (OTHER_DIMENTION_COUNT <= nDim)
	explicit constexpr _VectorT(const OTHER_TYPE& other) : _VectorT() {
		for (uint i = 0; i < OTHER_DIMENTION_COUNT; i++) {
			data[i] = static_cast<T>(other[i]);
		}
	}

	// Converts to a vector with less dimensions. This is explicit to avoid implicit loss of data.
	OTHER_TYPE_TEMPLATE requires (OTHER_DIMENTION_COUNT > nDim)
	explicit constexpr _VectorT(const OTHER_TYPE& other) : _VectorT() {
		for (uint i = 0; i < nDim; i++) {
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
		for (uint i = 0; i < nDim; i++)
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

	// = operator

	OTHER_TYPE_TEMPLATE
	constexpr THIS_TYPE& operator = (const OTHER_TYPE& other) {
		for (uint i = 0; i < OTHER_DIMENTION_COUNT; i++) {
			this->data[i] = other[i];
		}
		return SELF;
	}

	// arithmetic operators

	OTHER_TYPE_TEMPLATE
	constexpr THIS_TYPE& operator *= (const OTHER_TYPE& other) {
		for (uint i = 0; i < std::min(nDim, OTHER_DIMENTION_COUNT); i++) {
			this->data[i] *= other[i];
		}
		return SELF;
	}

	OTHER_TYPE_TEMPLATE
	constexpr THIS_TYPE& operator /= (const OTHER_TYPE& other) {
		for (uint i = 0; i < std::min(nDim, OTHER_DIMENTION_COUNT); i++) {
			this->data[i] /= other[i];
		}
		return SELF;
	}

	OTHER_TYPE_TEMPLATE
	constexpr THIS_TYPE& operator += (const OTHER_TYPE& other) {
		for (uint i = 0; i < std::min(nDim, OTHER_DIMENTION_COUNT); i++) {
			this->data[i] += other[i];
		}
		return SELF;
	}

	OTHER_TYPE_TEMPLATE
	constexpr THIS_TYPE& operator -= (const OTHER_TYPE& other) {
		for (uint i = 0; i < std::min(nDim, OTHER_DIMENTION_COUNT); i++) {
			this->data[i] -= other[i];
		}
		return SELF;
	}

	OTHER_ARITHMETIC_TYPE_TEMPLATE
	constexpr THIS_TYPE& operator *= (const OTHER_ARITHMETIC_TYPE& value) {

		for (uint i = 0; i < nDim; i++) {
			this->data[i] *= value;
		}
		return SELF;
	}

	OTHER_ARITHMETIC_TYPE_TEMPLATE
	constexpr THIS_TYPE& operator /= (const OTHER_ARITHMETIC_TYPE& value) {

		for (uint i = 0; i < nDim; i++) {
			this->data[i] /= value;
		}
		return SELF;
	}

	// non-commutative operators

	OTHER_TYPE_TEMPLATE
	friend constexpr const THIS_TYPE operator - (const THIS_TYPE& first, const OTHER_TYPE& other) {
		return THIS_TYPE(first) -= other;
	}

	OTHER_TYPE_TEMPLATE
	friend constexpr const THIS_TYPE operator / (const THIS_TYPE& first, const OTHER_TYPE& other) {
		return THIS_TYPE(first) /= other;
	}

	OTHER_ARITHMETIC_TYPE_TEMPLATE
	friend constexpr const THIS_TYPE operator / (const THIS_TYPE& first, const OTHER_ARITHMETIC_TYPE& value) {
		return THIS_TYPE(first) /= value;
	}

	// commutative operators

	// For both addiction and multiplication, 
	// the return value ensures the most data is preserved by checking if nDim or OTHER_DIMENTION_COUNT is larger

	// +

	OTHER_TYPE_TEMPLATE requires (nDim >= OTHER_DIMENTION_COUNT)
	friend constexpr const THIS_TYPE operator + (const THIS_TYPE& first, const OTHER_TYPE& other) {
		return THIS_TYPE(first) += other;
	}

	OTHER_TYPE_TEMPLATE requires (nDim < OTHER_DIMENTION_COUNT)
	friend constexpr const OTHER_TYPE operator + (const THIS_TYPE& first, const OTHER_TYPE& other) {
		return OTHER_TYPE(other) += first;
	}

	// *

	OTHER_TYPE_TEMPLATE requires (nDim >= OTHER_DIMENTION_COUNT)
	friend constexpr const THIS_TYPE operator * (const THIS_TYPE& first, const OTHER_TYPE& other) {
		return THIS_TYPE(first) *= other;
	}

	OTHER_TYPE_TEMPLATE requires (nDim < OTHER_DIMENTION_COUNT)
	friend constexpr const OTHER_TYPE operator * (const THIS_TYPE& first, const OTHER_TYPE& other) {
		return OTHER_TYPE(other) *= first;
	}

	OTHER_ARITHMETIC_TYPE_TEMPLATE
	friend constexpr const THIS_TYPE operator * (const THIS_TYPE& vector, const OTHER_ARITHMETIC_TYPE& value) {
		return THIS_TYPE(vector) *= value;
	}

	constexpr const THIS_TYPE operator - () const {
		THIS_TYPE return_vector = SELF;
		for (uint i = 0; i < nDim; i++) {
			return_vector[i] = -return_vector[i];
		}
		return return_vector;
	}

	constexpr const T SquaredMagnitude() const {

		T return_value = 0;
		for (uint i = 0; i < nDim; i++) {
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
		for (uint i = 0; i < nDim; i++) {
			data[i] *= inv_magnitude;
		}
		return SELF;
	}
	
	inline constexpr const THIS_TYPE Normalised() const {
		return THIS_TYPE(SELF).Normalise();
	}

	inline constexpr const THIS_TYPE Abs() const {
		THIS_TYPE return_vector = THIS_TYPE(SELF);

		for (uint i = 0; i < nDim; i++) {
			if (return_vector.data[i] < T(0))
				return_vector.data[i] = -return_vector.data[i];
		}
		return return_vector;
	}

	template <typename OTHER_ARITHMETIC_TYPE>
	inline constexpr T Dot(const _VectorT<OTHER_ARITHMETIC_TYPE, nDim>& rhs) {
		T return_value = T(0);

		for (uint i = 0; i < nDim; i++) {
			return_value += data[i] * rhs[i];
		}
		return return_value;
	}

	OTHER_ARITHMETIC_TYPE_TEMPLATE
	static inline constexpr const THIS_TYPE Fill(const OTHER_ARITHMETIC_TYPE value) {

		THIS_TYPE temp;

		temp.data.fill(static_cast<T>(value));
		return temp;
	}

#undef THIS_TYPE
#undef OTHER_TYPE_TEMPLATE
#undef OTHER_TYPE

};

inline constexpr const _VectorT<int,1> Left  {-1};
inline constexpr const _VectorT<int,1> Right { 1};

inline constexpr const _VectorT<int,2> Up   {0,  1};
inline constexpr const _VectorT<int,2> Down {0, -1};

inline constexpr const _VectorT<int,3> Back    {0, 0, -1};
inline constexpr const _VectorT<int,3> Forward {0, 0,  1};

inline constexpr const _VectorT<int,4> Ana  {0, 0, 0,  1};
inline constexpr const _VectorT<int,4> Kata {0, 0, 0, -1};

template<uint nDim>
static constexpr const _VectorT<int,nDim> Zero = _VectorT<int,nDim>::Fill(0);

template<uint nDim>
static constexpr const _VectorT<int,nDim> One = _VectorT<int,nDim>::Fill(1);

} // namespace Vectors