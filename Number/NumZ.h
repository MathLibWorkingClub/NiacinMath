#pragma once

#include "Num.h"

class NumZ : public Num
{
protected:
	size_t bitPatLen;
	uint32_t* bitPat;
	bool sign;
public:
	NumZ();
	explicit NumZ(size_t len);
	NumZ(size_t len, uint32_t* bPat, bool s);
	NumZ(const NumZ&);

	NumZ operator-() const; // Negative
	NumZ operator+(const NumZ&) const;
	NumZ operator-(const NumZ&) const;
	NumZ operator*(const NumZ&) const;
	NumZ operator/(const NumZ&) const;
	NumZ operator%(const NumZ&) const;

	NumZ wrappingAdd(const NumZ&) const;
	NumZ wrappingSub(const NumZ&) const;
	NumZ wrappingMul(const NumZ&) const;
	NumZ wrappingDiv(const NumZ&) const;
	NumZ wrappingRem(const NumZ&) const;

	void operator+=(const NumZ&);
	void operator-=(const NumZ&);
	void operator*=(const NumZ&);
	void operator/=(const NumZ&);
	void operator%=(const NumZ&);

	bool operator==(const NumZ&) const;
	bool operator!=(const NumZ&) const;
	bool operator>(const NumZ&) const;
	bool operator<(const NumZ&) const;
	bool operator>=(const NumZ&) const;
	bool operator<=(const NumZ&) const;

	void compact(); // Shorten the bitPat by remove leading-zeros
};
