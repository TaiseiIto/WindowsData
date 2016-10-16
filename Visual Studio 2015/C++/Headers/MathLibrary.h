#ifndef MATHLIBRARY
#define MATHLIBRARY
#include<string>

namespace MathLibrary
{
	class Bits;
	class NaturalNumber;
	class Integer;
	class Fraction;
	class ComplexNumber;

	typedef unsigned int BitsDataType;
	typedef size_t BitsSizeType;

	class Bits
	{
	#ifdef MATHLIBRARY_DEBUG
	public:
	#else
	private:
	#endif
		MathLibrary::BitsDataType *data;
		MathLibrary::BitsSizeType size;
	public:
		#ifdef MATHLIBRARY_DEBUG
		std::string getBitTest(MathLibrary::BitsSizeType position)const;
		#endif
		Bits(void);
		Bits(MathLibrary::BitsSizeType size);
		Bits(std::string data);
		Bits(const MathLibrary::Bits &object);
		~Bits();
		bool getBit(MathLibrary::BitsSizeType position)const;
		void setBit(MathLibrary::BitsSizeType position, bool value);
		MathLibrary::BitsSizeType getSize(void)const;
		void setSize(MathLibrary::BitsSizeType size);
		MathLibrary::Bits operator=(MathLibrary::Bits operand);
		MathLibrary::Bits operator=(std::string operand);
		MathLibrary::Bits operator~(void)const;
		MathLibrary::Bits operator&(MathLibrary::Bits operand)const;
		MathLibrary::Bits operator|(MathLibrary::Bits operand)const;
		MathLibrary::Bits operator^(MathLibrary::Bits operand)const;
		MathLibrary::Bits operator<<(MathLibrary::BitsSizeType operand)const;
		MathLibrary::Bits operator>>(MathLibrary::BitsSizeType operand)const;
		MathLibrary::Bits operator&=(MathLibrary::Bits operand);
		MathLibrary::Bits operator|=(MathLibrary::Bits operand);
		MathLibrary::Bits operator^=(MathLibrary::Bits operand);
		MathLibrary::Bits operator<<=(MathLibrary::BitsSizeType operand);
		MathLibrary::Bits operator>>=(MathLibrary::BitsSizeType operand);
		bool operator==(MathLibrary::Bits operand)const;
		bool operator!=(MathLibrary::Bits operand)const;
		operator std::string(void)const;
		friend std::istream &operator>>(std::istream &is, MathLibrary::Bits &bits);
		friend std::ostream &operator<<(std::ostream &os, const MathLibrary::Bits &bits);
	};

