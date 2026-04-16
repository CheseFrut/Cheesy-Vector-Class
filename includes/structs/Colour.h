#pragma once

#include "Vector.h"

// --- Cariable defines for convinience --- //

// - THIS_TYPE - //

// This is a shorthand define for the base class of the current class being worked on.

#define N_DIMS
#define THIS_ARITHMETIC_TYPE
#define THIS_TYPE

// - VECTOR_TYPE - //
	
// This is a _VectorT type with the same number of dimentions and the same arithmetic type as THIS_TYPE,
// but with a variable memory structure:

#define VECTOR_TYPE_TEMPLATE
#define VECTOR_TYPE

// --- Colour type --- //

#undef N_DIMS
#undef VECTOR_TYPE_TEMPLATE
#undef VECTOR_TYPE

#define N_DIMS 4
#define VECTOR_TYPE_TEMPLATE template <typename T1, typename MEMORY_STRUCTURE1>
#define VECTOR_TYPE Vector::_VectorT<T1, N_DIMS, MEMORY_STRUCTURE1>

template<typename T>
struct _COLOUR4_MEM_STRUCT {
	union {
		struct { T r, g, b, a; };
		std::array<T, N_DIMS> data{ };
	};
};

#undef THIS_ARITHMETIC_TYPE
#undef THIS_TYPE

#define THIS_ARITHMETIC_TYPE float
#define THIS_TYPE Vector::_VectorT<THIS_ARITHMETIC_TYPE, N_DIMS, _COLOUR4_MEM_STRUCT<THIS_ARITHMETIC_TYPE>>

struct Colour : public THIS_TYPE {

	using THIS_TYPE::_VectorT;

