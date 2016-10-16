#include<string>

namespace MyMath
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
	#ifdef MYMATH_DEBUG
	public:
	#else
	private:
	#endif
		MyMath::BitsDataType *data;
		MyMath::BitsSizeType size;
	public:
		#ifdef MYMATH_DEBUG
		std::string getBitTest(MyMath::BitsSizeType position)const;
		#endif
		Bits(void);
		Bits(MyMath::BitsSizeType size);
		Bits(std::string data);
		Bits(const MyMath::Bits &object);
		~Bits();
		bool getBit(MyMath::BitsSizeType position)const;
		void setBit(MyMath::BitsSizeType position, bool value);
		MyMath::BitsSizeType getSize(void)const;
		void setSize(MyMath::BitsSizeType size);
		MyMath::Bits operator=(MyMath::Bits operand);
		MyMath::Bits operator=(std::string operand);
		MyMath::Bits operator~(void)const;
		MyMath::Bits operator&(MyMath::Bits operand)const;
		MyMath::Bits operator|(MyMath::Bits operand)const;
		MyMath::Bits operator^(MyMath::Bits operand)const;
		MyMath::Bits operator<<(MyMath::BitsSizeType operand)const;
		MyMath::Bits operator>>(MyMath::BitsSizeType operand)const;
		MyMath::Bits operator&=(MyMath::Bits operand);
		MyMath::Bits operator|=(MyMath::Bits operand);
		MyMath::Bits operator^=(MyMath::Bits operand);
		MyMath::Bits operator<<=(MyMath::BitsSizeType operand);
		MyMath::Bits operator>>=(MyMath::BitsSizeType operand);
		bool operator==(MyMath::Bits operand)const;
		bool operator!=(MyMath::Bits operand)const;
		operator std::string(void)const;
		friend std::istream &operator>>(std::istream &is, MyMath::Bits &bits);
		friend std::ostream &operator<<(std::ostream &os, const MyMath::Bits &bits);
	};

	class NaturalNumber
	{
	private:
		MyMath::Bits bits;
	#ifdef MYMATH_DEBUG
	public:
	#else
	private:
	#endif
		MyMath::Bits getBits(void)const;
		void setBits(MyMath::Bits bits);
		void cutExtraZeros(void);
	public:
		NaturalNumber(void);
		NaturalNumber(MyMath::Bits data);
		NaturalNumber(const MyMath::NaturalNumber &object);
		MyMath::NaturalNumber operator=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator=(MyMath::Integer operand);
		MyMath::NaturalNumber operator=(MyMath::Fraction operand);
		MyMath::NaturalNumber operator=(MyMath::ComplexNumber operand);
		MyMath::NaturalNumber operator=(MyMath::Bits operand);
		MyMath::NaturalNumber operator=(std::string operand);
		MyMath::NaturalNumber operator~(void)const;
		MyMath::NaturalNumber operator&(MyMath::NaturalNumber operand)const;
		MyMath::NaturalNumber operator&(MyMath::Bits operand)const;
		MyMath::NaturalNumber operator|(MyMath::NaturalNumber operand)const;
		MyMath::NaturalNumber operator|(MyMath::Bits operand)const;
		MyMath::NaturalNumber operator^(MyMath::NaturalNumber operand)const;
		MyMath::NaturalNumber operator^(MyMath::Bits operand)const;
		MyMath::NaturalNumber operator<<(MyMath::BitsSizeType operand)const;
		MyMath::NaturalNumber operator>>(MyMath::BitsSizeType operand)const;
		MyMath::NaturalNumber operator+(MyMath::NaturalNumber operand)const;
		MyMath::Integer operator+(MyMath::Integer operand)const;
		MyMath::Fraction operator+(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator+(MyMath::ComplexNumber operand)const;
		MyMath::NaturalNumber operator-(MyMath::NaturalNumber operand)const;
		MyMath::Integer operator-(MyMath::Integer operand)const;
		MyMath::Fraction operator-(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator-(MyMath::ComplexNumber operand)const;
		MyMath::NaturalNumber operator*(MyMath::NaturalNumber operand)const;
		MyMath::Integer operator*(MyMath::Integer operand)const;
		MyMath::Fraction operator*(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator*(MyMath::ComplexNumber operand)const;
		MyMath::NaturalNumber operator/(MyMath::NaturalNumber operand)const;
		MyMath::Integer operator/(MyMath::Integer operand)const;
		MyMath::Fraction operator/(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator/(MyMath::ComplexNumber operand)const;
		MyMath::NaturalNumber operator%(MyMath::NaturalNumber operand)const;
		MyMath::Integer operator%(MyMath::Integer operand)const;
		MyMath::NaturalNumber operator++(void);
		MyMath::NaturalNumber operator++(int);
		MyMath::NaturalNumber operator--(void);
		MyMath::NaturalNumber operator--(int);
		MyMath::NaturalNumber operator&=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator&=(MyMath::Bits operand);
		MyMath::NaturalNumber operator|=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator|=(MyMath::Bits operand);
		MyMath::NaturalNumber operator^=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator^=(MyMath::Bits operand);
		MyMath::NaturalNumber operator<<=(MyMath::BitsSizeType operand);
		MyMath::NaturalNumber operator>>=(MyMath::BitsSizeType operand);
		MyMath::NaturalNumber operator+=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator+=(MyMath::Integer operand);
		MyMath::NaturalNumber operator+=(MyMath::Fraction operand);
		MyMath::NaturalNumber operator+=(MyMath::ComplexNumber operand);
		MyMath::NaturalNumber operator-=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator-=(MyMath::Integer operand);
		MyMath::NaturalNumber operator-=(MyMath::Fraction operand);
		MyMath::NaturalNumber operator-=(MyMath::ComplexNumber operand);
		MyMath::NaturalNumber operator*=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator*=(MyMath::Integer operand);
		MyMath::NaturalNumber operator*=(MyMath::Fraction operand);
		MyMath::NaturalNumber operator*=(MyMath::ComplexNumber operand);
		MyMath::NaturalNumber operator/=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator/=(MyMath::Integer operand);
		MyMath::NaturalNumber operator/=(MyMath::Fraction operand);
		MyMath::NaturalNumber operator/=(MyMath::ComplexNumber operand);
		MyMath::NaturalNumber operator%=(MyMath::NaturalNumber operand);
		MyMath::NaturalNumber operator%=(MyMath::Integer operand);
		bool operator==(MyMath::NaturalNumber operand)const;
		bool operator==(MyMath::Integer operand)const;
		bool operator==(MyMath::Fraction operand)const;
		bool operator==(MyMath::ComplexNumber operand)const;
		bool operator!=(MyMath::NaturalNumber operand)const;
		bool operator!=(MyMath::Integer operand)const;
		bool operator!=(MyMath::Fraction operand)const;
		bool operator!=(MyMath::ComplexNumber operand)const;
		bool operator>(MyMath::NaturalNumber operand)const;
		bool operator>(MyMath::Integer operand)const;
		bool operator>(MyMath::Fraction operand)const;
		bool operator<(MyMath::NaturalNumber operand)const;
		bool operator<(MyMath::Integer operand)const;
		bool operator<(MyMath::Fraction operand)const;
		bool operator>=(MyMath::NaturalNumber operand)const;
		bool operator>=(MyMath::Integer operand)const;
		bool operator>=(MyMath::Fraction operand)const;
		bool operator<=(MyMath::NaturalNumber operand)const;
		bool operator<=(MyMath::Integer operand)const;
		bool operator<=(MyMath::Fraction operand)const;
		bool operator!(void)const;
		operator MyMath::Integer(void)const;
		operator MyMath::Fraction(void)const;
		operator MyMath::ComplexNumber(void)const;
		operator std::string(void)const;
		friend std::istream &operator>>(std::istream &is, MyMath::NaturalNumber &naturalNumber);
		friend std::ostream &operator<<(std::ostream &os, const MyMath::NaturalNumber &naturalNumber);
	};

	typedef bool Sign;
	const Sign plus = true;
	const Sign minus = false;
	
	class Integer
	{
	private:
		MyMath::Sign sign;
		MyMath::NaturalNumber absoluteValue;
	#ifdef MYMATH_DEBUG
	public:
	#else
	private:
	#endif
		MyMath::Sign getSign(void)const;
		MyMath::NaturalNumber getAbsoluteValue(void)const;
		void setSign(MyMath::Sign sign);
		void setAbsoluteValue(MyMath::NaturalNumber absoluteValue);
	public:
		Integer(void);
		Integer(MyMath::Sign sign, MyMath::NaturalNumber absoluteValue);
		Integer(const MyMath::Integer &object);
		MyMath::Integer operator=(MyMath::Integer operand);
		MyMath::Integer operator=(MyMath::NaturalNumber operand);
		MyMath::Integer operator=(MyMath::Fraction operand);
		MyMath::Integer operator=(MyMath::ComplexNumber operand);
		MyMath::Integer operator=(std::string operand);
		MyMath::Integer operator+(MyMath::Integer operand)const;
		MyMath::Integer operator+(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator+(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator+(MyMath::ComplexNumber operand)const;
		MyMath::Integer operator-(MyMath::Integer operand)const;
		MyMath::Integer operator-(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator-(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator-(MyMath::ComplexNumber operand)const;
		MyMath::Integer operator*(MyMath::Integer operand)const;
		MyMath::Integer operator*(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator*(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator*(MyMath::ComplexNumber operand)const;
		MyMath::Integer operator/(MyMath::Integer operand)const;
		MyMath::Integer operator/(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator/(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator/(MyMath::ComplexNumber operand)const;
		MyMath::Integer operator%(MyMath::Integer operand)const;
		MyMath::Integer operator%(MyMath::NaturalNumber operand)const;
		MyMath::Integer operator+=(MyMath::Integer operand);
		MyMath::Integer operator+=(MyMath::NaturalNumber operand);
		MyMath::Integer operator+=(MyMath::Fraction operand);
		MyMath::Integer operator+=(MyMath::ComplexNumber operand);
		MyMath::Integer operator-=(MyMath::Integer operand);
		MyMath::Integer operator-=(MyMath::NaturalNumber operand);
		MyMath::Integer operator-=(MyMath::Fraction operand);
		MyMath::Integer operator-=(MyMath::ComplexNumber operand);
		MyMath::Integer operator*=(MyMath::Integer operand);
		MyMath::Integer operator*=(MyMath::NaturalNumber operand);
		MyMath::Integer operator*=(MyMath::Fraction operand);
		MyMath::Integer operator*=(MyMath::ComplexNumber operand);
		MyMath::Integer operator/=(MyMath::Integer operand);
		MyMath::Integer operator/=(MyMath::NaturalNumber operand);
		MyMath::Integer operator/=(MyMath::Fraction operand);
		MyMath::Integer operator/=(MyMath::ComplexNumber operand);
		MyMath::Integer operator%=(MyMath::Integer operand);
		MyMath::Integer operator%=(MyMath::NaturalNumber operand);
		MyMath::Integer operator++(void);
		MyMath::Integer operator++(int);
		MyMath::Integer operator--(void);
		MyMath::Integer operator--(int);
		bool operator==(MyMath::Integer operand)const;
		bool operator==(MyMath::NaturalNumber operand)const;
		bool operator==(MyMath::Fraction operand)const;
		bool operator==(MyMath::ComplexNumber operand)const;
		bool operator!=(MyMath::Integer operand)const;
		bool operator!=(MyMath::NaturalNumber operand)const;
		bool operator!=(MyMath::Fraction operand)const;
		bool operator!=(MyMath::ComplexNumber operand)const;
		bool operator>(MyMath::Integer operand)const;
		bool operator>(MyMath::NaturalNumber operand)const;
		bool operator>(MyMath::Fraction operand)const;
		bool operator<(MyMath::Integer operand)const;
		bool operator<(MyMath::NaturalNumber operand)const;
		bool operator<(MyMath::Fraction operand)const;
		bool operator>=(MyMath::Integer operand)const;
		bool operator>=(MyMath::NaturalNumber operand)const;
		bool operator>=(MyMath::Fraction operand)const;
		bool operator<=(MyMath::Integer operand)const;
		bool operator<=(MyMath::NaturalNumber operand)const;
		bool operator<=(MyMath::Fraction operand)const;
		bool operator!(void)const;
		operator MyMath::NaturalNumber(void)const;
		operator MyMath::Fraction(void)const;
		operator MyMath::ComplexNumber(void)const;
		operator std::string(void)const;
		friend std::istream &operator>>(std::istream &is, MyMath::Integer &integer);
		friend std::ostream &operator<<(std::ostream &os, const MyMath::Integer &integer);
	};

	class Fraction
	{
	private:
		MyMath::Sign sign;
		MyMath::NaturalNumber numerator;
		MyMath::NaturalNumber denominator;
	#ifdef MYMATH_DEBUG
	public:
	#else
	private:
	#endif
		MyMath::Sign getSign(void)const;
		MyMath::NaturalNumber getNumerator(void)const;
		MyMath::NaturalNumber getDenominator(void)const;
		void setSign(MyMath::Sign newSign);
		void setNumerator(MyMath::NaturalNumber newNumerator);
		void setDenominator(MyMath::NaturalNumber newDenominator);
		void reduce(void);
	public:
		Fraction(void);
		Fraction(MyMath::Sign sign, MyMath::NaturalNumber numerator, MyMath::NaturalNumber denominator);
		Fraction(const MyMath::Fraction &object);
		MyMath::Fraction operator=(MyMath::Fraction operand);
		MyMath::Fraction operator=(MyMath::NaturalNumber operand);
		MyMath::Fraction operator=(MyMath::Integer operand);
		MyMath::Fraction operator=(MyMath::ComplexNumber operand);
		MyMath::Fraction operator=(std::string operand);
		MyMath::Fraction operator+(MyMath::Fraction operand)const;
		MyMath::Fraction operator+(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator+(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator+(MyMath::ComplexNumber operand)const;
		MyMath::Fraction operator-(MyMath::Fraction operand)const;
		MyMath::Fraction operator-(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator-(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator-(MyMath::ComplexNumber operand)const;
		MyMath::Fraction operator*(MyMath::Fraction operand)const;
		MyMath::Fraction operator*(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator*(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator*(MyMath::ComplexNumber operand)const;
		MyMath::Fraction operator/(MyMath::Fraction operand)const;
		MyMath::Fraction operator/(MyMath::NaturalNumber operand)const;
		MyMath::Fraction operator/(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator/(MyMath::ComplexNumber operand)const;
		MyMath::Fraction operator+=(MyMath::Fraction operand);
		MyMath::Fraction operator+=(MyMath::NaturalNumber operand);
		MyMath::Fraction operator+=(MyMath::Integer operand);
		MyMath::Fraction operator+=(MyMath::ComplexNumber operand);
		MyMath::Fraction operator-=(MyMath::Fraction operand);
		MyMath::Fraction operator-=(MyMath::NaturalNumber operand);
		MyMath::Fraction operator-=(MyMath::Integer operand);
		MyMath::Fraction operator-=(MyMath::ComplexNumber operand);
		MyMath::Fraction operator*=(MyMath::Fraction operand);
		MyMath::Fraction operator*=(MyMath::NaturalNumber operand);
		MyMath::Fraction operator*=(MyMath::Integer operand);
		MyMath::Fraction operator*=(MyMath::ComplexNumber operand);
		MyMath::Fraction operator/=(MyMath::Fraction operand);
		MyMath::Fraction operator/=(MyMath::NaturalNumber operand);
		MyMath::Fraction operator/=(MyMath::Integer operand);
		MyMath::Fraction operator/=(MyMath::ComplexNumber operand);
		MyMath::Fraction operator++(void);
		MyMath::Fraction operator++(int);
		MyMath::Fraction operator--(void);
		MyMath::Fraction operator--(int);
		bool operator==(MyMath::Fraction operand)const;
		bool operator==(MyMath::NaturalNumber operand)const;
		bool operator==(MyMath::Integer operand)const;
		bool operator==(MyMath::ComplexNumber operand)const;
		bool operator!=(MyMath::Fraction operand)const;
		bool operator!=(MyMath::NaturalNumber operand)const;
		bool operator!=(MyMath::Integer operand)const;
		bool operator!=(MyMath::ComplexNumber operand)const;
		bool operator>(MyMath::Fraction operand)const;
		bool operator>(MyMath::NaturalNumber operand)const;
		bool operator>(MyMath::Integer operand)const;
		bool operator<(MyMath::Fraction operand)const;
		bool operator<(MyMath::NaturalNumber operand)const;
		bool operator<(MyMath::Integer operand)const;
		bool operator>=(MyMath::Fraction operand)const;
		bool operator>=(MyMath::NaturalNumber operand)const;
		bool operator>=(MyMath::Integer operand)const;
		bool operator<=(MyMath::Fraction operand)const;
		bool operator<=(MyMath::NaturalNumber operand)const;
		bool operator<=(MyMath::Integer operand)const;
		bool operator!(void)const;
		operator MyMath::NaturalNumber(void)const;
		operator MyMath::Integer(void)const;
		operator MyMath::ComplexNumber(void)const;
		operator std::string(void)const;
		std::string toDecimal(unsigned int digit)const;
		friend std::istream &operator>>(std::istream &is, MyMath::Fraction &fraction);
		friend std::ostream &operator<<(std::ostream &os, const MyMath::Fraction &fraction);
	};

	class ComplexNumber
	{
	private:
		MyMath::Fraction realPart;
		MyMath::Fraction imaginaryPart;
	#ifdef MYMATH_DEBUG
	public:
	#else
	private:
	#endif
		MyMath::Fraction getRealPart(void)const;
		MyMath::Fraction getImaginaryPart(void)const;
		void setRealPart(const MyMath::Fraction &realPart);
		void setImaginaryPart(const MyMath::Fraction &imaginaryPart);
	public:
		ComplexNumber(void);
		ComplexNumber(MyMath::Fraction realPart, MyMath::Fraction imaginaryPart);
		ComplexNumber(const MyMath::ComplexNumber &object);
		MyMath::ComplexNumber operator=(MyMath::ComplexNumber operand);
		MyMath::ComplexNumber operator=(MyMath::NaturalNumber operand);
		MyMath::ComplexNumber operator=(MyMath::Integer operand);
		MyMath::ComplexNumber operator=(MyMath::Fraction operand);
		MyMath::ComplexNumber operator=(std::string operand);
		MyMath::ComplexNumber operator+(MyMath::ComplexNumber operand)const;
		MyMath::ComplexNumber operator+(MyMath::NaturalNumber operand)const;
		MyMath::ComplexNumber operator+(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator+(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator-(MyMath::ComplexNumber operand)const;
		MyMath::ComplexNumber operator-(MyMath::NaturalNumber operand)const;
		MyMath::ComplexNumber operator-(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator-(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator*(MyMath::ComplexNumber operand)const;
		MyMath::ComplexNumber operator*(MyMath::NaturalNumber operand)const;
		MyMath::ComplexNumber operator*(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator*(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator/(MyMath::ComplexNumber operand)const;
		MyMath::ComplexNumber operator/(MyMath::NaturalNumber operand)const;
		MyMath::ComplexNumber operator/(MyMath::Integer operand)const;
		MyMath::ComplexNumber operator/(MyMath::Fraction operand)const;
		MyMath::ComplexNumber operator+=(MyMath::ComplexNumber operand);
		MyMath::ComplexNumber operator+=(MyMath::NaturalNumber operand);
		MyMath::ComplexNumber operator+=(MyMath::Integer operand);
		MyMath::ComplexNumber operator+=(MyMath::Fraction operand);
		MyMath::ComplexNumber operator-=(MyMath::ComplexNumber operand);
		MyMath::ComplexNumber operator-=(MyMath::NaturalNumber operand);
		MyMath::ComplexNumber operator-=(MyMath::Integer operand);
		MyMath::ComplexNumber operator-=(MyMath::Fraction operand);
		MyMath::ComplexNumber operator*=(MyMath::ComplexNumber operand);
		MyMath::ComplexNumber operator*=(MyMath::NaturalNumber operand);
		MyMath::ComplexNumber operator*=(MyMath::Integer operand);
		MyMath::ComplexNumber operator*=(MyMath::Fraction operand);
		MyMath::ComplexNumber operator/=(MyMath::ComplexNumber operand);
		MyMath::ComplexNumber operator/=(MyMath::NaturalNumber operand);
		MyMath::ComplexNumber operator/=(MyMath::Integer operand);
		MyMath::ComplexNumber operator/=(MyMath::Fraction operand);
		MyMath::ComplexNumber operator++(void);
		MyMath::ComplexNumber operator++(int);
		MyMath::ComplexNumber operator--(void);
		MyMath::ComplexNumber operator--(int);
		bool operator==(MyMath::ComplexNumber operand)const;
		bool operator==(MyMath::NaturalNumber operand)const;
		bool operator==(MyMath::Integer operand)const;
		bool operator==(MyMath::Fraction operand)const;
		bool operator!=(MyMath::ComplexNumber operand)const;
		bool operator!=(MyMath::NaturalNumber operand)const;
		bool operator!=(MyMath::Integer operand)const;
		bool operator!=(MyMath::Fraction operand)const;
		operator MyMath::NaturalNumber(void)const;
		operator MyMath::Integer(void)const;
		operator MyMath::Fraction(void)const;
		operator std::string(void)const;
		MyMath::ComplexNumber conjugate(void)const;
		std::string toDecimal(unsigned int digit)const;
		friend std::istream &operator>>(std::istream &is, MyMath::ComplexNumber &complexNumber);
		friend std::ostream &operator<<(std::ostream &os, const MyMath::ComplexNumber &complexNumber);
	};
}

