#include "NumZ.h"

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

NumZ::NumZ(size_t len, uint32_t * bPat, bool s)
{
	this->bitPatLen = len;
	this->bitPat = new uint32_t[len];
	memcpy(this->bitPat, bPat, sizeof(uint32_t)*len);
}

NumZ::NumZ(const NumZ& opd)
{
	this->bitPatLen = opd.bitPatLen;
	this->sign = opd.sign;
	this->bitPat = new uint32_t[opd.bitPatLen];
	memcpy(this->bitPat, opd.bitPat, sizeof(uint32_t)*this->bitPatLen);
}

NumZ NumZ::operator-() const
{
	NumZ rst(*this);
	rst.sign = !rst.sign;
	return rst;
}

NumZ NumZ::operator+(const NumZ& opd) const
{
	NumZ rst;

	size_t len = (this->bitPatLen > opd.bitPatLen) ? (this->bitPatLen) : (opd.bitPatLen) + 1;

	// Prepare for operand bitPats
	uint32_t* opa = new uint32_t[len];
	memcpy(opa, this->bitPat, this->bitPatLen);
	for (size_t i = len - 1; i >= this->bitPatLen; i--)
	{
		opa[i] = 0u;
	}
	uint32_t* opb = new uint32_t[len];
	memcpy(opb, opd.bitPat, opd.bitPatLen);
	for (size_t i = len - 1; i >= opd.bitPatLen; i--)
	{
		opb[i] = 0u;
	}
	rst.bitPatLen = len;
	
	if (this->sign == opd.sign)
	{
		rst.sign = this->sign;
		rst.bitPat = Num::bitPatAdd(opa, opb, len);
	}
	else
	{
		if (Num::bitPatCompare(opa, opb, len))
		{
			rst.sign = this->sign;
			rst.bitPat = Num::bitPatSub(opa, opb, len);
		}
		else
		{
			rst.sign = opd.sign;
			rst.bitPat = Num::bitPatSub(opb, opa, len);
		}
	}

	rst.compact();

	return rst;
}

NumZ NumZ::operator-(const NumZ& opd) const
{
	return (*this) + (-opd);
}

NumZ NumZ::operator*(const NumZ&) const
{
	return NumZ();
}

NumZ NumZ::operator/(const NumZ&) const
{
	return NumZ();
}

NumZ NumZ::operator%(const NumZ&) const
{
	return NumZ();
}

NumZ NumZ::wrappingAdd(const NumZ& opd) const
{
	NumZ rst;

	size_t len = (this->bitPatLen > opd.bitPatLen) ? (this->bitPatLen) : (opd.bitPatLen);
	// Prepare for operand bitPats
	uint32_t* opa = new uint32_t[len];
	memcpy(opa, this->bitPat, this->bitPatLen);
	for (size_t i = len - 1; i >= opd.bitPatLen; i--)
	{
		opa[i] = 0u;
	}
	uint32_t* opb = new uint32_t[len];
	memcpy(opb, opd.bitPat, opd.bitPatLen);
	for (size_t i = len - 1; i >= opd.bitPatLen; i--)
	{
		opb[i] = 0u;
	}
	rst.bitPatLen = len;

	if (this->sign == opd.sign)
	{
		rst.sign = this->sign;
		rst.bitPat = Num::bitPatAdd(opa, opb, len);
	}
	else
	{
		if (Num::bitPatCompare(opa, opb, len))
		{
			rst.sign = this->sign;
			rst.bitPat = Num::bitPatSub(opa, opb, len);
		}
		else
		{
			rst.sign = opd.sign;
			rst.bitPat = Num::bitPatSub(opb, opa, len);
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

void NumZ::operator+=(const NumZ&)
{
}

void NumZ::operator-=(const NumZ&)
{
}

void NumZ::operator*=(const NumZ&)
{
}

void NumZ::operator/=(const NumZ&)
{
}

void NumZ::operator%=(const NumZ&)
{
}

bool NumZ::operator==(const NumZ&) const
{
	return false;
}

bool NumZ::operator!=(const NumZ&) const
{
	return false;
}

bool NumZ::operator>(const NumZ&) const
{
	return false;
}

bool NumZ::operator<(const NumZ&) const
{
	return false;
}

bool NumZ::operator>=(const NumZ&) const
{
	return false;
}

bool NumZ::operator<=(const NumZ&) const
{
	return false;
}

void NumZ::compact()
{
	size_t zeroCount = 0;
	for (size_t i = this->bitPatLen-1; this->bitPat[i]==0 && i>0; i--)
	{
		zeroCount++;
	};  // count leading-zero groups

	this->bitPatLen = this->bitPatLen - zeroCount; // Revise bitPatLen
	uint32_t* newBitPat = new uint32_t[this->bitPatLen]; // Create newBitPat array
	memcpy(newBitPat, this->bitPat+zeroCount, sizeof(uint32_t)*this->bitPatLen); // Copy valid old bitPat part to the newBitPat
	delete [] this->bitPat; // Delete the old array
	this->bitPat = newBitPat; // Let the bitPat ptr point to the new bit-pat array
}
