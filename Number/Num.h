#pragma once

#include <cstdlib>
#include <cstdint>
#include <string>
#include <cstring>
//#include <NumZ.h>
//#include <NumQ.h>
//#include <NumR.h>
//#include <NumC.h>
//#include <NumV.h>

class Num
{
public:
	Num();
	Num(const Num&);

	static uint32_t* bitPatAdd(const uint32_t* opa, const uint32_t* opb, const int len); // Add two unsigned bit pat
	static uint32_t* bitPatSub(const uint32_t* opa, const uint32_t* opb, const int len); // Sub two bit unsigned bit pat, opa should be larger than opb to make this operation significant
	static bool bitPatCompare(const uint32_t* opa, const uint32_t* opb, const int len); // Compare two unsinged bit pat, return true if a>=b

};
