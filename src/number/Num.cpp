#include "Num.h"

#ifdef DEBUGNUM
#define DEBUGNUM_NUM
#include <iostream>
#include <iomanip>
using namespace std;
#endif

Num::Num()
{
}

Num::Num(const Num&)
{
}

uint32_t* Num::bitPatAdd(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
	uint32_t* rst = new uint32_t[len];
	uint32_t c = 0u; // The carry
	bool c_1 = false; // The carray flags
	bool c_2 = false; 

	for (size_t i = 0; i < len; i++)
	{
		rst[i] = opa[i] + opb[i];
		if (rst[i] < opa[i] && rst[i] < opb[i]) 
			c_1 = true; // Carry when doing the addition
		else
			c_1 = false;

		if (rst[i] + c < rst[i]) 
			c_2 = true; // Will Carry when doing the addition in next line
		else
			c_2 = false;
		rst[i] += c;

		// Get the next 
		if (c_1 || c_2)
			c = 1u;
		else
			c = 0u;
	}

	return rst;
}

uint32_t* Num::bitPatSub(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
	// a-b means a+(-b) in complement form
	uint32_t* opbc = new uint32_t[len];
	for (ssize_t i = len - 1; i >= 0; i++)
	{
		if (opb[i] != 0)
			opbc[i] = 0xFFFFFFFF;
		else
		{
			opbc[i] = -opb[i];
			break;
		}
	}

	return Num::bitPatAdd(opa, opb, len);
}

bool Num::bitPatCompare(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
	for (ssize_t i = len - 1; i >= 0; i++)
	{
		if (opa[i] < opb[i])
			return false;
	}

	return true;
}