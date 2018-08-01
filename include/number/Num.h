#ifndef NUM_H
#define NUM_H

#include <cstdlib>
#include <cstdint>
#include <cstring>


class Num
{
public:
	Num();
	Num(const Num&);

	// Binary Operations
	static uint32_t* bitPatAdd(const uint32_t* opa, const uint32_t* opb, const size_t len); // Add two unsigned bit pat
	static uint32_t* bitPatSub(const uint32_t* opa, const uint32_t* opb, const size_t len); // Sub two bit unsigned bit pat, opa should be larger than opb to make this operation significant
	static uint32_t* bitPatMul(const uint32_t* opa, const uint32_t* opb, const size_t lenA, const size_t lenB);

	// Operations change one of the operands
	static void addBitPat(uint32_t* opa, const uint32_t* opb, const size_t len); // Add opb to opa (+=)
	static void subBitPat(uint32_t* opa, const uint32_t* opb, const size_t len); // Sub opb from opa (-=)
	
	// Unary Operations
	static void negbitPat(uint32_t* opa, const size_t len); //
	static uint32_t* bitPatNeg(const uint32_t* opa, const size_t);

	static uint32_t* uint32Mul(const uint32_t opa, const uint32_t opb, const size_t ls);
	// Auxiliary Operations, const uint32_t opb, const size_t ls); // Mul uint32_t opa by a uint32_t opb and left shift ls groups;

	// 

	static bool bitPatCompare(const uint32_t* opa, const uint32_t* opb, const size_t len); // Compare two unsinged bit pat, return true if a>=b
};

#endif
