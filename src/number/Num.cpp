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

uint32_t *Num::bitPatAdd(const uint32_t* opa, const uint32_t* opb, const size_t len)
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

uint32_t *Num::bitPatSub(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
	// a-b means a+(-b) in complement form
	uint32_t *opbc = new uint32_t[len];

	size_t nonZero; // The first non-zero pat
	for (size_t i = 0; i < len; i++)
	{
		if (opb[i] == 0)
			opbc[i] == 0;
		else
		{
			opbc[i] = -opb[i];
			nonZero = i;
			break;
		}
	}
	for (ssize_t i = nonZero + 1; i < len; i++)
	{
		opbc[i] = ~opb[i];
	}

	return Num::bitPatAdd(opa, opbc, len);
}

bool Num::bitPatCompare(const uint32_t* opa, const uint32_t* opb, const size_t len)
{
#ifdef DEBUGNUM_NUM
	cout << "opa = ";
	for(ssize_t i = len - 1; i >= 0; i--)
		cout << setfill('0') << setw(8) << hex << opa[i] << " ";
	cout << endl;
	cout << "opb = ";
	for(ssize_t i = len - 1; i >= 0; i--)
		cout << setfill('0') << setw(8) << hex << opb[i] << " ";
	cout << endl;
#endif
	for (ssize_t i = len - 1; i >= 0; i--)
	{
#ifdef DEBUGNUM_NUM
	cout << "i = " << i << endl;
	cout << "a = " << opa[i] << endl;
	cout << "b = " << opb[i] << endl;
#endif
		if (opa[i] < opb[i])
			return false;
		if (opa[i] > opb[i])
			return true;
	}

	return true;
}