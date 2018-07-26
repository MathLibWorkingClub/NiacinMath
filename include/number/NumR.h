#pragma once

#include "Num.h"

class NumR : public Num
{
protected:
	size_t bitPatLen;
	size_t bitPatPrec;
	uint32_t* bitPat;
	bool sign;
public:
	NumR();
	explicit NumR(size_t len, size_t prec);
	NumR(size_t len, size_t prec, int_fast32_t* bPat, bool s);
	NumR(const NumR&);

	NumR operator+(const NumR&) const;
	NumR operator-(const NumR&) const;
	NumR operator*(const NumR&) const;
	NumR operator/(const NumR&) const;
	NumR operator%(const NumR&) const;

	void operator+=(const NumR&);
	void operator-=(const NumR&);
	void operator*=(const NumR&);
	void operator/=(const NumR&);
	void operator%=(const NumR&);

	bool operator==(const NumR&) const;
	bool operator!=(const NumR&) const;
	bool operator>(const NumR&) const;
	bool operator<(const NumR&) const;
	bool operator>=(const NumR&) const;
	bool operator<=(const NumR&) const;

	void compact(); // Shorten the bitPat by remove leading-zeros
};
