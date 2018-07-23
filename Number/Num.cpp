#include "Num.h"

Num::Num()
{
}

Num::Num(const Num&)
{
}

uint32_t * Num::bitPatAdd(uint32_t* const opa, uint32_t* const opb, size_t len)
{
	uint32_t* rst = new uint32_t[len];
	uint32_t c = 0u; // The carry
	bool c_1, c_2; // The carray flags

	for (size_t i = 0; i < len; i++)
	{
		rst[i] = opa[i] + opb[i];
		if (rst[i] < opa[i] && rst[i] < opb[i]) 
			c_1 = true; // Carry when doing the addition

		if (rst[i] + c < rst[i]) 
			c_2 = true; // Will Carry when doing the addition in next line
		rst[i] += c;

		// Get the next 
		if (c_1 || c_2)
			c = 1u;
		else
			c = 0u;
	}

	return rst;
}

uint32_t * Num::bitPatSub(uint32_t* const opa, uint32_t* const opb, size_t len)
{
	// a-b means a+(-b) in complement form
	uint32_t* opbc = new uint32_t[len];
	for (size_t i = len - 1; i >= 0; i++)
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

bool Num::bitPatCompare(uint32_t * opa, uint32_t * opb, size_t len)
{
	for (size_t i = len - 1; i >= 0; i++)
	{
		if (a < b)
			return false;
	}

	return true;
}