#pragma once
#include "Vector.h"

#define uint unsigned int
#define SELF (*this)

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

#define VECTOR_TYPE_TEMPLATE template <typename MEMORY_STRUCTURE>
#define VECTOR_TYPE Vector::_VectorT<THIS_ARITHMETIC_TYPE, N_DIMS, MEMORY_STRUCTURE>

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
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static Colour Hex8(const uint& hex) {

		const float div255 = 1.0 / 255.0;

		Colour result;

		const uint r_mask = 0xff000000;
		const uint g_mask = 0x00ff0000;
		const uint b_mask = 0x0000ff00;
		const uint a_mask = 0x000000ff;

		uint masked_r = hex & r_mask;
		uint masked_g = hex & g_mask;
		uint masked_b = hex & b_mask;
		uint masked_a = hex & a_mask;

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
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static Colour255 Hex8(const uint& hex) {

		Colour255 result;

		const uint r_mask = 0xff000000;
		const uint g_mask = 0x00ff0000;
		const uint b_mask = 0x0000ff00;
		const uint a_mask = 0x000000ff;

		uint masked_r = hex & r_mask;
		uint masked_g = hex & g_mask;
		uint masked_b = hex & b_mask;
		uint masked_a = hex & a_mask;

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
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static constexpr ColourRGB Hex6(const uint& hex) {

		const float div255 = 1.0 / 255.0;

		ColourRGB result;

		const uint r_mask = 0xff0000;
		const uint g_mask = 0x00ff00;
		const uint b_mask = 0x0000ff;

		uint masked_r = hex & r_mask;
		uint masked_g = hex & g_mask;
		uint masked_b = hex & b_mask;

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
		for (uint i = 0; i < N_DIMS; i++) {
			SELF[i] = other[i];
		}
	}

	static constexpr ColourRGB255 Hex6(const uint& hex) {

		ColourRGB255 result;

		const uint r_mask = 0xff0000;
		const uint g_mask = 0x00ff00;
		const uint b_mask = 0x0000ff;

		uint masked_r = hex & r_mask;
		uint masked_g = hex & g_mask;
		uint masked_b = hex & b_mask;

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

#undef uint
#undef SELF