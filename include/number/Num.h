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

	static uint32_t* bitPatAdd(const uint32_t* opa, const uint32_t* opb, const size_t len); // Add two unsigned bit pat
	static uint32_t* bitPatSub(const uint32_t* opa, const uint32_t* opb, const size_t len); // Sub two bit unsigned bit pat, opa should be larger than opb to make this operation significant
	static bool bitPatCompare(const uint32_t* opa, const uint32_t* opb, const size_t len); // Compare two unsinged bit pat, return true if a>=b

};

#endif
