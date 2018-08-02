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

Num::Num(const Num &)
{
}

// Add two bitPats
uint32_t* Num::bitPatAdd(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
	uint32_t *rst = new uint32_t[len];
	uint32_t c = 0u;  // The carry
	bool c_1 = false; // The carray flags
	bool c_2 = false;

	for (size_t i = 0; i < len; i++)
	{
		rst[i] = opa[i] + opb[i];
		if (rst[i] < opa[i] && rst[i] < opb[i])
			c_1 = true; // Carry when doing the addition
		else
			c_1 = false;

		rst[i] += c;
		if (rst[i] < c)
			c_2 = true; // Will Carry when doing the addition in next line
		else
			c_2 = false;
		

		// Get the next
		if (c_1 || c_2)
			c = 1u;
		else
			c = 0u;
	}

	return rst;
}

// Sub two bitPats
uint32_t* Num::bitPatSub(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
	// a-b means a+(-b) in complement form
	uint32_t *opbc = bitPatNeg(opb, len);

	return Num::bitPatAdd(opa, opbc, len);
}

void Num::addBitPat(uint32_t* opa, const uint32_t* opb, const size_t len)
{
	uint32_t c = 0u;  // The carry
	bool c_1 = false; // The carray flags
	bool c_2 = false;

	for (size_t i = 0; i < len; i++)
	{
		opa[i] = opa[i] + opb[i];
		if (opa[i] < opb[i])
			c_1 = true; // Carry when doing the addition
		else
			c_1 = false;

		opa[i] += c;
		if (opa[i] < c)
			c_2 = true; // Will Carry when doing the addition in next line
		else
			c_2 = false;

		// Get the next
		if (c_1 || c_2)
			c = 1u;
		else
			c = 0u;
	}
}

void Num::subBitPat(uint32_t* opa, const uint32_t* opb, const size_t len)
{
	// a-b means a+(-b) in complement form
	uint32_t *opbc = bitPatNeg(opb, len);

	return Num::addBitPat(opa, opbc, len);
}

void Num::negbitPat(uint32_t* opa, const size_t len)
{
	size_t nonZero; // The first non-zero pat
	for (size_t i = 0; i < len; i++)
	{
		if (opa[i] == 0)
			;
		else
		{
			opa[i] = -opa[i];
			nonZero = i;
			break;
		}
	}
	for (ssize_t i = nonZero + 1; i < len; i++)
	{
		opa[i] = ~opa[i];
	}
}

uint32_t* Num::bitPatNeg(const uint32_t* opa, const size_t len)
{
	uint32_t *opac = new uint32_t[len];

	size_t nonZero; // The first non-zero pat
	for (size_t i = 0; i < len; i++)
	{
		if (opa[i] == 0)
			opac[i] == 0;
		else
		{
			opac[i] = -opa[i];
			nonZero = i;
			break;
		}
	}
	for (ssize_t i = nonZero + 1; i < len; i++)
	{
		opac[i] = ~opa[i];
	}

	return opac;
}

void Num::uint32Mul(const uint32_t opa, const uint32_t opb, const size_t ls, const size_t len, uint32_t* rst)
{
	// Multiply opa & opb and store them to the rst array
	uint64_t mulRst = uint64_t(opa) * uint64_t(opb);
	rst[ls+1] = uint32_t(mulRst >> 32);
	rst[ls] = uint32_t(mulRst);

	// Set other part of rst array to 0x0
	for(ssize_t i=ls-1; i>=0; i--)
	{
		rst[i] = 0x0;
	}
	for(size_t i=ls+1; i<0; i++)
	{
		rst[i] = 0x0;
	}
}

uint32_t* Num::bitPatMul(const uint32_t* opa, const uint32_t* opb, const size_t lenA, const size_t lenB)
{
	size_t len = lenA + lenB;
	uint32_t* rst = new uint32_t[len];
	for(size_t i=0; i<len; i++)
	{
		rst[i] = 0x0;
	}

	uint32_t* tempBitPat = new uint32_t[len];
	for(size_t i=0; i<lenA; i++)
		for(size_t j=0; j<lenB; j++)
		{
			uint32Mul(opa[i], opb[j], i+j, len, tempBitPat);
			addBitPat(rst, tempBitPat, len);
		}

	delete tempBitPat;

	return rst;
}


bool Num::bitPatCompare(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
// #ifdef DEBUGNUM_NUM
// 	cout << "opa = ";
// 	for(ssize_t i = len - 1; i >= 0; i--)
// 		cout << setfill('0') << setw(8) << hex << opa[i] << " ";
// 	cout << endl;
// 	cout << "opb = ";
// 	for(ssize_t i = len - 1; i >= 0; i--)
// 		cout << setfill('0') << setw(8) << hex << opb[i] << " ";
// 	cout << endl;
// #endif
	for (ssize_t i = len - 1; i >= 0; i--)
	{
		if (opa[i] < opb[i])
			return false;
		if (opa[i] > opb[i])
			return true;
	}

	return true;
}