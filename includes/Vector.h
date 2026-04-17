#pragma once

#include <array>
#include <cmath>
#include <cstdarg>
#include <ostream>
#include <type_traits>
#include <utility>

// Helper function 1/sqrt(x)

inline constexpr float FastInvSqrt(float x, unsigned int iteration_count = 1) {

	float xhalf = 0.5f * x;
	int i = *(int*)&x;              // get bits for floating value
	i = 0x5f375a86 - (i >> 1);      // gives initial guess y0
	x = *(float*)&i;                // convert bits back to float

	while (iteration_count--)
		x = x * (1.5f - xhalf * x * x); // Newton approximation equation for 1/sqrt(x)

	return x;
}

// -------- Namespace Vector -------- //

namespace Vector {

	// Any custom memory structure requires this member: 
	//	std::array<T, nDim> data
	// The memory structure allows you to for example make a vector3 structure that unions data with: struct { T x, y, z; }

	template<typename T, size_t nDim>
	struct DEFAULT_MEMORY_STRUCTURE { std::array<T, nDim> data{ }; };

	// -- Defines for readability -- //

#define THIS_TYPE _VectorT<T, nDim, MEMORY_STRUCTURE>

#define OTHER_ARITHMETIC_TYPE T1

#define OTHER_DIMENTION_COUNT nDim1
#define OTHER_MEMORY_STRUCTURE MEMORY_STRUCTURE1

#define OTHER_TYPE _VectorT<T1, nDim1, MEMORY_STRUCTURE1>

#define COMBINED_TYPE _VectorT<std::common_type_t<T,T1>, std::max<unsigned int>(nDim,nDim1)>

#define OTHER_TYPE_TEMPLATE template<typename T1, size_t nDim1, typename MEMORY_STRUCTURE1>
#define THIS_AND_OTHER_TYPE_TEMPLATE template<typename T, size_t nDim, typename MEMORY_STRUCTURE, typename T1, size_t nDim1, typename MEMORY_STRUCTURE1>

#define OTHER_ARITHMETIC_TYPE_TEMPLATE template <typename T1> requires (std::is_arithmetic<T1>::value)

	// -- The Vector struct -- //

	template <typename T, size_t nDim, class MEMORY_STRUCTURE = DEFAULT_MEMORY_STRUCTURE<T, nDim>>
	struct _VectorT : public MEMORY_STRUCTURE {

	private:

		using MEMORY_STRUCTURE::data;

		// Variadic constructor helpers

		constexpr void set_at(const size_t idx, const T value) {
			this->data[idx] = value;
		}

		template<size_t... idx, typename... Args>
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
			: std::false_type {
		};

		template <>
		struct DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY<std::void_t<decltype(std::declval<MEMORY_STRUCTURE>().data)>>
			: std::true_type {
		};

		// Assertion checks

		static_assert(std::is_arithmetic<T>::value,
			"T must be an arithmetic type.");

		static_assert(nDim > 0,
			"Vector cannot have 0 dimensions.");

		static_assert(DOES_MEMORY_STRUCTURE_CONTAIN_VALID_DATA_ARRAY<>::value,
			"Memory structure requires the following member: \nstd::array<typename T, std::size_t nDim> data");

	public:

		using valueType = T;

		static constexpr size_t dimensionCount = nDim;

		explicit constexpr _VectorT() = default;

		template<typename... Args> requires ( // Variadic constructor is used if:
			(sizeof...(Args) + 1 <= nDim) &&		// - number of args is less than or equal to number of stated dimensions.
			(std::conjunction_v<std::is_convertible<Args, T>...>)) // - if all of the given parameters are convertible to a numeric type.
			explicit constexpr _VectorT(const T first, const Args... args) : _VectorT() {
			set_from_variadic(first, args...);
		}

		// Implicitly converts to a vector with more or an equal number of dimensions:
		OTHER_TYPE_TEMPLATE requires (OTHER_DIMENTION_COUNT <= nDim)
			constexpr _VectorT(const OTHER_TYPE& other) : _VectorT() {
			for (size_t i = 0; i < OTHER_DIMENTION_COUNT; i++) {
				data[i] = static_cast<T>(other[i]);
			}
		}

