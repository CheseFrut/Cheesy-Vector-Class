#pragma once

#include "Vector.h"

// --- Cariable defines for convinience --- //

// - THIS_TYPE - //

// This is a shorthand define for the base class of the current class being worked on.

#define N_DIMS
#define THIS_ARITHMETIC_TYPE
#define THIS_MEMORY_STRUCTURE
#define THIS_TYPE Vector::_VectorT<THIS_ARITHMETIC_TYPE, N_DIMS, THIS_MEMORY_STRUCTURE<THIS_ARITHMETIC_TYPE>>

// - VECTOR_TYPE - //
	
// This is a _VectorT type with the same number of dimentions and the same arithmetic type as THIS_TYPE,
// but with a variable memory structure:

#define VECTOR_TYPE_TEMPLATE template <typename T1, typename MEMORY_STRUCTURE1>
#define VECTOR_TYPE Vector::_VectorT<T1, N_DIMS, MEMORY_STRUCTURE1>

// --- Colour type --- //

#define N_DIMS 4
#define THIS_MEMORY_STRUCTURE _COLOUR4_MEM_STRUCT

template<typename T>
struct _COLOUR4_MEM_STRUCT {
	union {
		struct { T r, g, b, a; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_ARITHMETIC_TYPE float

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

		const float div255 = 1.0 / 255.0;

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

	static constexpr const THIS_TYPE Red{ 1, 0, 0, 1 };
	static constexpr const THIS_TYPE Green{ 0, 1, 0, 1 };
	static constexpr const THIS_TYPE Blue{ 0, 0, 1, 1 };

	static constexpr const THIS_TYPE Yellow{ 1, 1, 0, 1 };
	static constexpr const THIS_TYPE Cyan{ 0, 1, 1, 1 };
	static constexpr const THIS_TYPE Magenta{ 1, 0, 1, 1 };

	static constexpr const THIS_TYPE White{ 1, 1, 1, 1 };
	static constexpr const THIS_TYPE Black{ 0, 0, 0, 1 };
	static constexpr const THIS_TYPE Null, Empty{ 0, 0, 0, 0 };
};

#define THIS_ARITHMETIC_TYPE uint8_t

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

	static constexpr const THIS_TYPE Red	{ 255,   0,   0, 255 };
	static constexpr const THIS_TYPE Green	{   0, 255,   0, 255 };
	static constexpr const THIS_TYPE Blue	{   0,   0, 255, 255 };
	static constexpr const THIS_TYPE Yellow	{ 255, 255,   0, 255 };
	static constexpr const THIS_TYPE Cyan	{   0, 255, 255, 255 };
	static constexpr const THIS_TYPE Magenta{ 255,   0, 255, 255 };
	static constexpr const THIS_TYPE White	{ 255, 255, 255, 255 };
	static constexpr const THIS_TYPE Black	{   0,   0,   0, 255 };

	static constexpr const THIS_TYPE Null, Empty { 0, 0, 0, 0 };
};

// --- ColourRGB type --- //

#define N_DIMS 3
#define THIS_MEMORY_STRUCTURE _COLOUR3_MEM_STRUCT

template<typename T>
struct _COLOUR3_MEM_STRUCT {
	union {
		struct { T r, g, b; };
		std::array<T, N_DIMS> data{ };
	};
};

#define THIS_ARITHMETIC_TYPE float

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

		const float div255 = 1.0 / 255.0;

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

	static constexpr const THIS_TYPE Red	{ 1, 0, 0 };
	static constexpr const THIS_TYPE Green	{ 0, 1, 0 };
	static constexpr const THIS_TYPE Blue	{ 0, 0, 1 };
	static constexpr const THIS_TYPE Yellow	{ 1, 1, 0 };
	static constexpr const THIS_TYPE Cyan	{ 0, 1, 1 };
	static constexpr const THIS_TYPE Magenta{ 1, 0, 1 };
	static constexpr const THIS_TYPE White	{ 1, 1, 1 };

	static constexpr const THIS_TYPE Black,Null,Empty { 0, 0, 0 };
};

#define THIS_ARITHMETIC_TYPE uint8_t

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

	static constexpr const THIS_TYPE Red		{ 255,   0,   0 };
	static constexpr const THIS_TYPE Green		{   0, 255,   0 };
	static constexpr const THIS_TYPE Blue		{   0,   0, 255 };
	static constexpr const THIS_TYPE Yellow		{ 255, 255,   0 };
	static constexpr const THIS_TYPE Cyan		{   0, 255, 255 };
	static constexpr const THIS_TYPE Magenta	{ 255,   0, 255 };
	static constexpr const THIS_TYPE White		{ 255, 255, 255 };

	static constexpr const THIS_TYPE Black,Null,Empty { 0, 0, 0 };
};
#undef N_DIMS
#undef THIS_TYPE
#undef THIS_MEMORY_STRUCTURE

#undef VECTOR_TYPE
#undef VECTOR_TYPE_TEMPLATE