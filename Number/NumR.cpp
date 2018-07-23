#include "NumR.h"

NumR::NumR()
{
}

NumR::NumR(size_t len, size_t prec)
{
	this->bitPatLen = len;
	this->bitPatPrec = prec;
	this->bitPat = new uint32_t[len];
	for (size_t i = 0; i < len; i++)
	{
		this->bitPat[i] = 0;
	}
}

NumR::NumR(size_t len, size_t prec, int_fast32_t * bPat, bool s)
{
	this->bitPatLen = len;
	this->bitPatPrec = prec;
	this->bitPat = new uint32_t[len];
	memcpy(this->bitPat, bPat, sizeof(uint32_t)*len);
}

NumR::NumR(const NumR& opd)
{
	this->bitPatLen = opd.bitPatLen;
	this->bitPatPrec = opd.bitPatPrec;
	this->sign = opd.sign;
	this->bitPat = new uint32_t[opd.bitPatLen];
	memcpy(this->bitPat, opd.bitPat, sizeof(uint32_t)*this->bitPatLen);
}

NumR NumR::operator+(const NumR& opd) const
{
	NumR rst;

	size_t prec = (this->bitPatPrec > opd.bitPatPrec) ? (this->bitPatPrec) : (opd.bitPatPrec);
	size_t len = (this->bitPatLen + (prec - this->bitPatPrec) > opd.bitPatLen + (prec - opd.bitPatPrec)) ? (this->bitPatLen+ (prec - this->bitPatPrec)) : (opd.bitPatLen+ (prec - opd.bitPatPrec));
	// Prepare for operand bitPats
	uint32_t* opa = new uint32_t[len];
	memcpy(opa , 0, prec - this->bitPatPrec);
	memcpy(opa + (prec - this->bitPatPrec), this->bitPat, this->bitPatLen);
	uint32_t* opb = new uint32_t[len];
	memcpy(opb, 0, prec - opd.bitPatPrec);
	memcpy(opb + (prec - opd.bitPatPrec), opd.bitPat, opd.bitPatLen);
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

NumR NumR::operator-(const NumR&) const
{
	return NumR();
}

NumR NumR::operator*(const NumR&) const
{
	return NumR();
}

NumR NumR::operator/(const NumR&) const
{
	return NumR();
}

NumR NumR::operator%(const NumR&) const
{
	return NumR();
}

void NumR::operator+=(const NumR&)
{
}

void NumR::operator-=(const NumR&)
{
}

void NumR::operator*=(const NumR&)
{
}

void NumR::operator/=(const NumR&)
{
}

void NumR::operator%=(const NumR&)
{
}

bool NumR::operator==(const NumR&) const
{
	return false;
}

bool NumR::operator!=(const NumR&) const
{
	return false;
}

bool NumR::operator>(const NumR&) const
{
	return false;
}

bool NumR::operator<(const NumR&) const
{
	return false;
}

bool NumR::operator>=(const NumR&) const
{
	return false;
}

bool NumR::operator<=(const NumR&) const
{
	return false;
}

void NumR::compact()
{
	
}