		// Converts to a vector with less dimensions:
		OTHER_TYPE_TEMPLATE requires (OTHER_DIMENTION_COUNT > nDim)
			explicit constexpr _VectorT(const OTHER_TYPE& other) : _VectorT() {
			for (size_t i = 0; i < nDim; i++) {
				data[i] = static_cast<T>(other[i]);
			}
		}

		T& at(const size_t idx) {
			return data.at(idx);
		}

		const T& at(const size_t idx) const {
			return data.at(idx);
		}

		// ----- operators ----- //

		T& operator [] (const size_t idx) {
			return at(idx);
		}

		const T& operator [] (const size_t idx) const {
			return at(idx);
		}

		constexpr operator bool() const {
			for (size_t i = 0; i < nDim; i++)
				if (data[i]) return true;

			return false;
		}

		friend std::ostream& operator << (std::ostream& ostream, const THIS_TYPE& vector) {
			ostream << '(';

			for (size_t i = 0; i < vector.dimensionCount; i++) {
				if (i == 0)
					ostream << vector[i];
				else
					ostream << ", " << vector[i];
			}
			ostream << ')';

			return ostream;
		}

		// arbitrary explicit conversions between vector types

		OTHER_TYPE_TEMPLATE requires(nDim >= OTHER_DIMENTION_COUNT)
			constexpr operator OTHER_TYPE () const {
			OTHER_TYPE return_vector;
			for (size_t i = 0; i < nDim; i++) {
				return_vector[i] = (*this).data[i];
			}

			for (size_t i = OTHER_DIMENTION_COUNT; i < nDim; i++) {
				return_vector[i] = T{};
			}

			return return_vector;
		}

		OTHER_TYPE_TEMPLATE requires(nDim < OTHER_DIMENTION_COUNT)
			constexpr explicit operator OTHER_TYPE () const {
			OTHER_TYPE return_vector;
			for (size_t i = 0; i < nDim; i++) {
				return_vector[i] = (*this).data[i];
			}

			return return_vector;
		}

		// = operator

		OTHER_TYPE_TEMPLATE requires(nDim <= OTHER_DIMENTION_COUNT)
			constexpr THIS_TYPE& operator = (const OTHER_TYPE& other) {

			for (size_t i = 0; i < nDim; i++) {
				this->data[i] = other[i];
			}
			return (*this);
		}

		OTHER_TYPE_TEMPLATE requires(nDim > OTHER_DIMENTION_COUNT)
			constexpr THIS_TYPE& operator = (const OTHER_TYPE& other) {

			for (size_t i = 0; i < OTHER_DIMENTION_COUNT; i++) {
				this->data[i] = other[i];
			}

			for (size_t i = OTHER_DIMENTION_COUNT; i < nDim; i++) {
				this->data[i] = T{}; // reset to the type's default value (usually 0)
			}
			return (*this);
		}

		// - arithmetic operators - //

		// Vector += Vector

		OTHER_TYPE_TEMPLATE
			constexpr THIS_TYPE& operator += (const OTHER_TYPE& other) {
			for (size_t i = 0; i < std::min(nDim, OTHER_DIMENTION_COUNT); i++) {
				this->data[i] += other[i];
			}
			return (*this);
		}

		// Vector -= Vector

		OTHER_TYPE_TEMPLATE
			constexpr THIS_TYPE& operator -= (const OTHER_TYPE& other) {
			for (size_t i = 0; i < std::min(nDim, OTHER_DIMENTION_COUNT); i++) {
				this->data[i] -= other[i];
			}
			return (*this);
		}

		// Vector *= number

		OTHER_ARITHMETIC_TYPE_TEMPLATE
			constexpr THIS_TYPE& operator *= (const OTHER_ARITHMETIC_TYPE& value) {

			for (size_t i = 0; i < nDim; i++) {
				this->data[i] *= value;
			}
			return (*this);
		}

		// Vector /= number

