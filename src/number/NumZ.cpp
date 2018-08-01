#include "NumZ.h"

#ifdef DEBUGNUM
#include <iostream>
#include <iomanip>
using namespace std;
#define DEBUGNUM_Z
#endif

NumZ::NumZ()
{
}

NumZ::NumZ(size_t len)
{
	this->bitPatLen = len;
	this->bitPat = new uint32_t[len];
	for (size_t i = 0; i < len; i++)
	{
		this->bitPat[i] = 0u;
	}
}

NumZ::NumZ(size_t len, uint32_t *bPat, bool s)
{
	this->bitPatLen = len;
	this->bitPat = new uint32_t[len];
	this->sign = s;
	memcpy(this->bitPat, bPat, sizeof(uint32_t) * len);
}

NumZ::NumZ(const NumZ &opd)
{
	this->bitPatLen = opd.bitPatLen;
	this->sign = opd.sign;
	this->bitPat = new uint32_t[opd.bitPatLen];
	memcpy(this->bitPat, opd.bitPat, sizeof(uint32_t) * this->bitPatLen);
}

NumZ::~NumZ()
{
	delete [] this->bitPat;
}

size_t NumZ::getLen() const
{
	return this->bitPatLen;
}

bool NumZ::getSign() const
{
	return this->sign;
}

const uint32_t *NumZ::getBitPat() const
{
	return this->bitPat;
}

NumZ NumZ::operator-() const
{
	NumZ rst(*this);
	rst.sign = !rst.sign;
	return rst;
}

#ifdef DEBUGNUM_Z
#define DEBUGNUM_Z_ADD
#endif
NumZ NumZ::operator+(const NumZ &opd) const
{
	NumZ rst;

	size_t len = (this->bitPatLen > opd.bitPatLen) ? (this->bitPatLen) : (opd.bitPatLen) + 1;

	// Prepare for operand bitPats
	uint32_t *opa = new uint32_t[len];
	memcpy(opa, this->bitPat, this->bitPatLen * sizeof(uint32_t));
	for (ssize_t i = len - 1; i >= this->bitPatLen; i--)
	{
		opa[i] = 0u;
	}
#ifdef DEBUGNUM_Z_ADD
	cout << "opa = ";
	for (ssize_t i = len - 1; i >= 0; i--)
	{
		cout << setfill('0') << setw(8) << hex << opa[i] << " ";
	}
	cout << endl;
#endif
	uint32_t *opb = new uint32_t[len];
	memcpy(opb, opd.bitPat, opd.bitPatLen * sizeof(uint32_t));
	for (ssize_t i = len - 1; i >= opd.bitPatLen; i--)
	{
		opb[i] = 0u;
	}
#ifdef DEBUGNUM_Z_ADD
	cout << "opb = ";
	for (ssize_t i = len - 1; i >= 0; i--)
	{
		cout << setfill('0') << setw(8) << hex << opb[i] << " ";
	}
	cout << endl;
#endif
	rst.bitPatLen = len;

	// Compute the sign of rst
	if (this->sign == opd.sign)
	{
		rst.sign = this->sign;
		rst.bitPat = Num::bitPatAdd(opa, opb, len);
	}
	else
	{
		// Compare the bitPat of two operands
		if (Num::bitPatCompare(opa, opb, len))
		{
			rst.sign = this->sign;
			rst.bitPat = Num::bitPatSub(opa, opb, len);
		}
		else
		{
#ifdef DEBUGNUM_Z_ADD
			cout << "opa < opb" << endl;
#endif
			rst.sign = opd.sign;
			rst.bitPat = Num::bitPatSub(opb, opa, len);
		}
	}

	rst.compact();
	delete [] opa;
	delete [] opb;
	return rst;
}

NumZ NumZ::operator-(const NumZ &opd) const
{
	return (*this) + (-opd);
}

NumZ NumZ::operator*(const NumZ &opd)const
{
	uint32_t* rstBitPat = new uint32_t[this->bitPatLen + opd.bitPatLen];

	return NumZ();
}

NumZ NumZ::operator/(const NumZ &) const
{
	return NumZ();
}

NumZ NumZ::operator%(const NumZ &) const
{
	return NumZ();
}

NumZ NumZ::wrappingAdd(const NumZ &opd) const
{
	NumZ rst;

	size_t len = (this->bitPatLen > opd.bitPatLen) ? (this->bitPatLen) : (opd.bitPatLen);

	rst.bitPatLen = len;

	if (this->sign == opd.sign)
	{
		rst.sign = this->sign;
		rst.bitPat = Num::bitPatAdd(this->bitPat, opd.bitPat, len);
	}
	else
	{
		if (Num::bitPatCompare(this->bitPat, opd.bitPat, len))
		{
			rst.sign = this->sign;
			rst.bitPat = Num::bitPatSub(this->bitPat, opd.bitPat, len);
		}
		else
		{
			rst.sign = opd.sign;
			rst.bitPat = Num::bitPatSub(this->bitPat, opd.bitPat, len);
		}
	}

	return rst;
}

NumZ NumZ::wrappingSub(const NumZ &opd) const
{
	return (*this) - (-opd);
}

NumZ NumZ::wrappingMul(const NumZ &) const
{
	return NumZ();
}

NumZ NumZ::wrappingDiv(const NumZ &) const
{
	return NumZ();
}

NumZ NumZ::wrappingRem(const NumZ &) const
{
	return NumZ();
}

void NumZ::operator+=(const NumZ &)
{
}

void NumZ::operator-=(const NumZ &)
{
}

void NumZ::operator*=(const NumZ &)
{
}

void NumZ::operator/=(const NumZ &)
{
}

void NumZ::operator%=(const NumZ &)
{
}

bool NumZ::operator==(const NumZ &) const
{
	return false;
}

bool NumZ::operator!=(const NumZ &) const
{
	return false;
}

bool NumZ::operator>(const NumZ &) const
{
	return false;
}

bool NumZ::operator<(const NumZ &) const
{
	return false;
}

bool NumZ::operator>=(const NumZ &) const
{
	return false;
}

bool NumZ::operator<=(const NumZ &) const
{
	return false;
}

void NumZ::compact()
{
	size_t zeroCount = 0;
	for (size_t i = this->bitPatLen - 1; this->bitPat[i] == 0 && i > 0; i--)
	{
		zeroCount++;
	}; // count leading-zero groups

	this->bitPatLen = this->bitPatLen - zeroCount;						 // Revise bitPatLen
	uint32_t *newBitPat = new uint32_t[this->bitPatLen];				 // Create newBitPat array
	memcpy(newBitPat, this->bitPat, sizeof(uint32_t) * this->bitPatLen); // Copy valid old bitPat part to the newBitPat
	delete[] this->bitPat;												 // Delete the old array
	this->bitPat = newBitPat;											 // Let the bitPat ptr point to the new bit-pat array
}