	VECTOR_TYPE_TEMPLATE
		Colour(VECTOR_TYPE other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	VECTOR_TYPE_TEMPLATE
		constexpr Colour& operator *= (const VECTOR_TYPE& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	VECTOR_TYPE_TEMPLATE
		friend const constexpr Colour operator * (const Colour& first, const VECTOR_TYPE& other) {
		return Colour(first) *= other;

	}

	static Colour Hex8(const size_t& hex) {

		const float div255 = 1.0f / 255.0f;

		Colour result;

		const size_t r_mask = 0xff000000;
		const size_t g_mask = 0x00ff0000;
		const size_t b_mask = 0x0000ff00;
		const size_t a_mask = 0x000000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;
		size_t masked_a = hex & a_mask;

		result.r = float(masked_r >> 24) * div255;
		result.g = float(masked_g >> 16) * div255;
		result.b = float(masked_b >> 8) * div255;
		result.a = float(masked_a) * div255;

		return result;
		
	}

	static const Colour Red;
	static const Colour Green;
	static const Colour Blue;
	static const Colour Yellow;
	static const Colour Cyan;
	static const Colour Magenta;
	static const Colour White;
	static const Colour Black;
	static const Colour Null, Empty;
};

inline const Colour Colour::Red			( 1, 0, 0, 1 );
inline const Colour Colour::Green		( 0, 1, 0, 1 );
inline const Colour Colour::Blue		( 0, 0, 1, 1 );
inline const Colour Colour::Yellow		( 1, 1, 0, 1 );
inline const Colour Colour::Cyan		( 0, 1, 1, 1 );
inline const Colour Colour::Magenta		( 1, 0, 1, 1 );
inline const Colour Colour::White		( 1, 1, 1, 1 );
inline const Colour Colour::Black		( 0, 0, 0, 1 );
inline const Colour Colour::Null, Colour::Empty ( 0, 0, 0, 0 );

#undef THIS_ARITHMETIC_TYPE
#undef THIS_TYPE

#define THIS_ARITHMETIC_TYPE uint8_t
#define THIS_TYPE Vector::_VectorT<THIS_ARITHMETIC_TYPE, N_DIMS, _COLOUR4_MEM_STRUCT<THIS_ARITHMETIC_TYPE>>

struct Colour255 : public THIS_TYPE {

	using THIS_TYPE::_VectorT;

	VECTOR_TYPE_TEMPLATE
		Colour255(VECTOR_TYPE other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	VECTOR_TYPE_TEMPLATE
		constexpr Colour255& operator *= (const VECTOR_TYPE& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	VECTOR_TYPE_TEMPLATE
		friend const constexpr Colour255 operator * (const Colour255& first, const VECTOR_TYPE& other) {
		return Colour255(first) *= other;

	}

	static Colour255 Hex8(const size_t& hex) {

		Colour255 result;

		const size_t r_mask = 0xff000000;
		const size_t g_mask = 0x00ff0000;
		const size_t b_mask = 0x0000ff00;
		const size_t a_mask = 0x000000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;
		size_t masked_a = hex & a_mask;

		result.r = uint8_t(masked_r >> 24);
		result.g = uint8_t(masked_g >> 16);
		result.b = uint8_t(masked_b >> 8);
		result.a = uint8_t(masked_a);

		return result;
	}

	static const Colour255 Red;
	static const Colour255 Green;
	static const Colour255 Blue;
	static const Colour255 Yellow;
	static const Colour255 Cyan;
	static const Colour255 Magenta;
	static const Colour255 White;
	static const Colour255 Black;
	static const Colour255 Null, Empty;
};

inline const Colour255 Colour255::Red		( 255,   0,   0, 255 );
inline const Colour255 Colour255::Green		(   0, 255,   0, 255 );
inline const Colour255 Colour255::Blue		(   0,   0, 255, 255 );
inline const Colour255 Colour255::Yellow	( 255, 255,   0, 255 );
inline const Colour255 Colour255::Cyan		(   0, 255, 255, 255 );
inline const Colour255 Colour255::Magenta	( 255,   0, 255, 255 );
inline const Colour255 Colour255::White		( 255, 255, 255, 255 );
inline const Colour255 Colour255::Black		(   0,   0,   0, 255 );
inline const Colour255 Colour255::Null,Colour255::Empty ( 0, 0, 0, 0 );

#undef N_DIMS
#undef VECTOR_TYPE

#undef THIS_ARITHMETIC_TYPE
#undef THIS_TYPE

#undef VECTOR_TYPE_TEMPLATE

// --- ColourRGB type --- //

#define N_DIMS 3
#define VECTOR_TYPE Vector::_VectorT<T1, N_DIMS, MEMORY_STRUCTURE1>
#define VECTOR_TYPE_TEMPLATE template <typename T1, typename MEMORY_STRUCTURE1>

template<typename T>
struct _COLOUR3_MEM_STRUCT {
	union {
		struct { T r, g, b; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_ARITHMETIC_TYPE float
#define THIS_TYPE Vector::_VectorT<THIS_ARITHMETIC_TYPE, N_DIMS, _COLOUR3_MEM_STRUCT<THIS_ARITHMETIC_TYPE>>

struct ColourRGB : public THIS_TYPE {

	using THIS_TYPE::_VectorT;

	VECTOR_TYPE_TEMPLATE
		ColourRGB(VECTOR_TYPE other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	VECTOR_TYPE_TEMPLATE
		constexpr ColourRGB& operator *= (const VECTOR_TYPE& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	VECTOR_TYPE_TEMPLATE
		friend const constexpr ColourRGB operator * (const ColourRGB& first, const VECTOR_TYPE& other) {
		return ColourRGB(first) *= other;
	}

	static constexpr const ColourRGB Hex6(const size_t& hex) {

		const float div255 = 1.0f / 255.0f;

		ColourRGB result;

		const size_t r_mask = 0xff0000;
		const size_t g_mask = 0x00ff00;
		const size_t b_mask = 0x0000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;

		result.r = float(masked_r >> 16) * div255;
		result.g = float(masked_g >> 8) * div255;
		result.b = float(masked_b) * div255;

		return result;

	}

	static const ColourRGB Red;
	static const ColourRGB Green;
	static const ColourRGB Blue;
	static const ColourRGB Yellow;
	static const ColourRGB Cyan;
	static const ColourRGB Magenta;
	static const ColourRGB White;
	static const ColourRGB Black, Null, Empty;
};

inline const ColourRGB ColourRGB::Red		( 1, 0, 0 );
inline const ColourRGB ColourRGB::Green		( 0, 1, 0 );
inline const ColourRGB ColourRGB::Blue		( 0, 0, 1 );
inline const ColourRGB ColourRGB::Yellow	( 1, 1, 0 );
inline const ColourRGB ColourRGB::Cyan		( 0, 1, 1 );
inline const ColourRGB ColourRGB::Magenta	( 1, 0, 1 );
inline const ColourRGB ColourRGB::White		( 1, 1, 1 );
inline const ColourRGB ColourRGB::Black,ColourRGB::Null,ColourRGB::Empty ( 0, 0, 0 );

#undef THIS_ARITHMETIC_TYPE
#undef THIS_TYPE

#define THIS_ARITHMETIC_TYPE uint8_t
#define THIS_TYPE Vector::_VectorT<THIS_ARITHMETIC_TYPE, N_DIMS, _COLOUR3_MEM_STRUCT<THIS_ARITHMETIC_TYPE>>

struct ColourRGB255 : public THIS_TYPE {

	using THIS_TYPE::_VectorT;

	VECTOR_TYPE_TEMPLATE
		ColourRGB255(VECTOR_TYPE other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	VECTOR_TYPE_TEMPLATE
		constexpr ColourRGB255& operator *= (const VECTOR_TYPE& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	VECTOR_TYPE_TEMPLATE
		friend const constexpr ColourRGB255 operator * (const ColourRGB255& first, const VECTOR_TYPE& other) {
		return ColourRGB255(first) *= other;

	}

	static constexpr ColourRGB255 Hex6(const size_t& hex) {

		ColourRGB255 result;

		const size_t r_mask = 0xff0000;
		const size_t g_mask = 0x00ff00;
		const size_t b_mask = 0x0000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;

		result.r = uint8_t(masked_r >> 16);
		result.g = uint8_t(masked_g >> 8);
		result.b = uint8_t(masked_b);

		return result;
	}

	static const ColourRGB255 Red;
	static const ColourRGB255 Green;
	static const ColourRGB255 Blue;
	static const ColourRGB255 Yellow;
	static const ColourRGB255 Cyan;
	static const ColourRGB255 Magenta;
	static const ColourRGB255 White;
	static const ColourRGB255 Black,Null,Empty;
};

inline const ColourRGB255 ColourRGB255::Red			( 255,   0,   0 );
inline const ColourRGB255 ColourRGB255::Green		(   0, 255,   0 );
inline const ColourRGB255 ColourRGB255::Blue		(   0,   0, 255 );
inline const ColourRGB255 ColourRGB255::Yellow		( 255, 255,   0 );
inline const ColourRGB255 ColourRGB255::Cyan		(   0, 255, 255 );
inline const ColourRGB255 ColourRGB255::Magenta		( 255,   0, 255 );
inline const ColourRGB255 ColourRGB255::White		( 255, 255, 255 );
inline const ColourRGB255 ColourRGB255::Black,ColourRGB255::Null,ColourRGB255::Empty ( 0, 0, 0 );

#undef N_DIMS
#undef VECTOR_TYPE

#undef THIS_ARITHMETIC_TYPE
#undef THIS_TYPE

#undef VECTOR_TYPE_TEMPLATE