		OTHER_ARITHMETIC_TYPE_TEMPLATE
			constexpr THIS_TYPE& operator /= (const OTHER_ARITHMETIC_TYPE& value) {

			for (size_t i = 0; i < nDim; i++) {
				this->data[i] /= value;
			}
			return (*this);
		}

		// non-commutative operators //

		// Vector - Vector

		OTHER_TYPE_TEMPLATE
			friend constexpr const COMBINED_TYPE operator - (const THIS_TYPE& first, const OTHER_TYPE& other) {
			return COMBINED_TYPE(first) -= other;
		}

		// Vector / number

		OTHER_ARITHMETIC_TYPE_TEMPLATE
			friend constexpr const THIS_TYPE operator / (const THIS_TYPE& first, const OTHER_ARITHMETIC_TYPE& value) {
			return THIS_TYPE(first) /= value;
		}

		// commutative operators //

		// For both addiction and multiplication, 
		// the return value ensures the most data is preserved by checking if nDim or OTHER_DIMENTION_COUNT is larger

		// Vector + Vector

		OTHER_TYPE_TEMPLATE
			friend constexpr const COMBINED_TYPE operator + (const THIS_TYPE& first, const OTHER_TYPE& other) {
			return COMBINED_TYPE(first) += other;
		}


		// Vector * number

		OTHER_ARITHMETIC_TYPE_TEMPLATE
			friend constexpr const THIS_TYPE operator * (const THIS_TYPE& vector, const OTHER_ARITHMETIC_TYPE& value) {
			return THIS_TYPE(vector) *= value;
		}

		OTHER_ARITHMETIC_TYPE_TEMPLATE
			friend constexpr const THIS_TYPE operator * (const OTHER_ARITHMETIC_TYPE& value, const THIS_TYPE& vector) {
			return THIS_TYPE(vector) *= value;
		}

		constexpr const THIS_TYPE operator - () const {
			THIS_TYPE return_vector = (*this);
			for (size_t i = 0; i < nDim; i++) {
				return_vector[i] = -return_vector[i];
			}
			return return_vector;
		}

		// Vector == Vector

		OTHER_TYPE_TEMPLATE requires (nDim >= OTHER_DIMENTION_COUNT)
			friend constexpr const bool operator == (const THIS_TYPE& first, const OTHER_TYPE& other) {

			for (size_t i = 0; i < OTHER_DIMENTION_COUNT; i++) {
				if (first[i] != other[i]) return false;
			}

			// if the first vector is larger than the other, 
			// ensure the extra dimensions of the first vector are filled with default values (0)
			for (size_t i = OTHER_DIMENTION_COUNT; i < nDim; i++) {
				if (first[i] != T{})
					return false;
			}

			return true;
		}

		OTHER_TYPE_TEMPLATE requires (nDim < OTHER_DIMENTION_COUNT)
			friend constexpr const bool operator == (const THIS_TYPE& first, const OTHER_TYPE& other) {

			for (size_t i = 0; i < nDim; i++) {
				if (first[i] != other[i]) return false;
			}

			// if the first vector is larger than the other, 
			// ensure the extra dimensions of the first vector are filled with default values (0)
			for (size_t i = nDim; i < OTHER_DIMENTION_COUNT; i++) {
				if (other[i] != T{})
					return false;
			}

			return true;
		}

		// Vector != Vector

		OTHER_TYPE_TEMPLATE
			friend constexpr const bool operator != (const THIS_TYPE& first, const OTHER_TYPE& other) {
			return !(first == other);
		}

		// functions

		/// <summary>
		/// Returns the distance of the vector squared.
		/// </summary>
		constexpr const T SquaredMagnitude() const {

			T return_value = 0;
			for (size_t i = 0; i < nDim; i++) {
				return_value += (data[i] * data[i]);
			}
			return return_value;
		}

		/// <summary>
		/// Returns the distance of the vector.
		/// </summary>
		constexpr const T Magnitude() const {

			if (sizeof(T) >= sizeof(long double))
				return static_cast<T>(std::sqrtl(SquaredMagnitude()));

			else if (sizeof(T) >= sizeof(double))
				return static_cast<T>(std::sqrt(SquaredMagnitude()));

			else
				return static_cast<T>(std::sqrtf(SquaredMagnitude()));
		}