	class NaturalNumber
	{
	private:
		MathLibrary::Bits bits;
	#ifdef MATHLIBRARY_DEBUG
	public:
	#else
	private:
	#endif
		MathLibrary::Bits getBits(void)const;
		void setBits(MathLibrary::Bits bits);
		void cutExtraZeros(void);
	public:
		NaturalNumber(void);
		NaturalNumber(MathLibrary::Bits data);
		NaturalNumber(const MathLibrary::NaturalNumber &object);
		MathLibrary::NaturalNumber operator=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator=(MathLibrary::Integer operand);
		MathLibrary::NaturalNumber operator=(MathLibrary::Fraction operand);
		MathLibrary::NaturalNumber operator=(MathLibrary::ComplexNumber operand);
		MathLibrary::NaturalNumber operator=(MathLibrary::Bits operand);
		MathLibrary::NaturalNumber operator=(std::string operand);
		MathLibrary::NaturalNumber operator~(void)const;
		MathLibrary::NaturalNumber operator&(MathLibrary::NaturalNumber operand)const;
		MathLibrary::NaturalNumber operator&(MathLibrary::Bits operand)const;
		MathLibrary::NaturalNumber operator|(MathLibrary::NaturalNumber operand)const;
		MathLibrary::NaturalNumber operator|(MathLibrary::Bits operand)const;
		MathLibrary::NaturalNumber operator^(MathLibrary::NaturalNumber operand)const;
		MathLibrary::NaturalNumber operator^(MathLibrary::Bits operand)const;
		MathLibrary::NaturalNumber operator<<(MathLibrary::BitsSizeType operand)const;
		MathLibrary::NaturalNumber operator>>(MathLibrary::BitsSizeType operand)const;
		MathLibrary::NaturalNumber operator+(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Integer operator+(MathLibrary::Integer operand)const;
		MathLibrary::Fraction operator+(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator+(MathLibrary::ComplexNumber operand)const;
		MathLibrary::NaturalNumber operator-(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Integer operator-(MathLibrary::Integer operand)const;
		MathLibrary::Fraction operator-(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator-(MathLibrary::ComplexNumber operand)const;
		MathLibrary::NaturalNumber operator*(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Integer operator*(MathLibrary::Integer operand)const;
		MathLibrary::Fraction operator*(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator*(MathLibrary::ComplexNumber operand)const;
		MathLibrary::NaturalNumber operator/(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Integer operator/(MathLibrary::Integer operand)const;
		MathLibrary::Fraction operator/(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator/(MathLibrary::ComplexNumber operand)const;
		MathLibrary::NaturalNumber operator%(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Integer operator%(MathLibrary::Integer operand)const;
		MathLibrary::NaturalNumber operator++(void);
		MathLibrary::NaturalNumber operator++(int);
		MathLibrary::NaturalNumber operator--(void);
		MathLibrary::NaturalNumber operator--(int);
		MathLibrary::NaturalNumber operator&=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator&=(MathLibrary::Bits operand);
		MathLibrary::NaturalNumber operator|=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator|=(MathLibrary::Bits operand);
		MathLibrary::NaturalNumber operator^=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator^=(MathLibrary::Bits operand);
		MathLibrary::NaturalNumber operator<<=(MathLibrary::BitsSizeType operand);
		MathLibrary::NaturalNumber operator>>=(MathLibrary::BitsSizeType operand);
		MathLibrary::NaturalNumber operator+=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator+=(MathLibrary::Integer operand);
		MathLibrary::NaturalNumber operator+=(MathLibrary::Fraction operand);
		MathLibrary::NaturalNumber operator+=(MathLibrary::ComplexNumber operand);
		MathLibrary::NaturalNumber operator-=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator-=(MathLibrary::Integer operand);
		MathLibrary::NaturalNumber operator-=(MathLibrary::Fraction operand);
		MathLibrary::NaturalNumber operator-=(MathLibrary::ComplexNumber operand);
		MathLibrary::NaturalNumber operator*=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator*=(MathLibrary::Integer operand);
		MathLibrary::NaturalNumber operator*=(MathLibrary::Fraction operand);
		MathLibrary::NaturalNumber operator*=(MathLibrary::ComplexNumber operand);
		MathLibrary::NaturalNumber operator/=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator/=(MathLibrary::Integer operand);
		MathLibrary::NaturalNumber operator/=(MathLibrary::Fraction operand);
		MathLibrary::NaturalNumber operator/=(MathLibrary::ComplexNumber operand);
		MathLibrary::NaturalNumber operator%=(MathLibrary::NaturalNumber operand);
		MathLibrary::NaturalNumber operator%=(MathLibrary::Integer operand);
		bool operator==(MathLibrary::NaturalNumber operand)const;
		bool operator==(MathLibrary::Integer operand)const;
		bool operator==(MathLibrary::Fraction operand)const;
		bool operator==(MathLibrary::ComplexNumber operand)const;
		bool operator!=(MathLibrary::NaturalNumber operand)const;
		bool operator!=(MathLibrary::Integer operand)const;
		bool operator!=(MathLibrary::Fraction operand)const;
		bool operator!=(MathLibrary::ComplexNumber operand)const;
		bool operator>(MathLibrary::NaturalNumber operand)const;
		bool operator>(MathLibrary::Integer operand)const;
		bool operator>(MathLibrary::Fraction operand)const;
		bool operator<(MathLibrary::NaturalNumber operand)const;
		bool operator<(MathLibrary::Integer operand)const;
		bool operator<(MathLibrary::Fraction operand)const;
		bool operator>=(MathLibrary::NaturalNumber operand)const;
		bool operator>=(MathLibrary::Integer operand)const;
		bool operator>=(MathLibrary::Fraction operand)const;
		bool operator<=(MathLibrary::NaturalNumber operand)const;
		bool operator<=(MathLibrary::Integer operand)const;
		bool operator<=(MathLibrary::Fraction operand)const;
		bool operator!(void)const;
		operator MathLibrary::Integer(void)const;
		operator MathLibrary::Fraction(void)const;
		operator MathLibrary::ComplexNumber(void)const;
		operator std::string(void)const;
		friend std::istream &operator>>(std::istream &is, MathLibrary::NaturalNumber &naturalNumber);
		friend std::ostream &operator<<(std::ostream &os, const MathLibrary::NaturalNumber &naturalNumber);
	};

	typedef bool Sign;
	const Sign plus = true;
	const Sign minus = false;
	
	class Integer
	{
	private:
		MathLibrary::Sign sign;
		MathLibrary::NaturalNumber absoluteValue;
	#ifdef MATHLIBRARY_DEBUG
	public:
	#else
	private:
	#endif
		MathLibrary::Sign getSign(void)const;
		MathLibrary::NaturalNumber getAbsoluteValue(void)const;
		void setSign(MathLibrary::Sign sign);
		void setAbsoluteValue(MathLibrary::NaturalNumber absoluteValue);
	public:
		Integer(void);
		Integer(MathLibrary::Sign sign, MathLibrary::NaturalNumber absoluteValue);
		Integer(const MathLibrary::Integer &object);
		MathLibrary::Integer operator=(MathLibrary::Integer operand);
		MathLibrary::Integer operator=(MathLibrary::NaturalNumber operand);
		MathLibrary::Integer operator=(MathLibrary::Fraction operand);
		MathLibrary::Integer operator=(MathLibrary::ComplexNumber operand);
		MathLibrary::Integer operator=(std::string operand);
		MathLibrary::Integer operator+(MathLibrary::Integer operand)const;
		MathLibrary::Integer operator+(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator+(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator+(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Integer operator-(MathLibrary::Integer operand)const;
		MathLibrary::Integer operator-(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator-(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator-(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Integer operator*(MathLibrary::Integer operand)const;
		MathLibrary::Integer operator*(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator*(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator*(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Integer operator/(MathLibrary::Integer operand)const;
		MathLibrary::Integer operator/(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator/(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator/(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Integer operator%(MathLibrary::Integer operand)const;
		MathLibrary::Integer operator%(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Integer operator+=(MathLibrary::Integer operand);
		MathLibrary::Integer operator+=(MathLibrary::NaturalNumber operand);
		MathLibrary::Integer operator+=(MathLibrary::Fraction operand);
		MathLibrary::Integer operator+=(MathLibrary::ComplexNumber operand);
		MathLibrary::Integer operator-=(MathLibrary::Integer operand);
		MathLibrary::Integer operator-=(MathLibrary::NaturalNumber operand);
		MathLibrary::Integer operator-=(MathLibrary::Fraction operand);
		MathLibrary::Integer operator-=(MathLibrary::ComplexNumber operand);
		MathLibrary::Integer operator*=(MathLibrary::Integer operand);
		MathLibrary::Integer operator*=(MathLibrary::NaturalNumber operand);
		MathLibrary::Integer operator*=(MathLibrary::Fraction operand);
		MathLibrary::Integer operator*=(MathLibrary::ComplexNumber operand);
		MathLibrary::Integer operator/=(MathLibrary::Integer operand);
		MathLibrary::Integer operator/=(MathLibrary::NaturalNumber operand);
		MathLibrary::Integer operator/=(MathLibrary::Fraction operand);
		MathLibrary::Integer operator/=(MathLibrary::ComplexNumber operand);
		MathLibrary::Integer operator%=(MathLibrary::Integer operand);
		MathLibrary::Integer operator%=(MathLibrary::NaturalNumber operand);
		MathLibrary::Integer operator++(void);
		MathLibrary::Integer operator++(int);
		MathLibrary::Integer operator--(void);
		MathLibrary::Integer operator--(int);
		bool operator==(MathLibrary::Integer operand)const;
		bool operator==(MathLibrary::NaturalNumber operand)const;
		bool operator==(MathLibrary::Fraction operand)const;
		bool operator==(MathLibrary::ComplexNumber operand)const;
		bool operator!=(MathLibrary::Integer operand)const;
		bool operator!=(MathLibrary::NaturalNumber operand)const;
		bool operator!=(MathLibrary::Fraction operand)const;
		bool operator!=(MathLibrary::ComplexNumber operand)const;
		bool operator>(MathLibrary::Integer operand)const;
		bool operator>(MathLibrary::NaturalNumber operand)const;
		bool operator>(MathLibrary::Fraction operand)const;
		bool operator<(MathLibrary::Integer operand)const;
		bool operator<(MathLibrary::NaturalNumber operand)const;
		bool operator<(MathLibrary::Fraction operand)const;
		bool operator>=(MathLibrary::Integer operand)const;
		bool operator>=(MathLibrary::NaturalNumber operand)const;
		bool operator>=(MathLibrary::Fraction operand)const;
		bool operator<=(MathLibrary::Integer operand)const;
		bool operator<=(MathLibrary::NaturalNumber operand)const;
		bool operator<=(MathLibrary::Fraction operand)const;
		bool operator!(void)const;
		operator MathLibrary::NaturalNumber(void)const;
		operator MathLibrary::Fraction(void)const;
		operator MathLibrary::ComplexNumber(void)const;
		operator std::string(void)const;
		friend std::istream &operator>>(std::istream &is, MathLibrary::Integer &integer);
		friend std::ostream &operator<<(std::ostream &os, const MathLibrary::Integer &integer);
	};

	class Fraction
	{
	private:
		MathLibrary::Sign sign;
		MathLibrary::NaturalNumber numerator;
		MathLibrary::NaturalNumber denominator;
	#ifdef MATHLIBRARY_DEBUG
	public:
	#else
	private:
	#endif
		MathLibrary::Sign getSign(void)const;
		MathLibrary::NaturalNumber getNumerator(void)const;
		MathLibrary::NaturalNumber getDenominator(void)const;
		void setSign(MathLibrary::Sign newSign);
		void setNumerator(MathLibrary::NaturalNumber newNumerator);
		void setDenominator(MathLibrary::NaturalNumber newDenominator);
		void reduce(void);
	public:
		Fraction(void);
		Fraction(MathLibrary::Sign sign, MathLibrary::NaturalNumber numerator, MathLibrary::NaturalNumber denominator);
		Fraction(const MathLibrary::Fraction &object);
		MathLibrary::Fraction operator=(MathLibrary::Fraction operand);
		MathLibrary::Fraction operator=(MathLibrary::NaturalNumber operand);
		MathLibrary::Fraction operator=(MathLibrary::Integer operand);
		MathLibrary::Fraction operator=(MathLibrary::ComplexNumber operand);
		MathLibrary::Fraction operator=(std::string operand);
		MathLibrary::Fraction operator+(MathLibrary::Fraction operand)const;
		MathLibrary::Fraction operator+(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator+(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator+(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Fraction operator-(MathLibrary::Fraction operand)const;
		MathLibrary::Fraction operator-(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator-(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator-(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Fraction operator*(MathLibrary::Fraction operand)const;
		MathLibrary::Fraction operator*(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator*(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator*(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Fraction operator/(MathLibrary::Fraction operand)const;
		MathLibrary::Fraction operator/(MathLibrary::NaturalNumber operand)const;
		MathLibrary::Fraction operator/(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator/(MathLibrary::ComplexNumber operand)const;
		MathLibrary::Fraction operator+=(MathLibrary::Fraction operand);
		MathLibrary::Fraction operator+=(MathLibrary::NaturalNumber operand);
		MathLibrary::Fraction operator+=(MathLibrary::Integer operand);
		MathLibrary::Fraction operator+=(MathLibrary::ComplexNumber operand);
		MathLibrary::Fraction operator-=(MathLibrary::Fraction operand);
		MathLibrary::Fraction operator-=(MathLibrary::NaturalNumber operand);
		MathLibrary::Fraction operator-=(MathLibrary::Integer operand);
		MathLibrary::Fraction operator-=(MathLibrary::ComplexNumber operand);
		MathLibrary::Fraction operator*=(MathLibrary::Fraction operand);
		MathLibrary::Fraction operator*=(MathLibrary::NaturalNumber operand);
		MathLibrary::Fraction operator*=(MathLibrary::Integer operand);
		MathLibrary::Fraction operator*=(MathLibrary::ComplexNumber operand);
		MathLibrary::Fraction operator/=(MathLibrary::Fraction operand);
		MathLibrary::Fraction operator/=(MathLibrary::NaturalNumber operand);
		MathLibrary::Fraction operator/=(MathLibrary::Integer operand);
		MathLibrary::Fraction operator/=(MathLibrary::ComplexNumber operand);
		MathLibrary::Fraction operator++(void);
		MathLibrary::Fraction operator++(int);
		MathLibrary::Fraction operator--(void);
		MathLibrary::Fraction operator--(int);
		bool operator==(MathLibrary::Fraction operand)const;
		bool operator==(MathLibrary::NaturalNumber operand)const;
		bool operator==(MathLibrary::Integer operand)const;
		bool operator==(MathLibrary::ComplexNumber operand)const;
		bool operator!=(MathLibrary::Fraction operand)const;
		bool operator!=(MathLibrary::NaturalNumber operand)const;
		bool operator!=(MathLibrary::Integer operand)const;
		bool operator!=(MathLibrary::ComplexNumber operand)const;
		bool operator>(MathLibrary::Fraction operand)const;
		bool operator>(MathLibrary::NaturalNumber operand)const;
		bool operator>(MathLibrary::Integer operand)const;
		bool operator<(MathLibrary::Fraction operand)const;
		bool operator<(MathLibrary::NaturalNumber operand)const;
		bool operator<(MathLibrary::Integer operand)const;
		bool operator>=(MathLibrary::Fraction operand)const;
		bool operator>=(MathLibrary::NaturalNumber operand)const;
		bool operator>=(MathLibrary::Integer operand)const;
		bool operator<=(MathLibrary::Fraction operand)const;
		bool operator<=(MathLibrary::NaturalNumber operand)const;
		bool operator<=(MathLibrary::Integer operand)const;
		bool operator!(void)const;
		operator MathLibrary::NaturalNumber(void)const;
		operator MathLibrary::Integer(void)const;
		operator MathLibrary::ComplexNumber(void)const;
		operator std::string(void)const;
		std::string toDecimal(unsigned int digit)const;
		friend std::istream &operator>>(std::istream &is, MathLibrary::Fraction &fraction);
		friend std::ostream &operator<<(std::ostream &os, const MathLibrary::Fraction &fraction);
	};

	class ComplexNumber
	{
	private:
		MathLibrary::Fraction realPart;
		MathLibrary::Fraction imaginaryPart;
	#ifdef MATHLIBRARY_DEBUG
	public:
	#else
	private:
	#endif
		MathLibrary::Fraction getRealPart(void)const;
		MathLibrary::Fraction getImaginaryPart(void)const;
		void setRealPart(const MathLibrary::Fraction &realPart);
		void setImaginaryPart(const MathLibrary::Fraction &imaginaryPart);
	public:
		ComplexNumber(void);
		ComplexNumber(MathLibrary::Fraction realPart, MathLibrary::Fraction imaginaryPart);
		ComplexNumber(const MathLibrary::ComplexNumber &object);
		MathLibrary::ComplexNumber operator=(MathLibrary::ComplexNumber operand);
		MathLibrary::ComplexNumber operator=(MathLibrary::NaturalNumber operand);
		MathLibrary::ComplexNumber operator=(MathLibrary::Integer operand);
		MathLibrary::ComplexNumber operator=(MathLibrary::Fraction operand);
		MathLibrary::ComplexNumber operator=(std::string operand);
		MathLibrary::ComplexNumber operator+(MathLibrary::ComplexNumber operand)const;
		MathLibrary::ComplexNumber operator+(MathLibrary::NaturalNumber operand)const;
		MathLibrary::ComplexNumber operator+(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator+(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator-(MathLibrary::ComplexNumber operand)const;
		MathLibrary::ComplexNumber operator-(MathLibrary::NaturalNumber operand)const;
		MathLibrary::ComplexNumber operator-(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator-(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator*(MathLibrary::ComplexNumber operand)const;
		MathLibrary::ComplexNumber operator*(MathLibrary::NaturalNumber operand)const;
		MathLibrary::ComplexNumber operator*(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator*(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator/(MathLibrary::ComplexNumber operand)const;
		MathLibrary::ComplexNumber operator/(MathLibrary::NaturalNumber operand)const;
		MathLibrary::ComplexNumber operator/(MathLibrary::Integer operand)const;
		MathLibrary::ComplexNumber operator/(MathLibrary::Fraction operand)const;
		MathLibrary::ComplexNumber operator+=(MathLibrary::ComplexNumber operand);
		MathLibrary::ComplexNumber operator+=(MathLibrary::NaturalNumber operand);
		MathLibrary::ComplexNumber operator+=(MathLibrary::Integer operand);
		MathLibrary::ComplexNumber operator+=(MathLibrary::Fraction operand);
		MathLibrary::ComplexNumber operator-=(MathLibrary::ComplexNumber operand);
		MathLibrary::ComplexNumber operator-=(MathLibrary::NaturalNumber operand);
		MathLibrary::ComplexNumber operator-=(MathLibrary::Integer operand);
		MathLibrary::ComplexNumber operator-=(MathLibrary::Fraction operand);
		MathLibrary::ComplexNumber operator*=(MathLibrary::ComplexNumber operand);
		MathLibrary::ComplexNumber operator*=(MathLibrary::NaturalNumber operand);
		MathLibrary::ComplexNumber operator*=(MathLibrary::Integer operand);
		MathLibrary::ComplexNumber operator*=(MathLibrary::Fraction operand);
		MathLibrary::ComplexNumber operator/=(MathLibrary::ComplexNumber operand);
		MathLibrary::ComplexNumber operator/=(MathLibrary::NaturalNumber operand);
		MathLibrary::ComplexNumber operator/=(MathLibrary::Integer operand);
		MathLibrary::ComplexNumber operator/=(MathLibrary::Fraction operand);
		MathLibrary::ComplexNumber operator++(void);
		MathLibrary::ComplexNumber operator++(int);
		MathLibrary::ComplexNumber operator--(void);
		MathLibrary::ComplexNumber operator--(int);
		bool operator==(MathLibrary::ComplexNumber operand)const;
		bool operator==(MathLibrary::NaturalNumber operand)const;
		bool operator==(MathLibrary::Integer operand)const;
		bool operator==(MathLibrary::Fraction operand)const;
		bool operator!=(MathLibrary::ComplexNumber operand)const;
		bool operator!=(MathLibrary::NaturalNumber operand)const;
		bool operator!=(MathLibrary::Integer operand)const;
		bool operator!=(MathLibrary::Fraction operand)const;
		operator MathLibrary::NaturalNumber(void)const;
		operator MathLibrary::Integer(void)const;
		operator MathLibrary::Fraction(void)const;
		operator std::string(void)const;
		MathLibrary::ComplexNumber conjugate(void)const;
		std::string toDecimal(unsigned int digit)const;
		friend std::istream &operator>>(std::istream &is, MathLibrary::ComplexNumber &complexNumber);
		friend std::ostream &operator<<(std::ostream &os, const MathLibrary::ComplexNumber &complexNumber);
	};
}
#endif