		inline constexpr THIS_TYPE& Normalise() {

			// This block lowers bit-repression errors by, 
			// for example, turning a vector such as (23405, 2414500455027440, 59769032) 
			// into (0.00023405, 24145004.5502744, 0.59769032) before normalizing it.
			// This would give the same normalized vector as without moving the decimal place, 
			// but in the following algorithm will give a more accurate result.

#define UPPER_BOUND 10000000.0f
#define LOWER_BOUND 0.00000001f

			T largest_mag = -1;
			T lowest_mag = 1.7976931348623157E308;
			for (int i = 0; i < nDim; i++) {
				if (std::abs(data[i]) < lowest_mag)
					lowest_mag = data[i];
				else if (std::abs(data[i]) > largest_mag)
					largest_mag = data[i];
			}

			if (largest_mag > UPPER_BOUND)
				(*this) *= LOWER_BOUND;
			else if (lowest_mag < LOWER_BOUND)
				(*this) *= UPPER_BOUND;

#undef UPPER_BOUND
#undef LOWER_BOUND

			T inv_magnitude = static_cast<T>(FastInvSqrt(SquaredMagnitude()));
			for (size_t i = 0; i < nDim; i++) {
				data[i] *= inv_magnitude;
			}
			return (*this);
		}

		inline constexpr const THIS_TYPE Normalised() const {
			return THIS_TYPE((*this)).Normalise();
		}

		inline constexpr const THIS_TYPE Abs() const {
			THIS_TYPE return_vector = THIS_TYPE((*this));

			for (size_t i = 0; i < nDim; i++) {
				if (return_vector.data[i] < T(0))
					return_vector.data[i] = -return_vector.data[i];
			}

			return return_vector;
		}

		/// <summary>
		/// Returns the dot product of the current vector with another vector of the same number of dimensions.
		/// </summary>
		OTHER_TYPE_TEMPLATE requires(nDim == OTHER_DIMENTION_COUNT)
			inline constexpr const T Dot(const OTHER_TYPE& rhs) const {
			T return_value = T(0);

			for (size_t i = 0; i < nDim; i++) {
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
	};

	/// <summary>
	/// Returns the dot product of the current vector with another vector of the same number of dimensions.
	/// </summary>
	THIS_AND_OTHER_TYPE_TEMPLATE requires(nDim == OTHER_DIMENTION_COUNT)
		static inline constexpr const T Dot(const THIS_TYPE& lhs, const OTHER_TYPE& rhs) {
		return lhs.Dot(rhs);
	}

	inline constexpr const _VectorT<int, 1> Left				( -1 );
	inline constexpr const _VectorT<int, 1> Right				(  1 );
	inline constexpr const _VectorT<int, 2> Up				(  0,  1 );
	inline constexpr const _VectorT<int, 2> Down			(  0, -1 );
	inline constexpr const _VectorT<int, 3> Back		(  0,  0, -1 );
	inline constexpr const _VectorT<int, 3> Forward		(  0,  0,  1 );
	inline constexpr const _VectorT<int, 4> Ana		(  0,  0,  0,  1 );
	inline constexpr const _VectorT<int, 4> Kata	(  0,  0,  0, -1 );

	template<size_t nDim>
	static constexpr const _VectorT<int, nDim> Zero = _VectorT<int, nDim>::Fill(0);

	template<size_t nDim>
	static constexpr const _VectorT<int, nDim> One = _VectorT<int, nDim>::Fill(1);

#undef THIS_TYPE

#undef OTHER_DIMENTION_COUNT
#undef OTHER_MEMORY_STRUCTURE

#undef OTHER_TYPE
#undef OTHER_TYPE_TEMPLATE

#undef OTHER_ARITHMETIC_TYPE
#undef OTHER_ARITHMETIC_TYPE_TEMPLATE

#undef THIS_AND_OTHER_TYPE_TEMPLATE

} // namespace Vector