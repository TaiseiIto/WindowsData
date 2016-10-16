#include<climits>
#include<iostream>
#include<string>
#include"MyMath.h"

#ifdef MYMATH_DEBUG
std::string MyMath::Bits::getBitTest(MyMath::BitsSizeType position)const
{
	if(position < this->size)
	{
		MyMath::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
		MyMath::BitsSizeType elementPosition = position / elementSize;
		MyMath::BitsSizeType bitPosition = position % elementSize;
		if((this->data[elementPosition] & (1 << bitPosition)) >> bitPosition)return "1";
		else return "0";
	}
	else return "null";
}
#endif

MyMath::Bits::Bits(void)
{
	this->size = 0;
	this->data = new MyMath::BitsDataType(0);
	return;
}

MyMath::Bits::Bits(MyMath::BitsSizeType size)
{
	MyMath::BitsSizeType elementSize = sizeof(MyMath::BitsDataType) * CHAR_BIT;
	this->size = size;
	this->data = new MyMath::BitsDataType[size / elementSize + 1];
	for(MyMath::BitsSizeType i = 0; i <= size / elementSize; i++)this->data[i] = 0;
	return;
}

MyMath::Bits::Bits(std::string data)
{
	this->size = 0;
	this->data = new MyMath::BitsDataType(0);
	*this = data;
	return;
}

MyMath::Bits::Bits(const MyMath::Bits &object)
{
	MyMath::BitsSizeType elementSize = sizeof(MyMath::BitsDataType) * CHAR_BIT;
	this->size = object.size;
	this->data = new MyMath::BitsDataType[this->size / elementSize + 1];
	for(MyMath::BitsSizeType i = 0; i < this->size / elementSize + 1; i++)this->data[i] = object.data[i];
	return;
}

MyMath::Bits::~Bits()
{
	if(this->data != NULL)
	{
		delete [] this->data;
		this->data = NULL;
	}
	return;
}

bool MyMath::Bits::getBit(MyMath::BitsSizeType position)const
{
	if(position < this->size)
	{
		MyMath::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
		MyMath::BitsSizeType elementPosition = position / elementSize;
		MyMath::BitsSizeType bitPosition = position % elementSize;
		if((this->data[elementPosition] & (1 << bitPosition)) >> bitPosition)return true;
		else return false;
	}
	else
	{
		std::cerr << "position>=this->size @ bool MyMath::Bits::getBit(MyMath::BitsSizeType position)" << std::endl;
		std::cerr << "position == " << position << std::endl;
		std::cerr << "this->size == " << this->size << std::endl;
		return false;
	}
}

void MyMath::Bits::setBit(MyMath::BitsSizeType position, bool value)
{
	if(position < this->size)
	{
		if(value != this->getBit(position))
		{
			MyMath::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
			MyMath::BitsSizeType elementPosition = position / elementSize;
			MyMath::BitsSizeType bitPosition = position % elementSize;
			if(value)this->data[elementPosition] += 1 << bitPosition;
			else this->data[elementPosition] -= 1 << bitPosition;
		}
	}
	else
	{
		std::cerr << "position>=this->size @ void MyMath::Bits::setBit(MyMath::BitsSizeType position, bool value)" << std::endl;
		std::cerr << "position == " << position << std::endl;
		std::cerr << "this->size == " << this->size << std::endl;
	}
	return;
}

MyMath::BitsSizeType MyMath::Bits::getSize(void)const
{
	return this->size;
}

void MyMath::Bits::setSize(MyMath::BitsSizeType size)
{
	MyMath::BitsSizeType lastSize = this->size;
	MyMath::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
	if(size / elementSize > this->size / elementSize)
	{
		MyMath::BitsDataType *newdata;
		newdata = new MyMath::BitsDataType[size / elementSize + 1];
		for(MyMath::BitsSizeType i = 0; i <= this->size / elementSize; i++)newdata[i] = this->data[i];
		for(MyMath::BitsSizeType i = this->size / elementSize + 1; i <= size / elementSize; i++)newdata[i] = 0;
		if(this->data != NULL)delete [] this->data;
		this->data = newdata;
	}
	else if(size / elementSize < this->size / elementSize)
	{
		MyMath::BitsDataType *newdata;
		newdata = new MyMath::BitsDataType[size / elementSize + 1];
		for(MyMath::BitsSizeType i = 0; i <= size / elementSize; i++)newdata[i] = this->data[i];
		delete [] this->data;
		this->data = newdata;
	}
	this->size = elementSize * (size / elementSize + 1);
	if(size > lastSize)for(MyMath::BitsSizeType i = lastSize; i < size; i++)this->setBit(i, false);
	this->size = size;
	return;
}

MyMath::Bits MyMath::Bits::operator=(MyMath::Bits operand)
{
	MyMath::Bits result(operand);
	this->setSize(operand.getSize());
	for(MyMath::BitsSizeType i = 0; i < this->getSize(); i++)this->setBit(i, operand.getBit(i));
	return result;
}

MyMath::Bits MyMath::Bits::operator=(std::string operand)
{
	for(std::string::size_type i = 0; i < operand.size(); i++)if(operand.substr(i, 1) != "0" && operand.substr(i, 1) != "1")
	{
		std::cerr << "An operand is not binary. @ MyMath::Bits MyMath::Bits::operator=(std::string operand)" << std::endl;
		this->setSize(0);
		return *this;
	}
	this->setSize(operand.size());
	for(MyMath::BitsSizeType i = 0; i < this->getSize(); i++)this->setBit(i, (operand.substr(i, 1) == "1") ? true : false);
	return *this;
}

MyMath::Bits MyMath::Bits::operator~(void)const
{
	MyMath::Bits result(this->getSize());
	for(MyMath::BitsSizeType i = 0; i < result.getSize(); i++)result.setBit(i, this->getBit(i) ? false : true);
	return result;
}

MyMath::Bits MyMath::Bits::operator&(MyMath::Bits operand)const
{
	MyMath::Bits result((this->getSize() < operand.getSize()) ? this->getSize() : operand.getSize());
	for(MyMath::BitsSizeType i = 0; i < result.getSize(); i++)result.setBit(i, this->getBit(i) & operand.getBit(i));
	return result;
}

MyMath::Bits MyMath::Bits::operator|(MyMath::Bits operand)const
{
	MyMath::Bits larger = (this->getSize() >= operand.getSize()) ? *this : operand;
	MyMath::Bits smaller = (this->getSize() < operand.getSize()) ? *this : operand;
	MyMath::Bits result(larger.getSize());
	for(MyMath::BitsSizeType i = 0; i < smaller.getSize(); i++)result.setBit(i, larger.getBit(i) | smaller.getBit(i));
	for(MyMath::BitsSizeType i = smaller.getSize(); i < larger.getSize(); i++)result.setBit(i, larger.getBit(i));
	return result;
}

MyMath::Bits MyMath::Bits::operator^(MyMath::Bits operand)const
{
	MyMath::Bits larger = (this->getSize() >= operand.getSize()) ? *this : operand;
	MyMath::Bits smaller = (this->getSize() < operand.getSize()) ? *this : operand;
	MyMath::Bits result(larger.getSize());
	for(MyMath::BitsSizeType i = 0; i < smaller.getSize(); i++)result.setBit(i, larger.getBit(i) ^ smaller.getBit(i));
	for(MyMath::BitsSizeType i = smaller.getSize(); i < larger.getSize(); i++)result.setBit(i, larger.getBit(i));
	return result;
}

MyMath::Bits MyMath::Bits::operator<<(MyMath::BitsSizeType operand)const
{
	MyMath::Bits result(this->getSize() + operand);
	for(MyMath::BitsSizeType i = 0; i < operand; i++)result.setBit(i, false);
	for(MyMath::BitsSizeType i = 0; i < this->getSize(); i++)result.setBit(operand + i, this->getBit(i));
	return result;
}

MyMath::Bits MyMath::Bits::operator>>(MyMath::BitsSizeType operand)const
{
	if(this->getSize() <= operand)return MyMath::Bits(0);
	MyMath::Bits result(this->getSize() - operand);
	for(MyMath::BitsSizeType i = 0; i < result.getSize(); i++)result.setBit(i, this->getBit(i + operand));
	return result;
}

MyMath::Bits MyMath::Bits::operator&=(MyMath::Bits operand)
{
	*this = *this & operand;
	return *this;
}

MyMath::Bits MyMath::Bits::operator|=(MyMath::Bits operand)
{
	*this = *this | operand;
	return *this;
}

MyMath::Bits MyMath::Bits::operator^=(MyMath::Bits operand)
{
	*this = *this ^ operand;
	return *this;
}

MyMath::Bits MyMath::Bits::operator<<=(MyMath::BitsSizeType operand)
{
	*this = *this << operand;
	return *this;
}

MyMath::Bits MyMath::Bits::operator>>=(MyMath::BitsSizeType operand)
{
	*this = *this >> operand;
	return *this;
}

bool MyMath::Bits::operator==(MyMath::Bits operand)const
{
	if(this->getSize() != operand.getSize())return false;
 	for(MyMath::BitsSizeType i = 0; i < this->getSize(); i++)if(this->getBit(i) != operand.getBit(i))return false;
	return true;
}

bool MyMath::Bits::operator!=(MyMath::Bits operand)const
{
	if(this->getSize() != operand.getSize())return true;
 	for(MyMath::BitsSizeType i = 0; i < this->getSize(); i++)if(this->getBit(i) != operand.getBit(i))return true;
	return false;
}

MyMath::Bits::operator std::string(void)const
{
	std::string result = "";
	for(MyMath::BitsSizeType i = 0; i < this->getSize(); i++)
		if(this->getBit(i))result = result + "1";
		else result = result + "0";
	return result;
}

std::istream &MyMath::operator>>(std::istream &is, MyMath::Bits &bits)
{
	std::string str;
	is >> str;
	for(std::string::size_type i = 0; i < str.size(); i++)if(str.substr(i, 1) != "0" && str.substr(i, 1) != "1")
	{
		std::cerr << "Input data is not a binary. @ std::istream &MyMath::operator(std::istream &is, const MyMath::Bits &bits)" << std::endl;
		bits.setSize(0);
		return is;
	}
	bits = str;
	return is;
}

std::ostream &MyMath::operator<<(std::ostream &os, const MyMath::Bits &bits)
{
	for(MyMath::BitsSizeType i = 0; i < bits.getSize(); i++)
		if(bits.getBit(i))os << "1";
		else os << "0";
	return os;
}

MyMath::Bits MyMath::NaturalNumber::getBits(void)const
{
	return this->bits;
}

void MyMath::NaturalNumber::setBits(MyMath::Bits bits)
{
	this->bits = bits;
	this->cutExtraZeros();
	return;
}

void MyMath::NaturalNumber::cutExtraZeros(void)
{
	MyMath::BitsSizeType countExtraZeros = 0;
	for(MyMath::BitsSizeType i = this->bits.getSize() - 1; i < this->bits.getSize(); i--)
		if(!this->bits.getBit(i))countExtraZeros++;
		else break;
	this->bits.setSize(this->bits.getSize() - countExtraZeros);
	return;
}

MyMath::NaturalNumber::NaturalNumber(void)
{
	this->setBits(MyMath::Bits());
	return;
}

MyMath::NaturalNumber::NaturalNumber(MyMath::Bits data)
{
	this->setBits(data);
	this->cutExtraZeros();
	return;
}

MyMath::NaturalNumber::NaturalNumber(const MyMath::NaturalNumber &object)
{
	this->setBits(object.getBits());
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator=(MyMath::NaturalNumber operand)
{
	this->setBits(operand.getBits());
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator=(MyMath::Integer operand)
{
	*this = (MyMath::NaturalNumber)operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator=(MyMath::Fraction operand)
{
	*this = (MyMath::NaturalNumber)operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::NaturalNumber)operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator=(MyMath::Bits operand)
{
	this->setBits(operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator=(std::string operand)
{
	MyMath::Bits bitTen;
	bitTen = "0101";
	const MyMath::NaturalNumber ten = MyMath::NaturalNumber(bitTen);
	this->setBits(MyMath::Bits());
	for(std::string::size_type i = 0; i < operand.size(); i++)if(operand.c_str()[i] < '0' || '9' < operand.c_str()[i])
	{
		std::cerr << "operand is not natural number. @ MyMath::NaturalNumber MyMath::NaturalNumber::operator=(std::string operand)" << std::endl;
		return *this;
	}
	for(std::string::size_type i = 0; i < operand.size(); i++)
	{
		*this *= ten;
		for(char j = operand.c_str()[i]; j != '0'; j--)(*this)++;
	}
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator~(void)const
{
	MyMath::NaturalNumber result(~this->getBits());
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator&(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber result(this->getBits() & operand.getBits());
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator&(MyMath::Bits operand)const
{
	MyMath::NaturalNumber result(this->getBits() & operand);
	result.cutExtraZeros();
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator|(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber result(this->getBits() | operand.getBits());
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator|(MyMath::Bits operand)const
{
	MyMath::NaturalNumber result(this->getBits() | operand);
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator^(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber result(this->getBits() ^ operand.getBits());
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator^(MyMath::Bits operand)const
{
	MyMath::NaturalNumber result(this->getBits() ^ operand);
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator<<(MyMath::BitsSizeType operand)const
{
	MyMath::NaturalNumber result(this->getBits() << operand);
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator>>(MyMath::BitsSizeType operand)const
{
	MyMath::NaturalNumber result(this->getBits() >> operand);
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator+(MyMath::NaturalNumber operand)const
{
	MyMath::Bits longerBits = (this->getBits().getSize() >= operand.getBits().getSize()) ? this->getBits() : operand.getBits();
	MyMath::Bits shorterBits = (this->getBits().getSize() < operand.getBits().getSize()) ? this->getBits() : operand.getBits();
	MyMath::Bits resultBits(longerBits.getSize() + 1);
	bool carry = false;
	for(MyMath::BitsSizeType i = 0; i < shorterBits.getSize(); i++)
	{
		resultBits.setBit(i, carry ^ longerBits.getBit(i) ^ shorterBits.getBit(i));
		carry = (longerBits.getBit(i) & shorterBits.getBit(i)) | (carry & longerBits.getBit(i)) | (carry & shorterBits.getBit(i));
	}
	for(MyMath::BitsSizeType i = shorterBits.getSize(); i < longerBits.getSize(); i++)
	{
		resultBits.setBit(i, carry ^ longerBits.getBit(i));
		carry = carry & longerBits.getBit(i);
	}
	resultBits.setBit(resultBits.getSize() - 1, carry);
	return MyMath::NaturalNumber(resultBits);
}

MyMath::Integer MyMath::NaturalNumber::operator+(MyMath::Integer operand)const
{
	return (MyMath::Integer)*this + operand;
}

MyMath::Fraction MyMath::NaturalNumber::operator+(MyMath::Fraction operand)const
{
	return (MyMath::Fraction)*this + operand;
}

MyMath::ComplexNumber MyMath::NaturalNumber::operator+(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this + operand;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator-(MyMath::NaturalNumber operand)const
{
	MyMath::Bits largerBits = (*this >= operand) ? this->getBits() : operand.getBits();
	MyMath::Bits smallerBits = (*this < operand) ? this->getBits() : operand.getBits();
	MyMath::Bits resultBits(largerBits.getSize());
	bool borrow = false;
	if(*this < operand)
	{
		std::cerr << "*this < operand @ MyMath::NaturalNumber MyMath::NaturalNumber::operator-(MyMath::NaturalNumber operand)const" << std::endl;
		return MyMath::NaturalNumber();
	}
	for(MyMath::BitsSizeType i = 0; i < smallerBits.getSize(); i++)
	{
		resultBits.setBit(i, borrow ^ largerBits.getBit(i) ^ smallerBits.getBit(i));
		borrow = (!largerBits.getBit(i) & smallerBits.getBit(i)) | (borrow & !largerBits.getBit(i)) | (borrow & smallerBits.getBit(i));
	}
	for(MyMath::BitsSizeType i = smallerBits.getSize(); i < largerBits.getSize(); i++)
	{
		resultBits.setBit(i, borrow ^ largerBits.getBit(i));
		borrow = borrow & !largerBits.getBit(i);
	}
	return MyMath::NaturalNumber(resultBits);
}

MyMath::Integer MyMath::NaturalNumber::operator-(MyMath::Integer operand)const
{
	return (MyMath::Integer)*this - operand;
}

MyMath::Fraction MyMath::NaturalNumber::operator-(MyMath::Fraction operand)const
{
	return (MyMath::Fraction)*this - operand;
}

MyMath::ComplexNumber MyMath::NaturalNumber::operator-(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this - operand;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator*(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber result = MyMath::NaturalNumber();
	for(MyMath::BitsSizeType i = 0; i < this->getBits().getSize(); i++)if(this->getBits().getBit(i))result = result + (operand << i);
	return result;
}

MyMath::Integer MyMath::NaturalNumber::operator*(MyMath::Integer operand)const
{
	return (MyMath::Integer)*this * operand;
}

MyMath::Fraction MyMath::NaturalNumber::operator*(MyMath::Fraction operand)const
{
	return (MyMath::Fraction)*this * operand;
}

MyMath::ComplexNumber MyMath::NaturalNumber::operator*(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this * operand;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator/(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber result = MyMath::NaturalNumber();
	MyMath::NaturalNumber copyThis = *this;
	MyMath::Bits bitsOne = MyMath::Bits(1);
	bitsOne.setBit(0, true);
	const MyMath::NaturalNumber one = MyMath::NaturalNumber(bitsOne);
	if(operand.getBits().getSize() == 0)
	{
		std::cerr << "operand.getBits().getSize() == 0 @ MyMath::NaturalNumber MyMath::NaturalNumber::operator/(MyMath::NaturalNumber operand)const" << std::endl;
		return result;
	}
	if(*this < operand)return result;
	for(MyMath::BitsSizeType i = this->getBits().getSize() - operand.getBits().getSize(); i <= this->getBits().getSize() - operand.getBits().getSize(); i--)if(copyThis >= (operand << i))
	{
		result = result + (one << i);
		copyThis = copyThis - (operand << i);
	}
	return result;
}

MyMath::Integer MyMath::NaturalNumber::operator/(MyMath::Integer operand)const
{
	return (MyMath::Integer)*this / operand;
}

MyMath::Fraction MyMath::NaturalNumber::operator/(MyMath::Fraction operand)const
{
	return (MyMath::Fraction)*this / operand;
}

MyMath::ComplexNumber MyMath::NaturalNumber::operator/(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this / operand;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator%(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber result = *this;
	MyMath::Bits bitsOne = MyMath::Bits(1);
	bitsOne.setBit(0, true);
	const MyMath::NaturalNumber one = MyMath::NaturalNumber(bitsOne);
	if(operand.getBits().getSize() == 0)
	{
		std::cerr << "operand.getBits().getSize() == 0 @ MyMath::NaturalNumber MyMath::NaturalNumber::operator%(MyMath::NaturalNumber operand)const" << std::endl;
		return result;
	}
	if(*this < operand)return *this;
	for(MyMath::BitsSizeType i = this->getBits().getSize() - operand.getBits().getSize(); i <= this->getBits().getSize() - operand.getBits().getSize(); i--)if(result >= (operand << i))
	{
		result = result - (operand << i);
	}
	return result;
}

MyMath::Integer MyMath::NaturalNumber::operator%(MyMath::Integer operand)const
{
	return (MyMath::Integer)*this % operand;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator++(void)
{
	MyMath::Bits bitsOne = MyMath::Bits(1);
	bitsOne.setBit(0, true);
	const MyMath::NaturalNumber one = MyMath::NaturalNumber(bitsOne);
	*this += one;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator++(int)
{
	MyMath::NaturalNumber result = *this;
	MyMath::Bits bitsOne = MyMath::Bits(1);
	bitsOne.setBit(0, true);
	const MyMath::NaturalNumber one = MyMath::NaturalNumber(bitsOne);
	*this += one;
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator--(void)
{
	MyMath::Bits bitsOne = MyMath::Bits(1);
	bitsOne.setBit(0, true);
	const MyMath::NaturalNumber one = MyMath::NaturalNumber(bitsOne);
	*this -= one;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator--(int)
{
	MyMath::NaturalNumber result = *this;
	MyMath::Bits bitsOne = MyMath::Bits(1);
	bitsOne.setBit(0, true);
	const MyMath::NaturalNumber one = MyMath::NaturalNumber(bitsOne);
	*this -= one;
	return result;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator&=(MyMath::NaturalNumber operand)
{
	*this = *this & operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator&=(MyMath::Bits operand)
{
	this->setBits(this->getBits() & operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator|=(MyMath::NaturalNumber operand)
{
	*this = *this | operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator|=(MyMath::Bits operand)
{
	this->setBits(this->getBits() | operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator^=(MyMath::NaturalNumber operand)
{
	*this = *this ^ operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator^=(MyMath::Bits operand)
{
	this->setBits(this->getBits() ^ operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator<<=(MyMath::BitsSizeType operand)
{
	*this = *this << operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator>>=(MyMath::BitsSizeType operand)
{
	*this = *this >> operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator+=(MyMath::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator+=(MyMath::Integer operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Integer)*this + operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator+=(MyMath::Fraction operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Fraction)*this + operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator+=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::ComplexNumber)*this + operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator-=(MyMath::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator-=(MyMath::Integer operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Integer)*this - operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator-=(MyMath::Fraction operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Fraction)*this - operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator-=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::ComplexNumber)*this - operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator*=(MyMath::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator*=(MyMath::Integer operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Integer)*this * operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator*=(MyMath::Fraction operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Fraction)*this * operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator*=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::ComplexNumber)*this * operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator/=(MyMath::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator/=(MyMath::Integer operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Integer)*this / operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator/=(MyMath::Fraction operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Fraction)*this / operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator/=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::ComplexNumber)*this / operand);
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator%=(MyMath::NaturalNumber operand)
{
	*this = *this % operand;
	return *this;
}

MyMath::NaturalNumber MyMath::NaturalNumber::operator%=(MyMath::Integer operand)
{
	*this = (MyMath::NaturalNumber)((MyMath::Integer)*this % operand);
	return *this;
}

bool MyMath::NaturalNumber::operator==(MyMath::NaturalNumber operand)const
{
	return this->getBits() == operand.getBits();
}

bool MyMath::NaturalNumber::operator==(MyMath::Integer operand)const
{
	return operand == *this;
}

bool MyMath::NaturalNumber::operator==(MyMath::Fraction operand)const
{
	return operand == *this;
}

bool MyMath::NaturalNumber::operator==(MyMath::ComplexNumber operand)const
{
	return operand == *this;
}

bool MyMath::NaturalNumber::operator!=(MyMath::NaturalNumber operand)const
{
	return !(*this == operand);
}

bool MyMath::NaturalNumber::operator!=(MyMath::Integer operand)const
{
	return operand != *this;
}

bool MyMath::NaturalNumber::operator!=(MyMath::Fraction operand)const
{
	return operand != *this;
}

bool MyMath::NaturalNumber::operator!=(MyMath::ComplexNumber operand)const
{
	return operand != *this;
}

bool MyMath::NaturalNumber::operator>(MyMath::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return true;
	if(this->getBits().getSize() < operand.getBits().getSize())return false;
	for(MyMath::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return true;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return false;
	return false;
}

bool MyMath::NaturalNumber::operator>(MyMath::Integer operand)const
{
	return operand < *this;
}

bool MyMath::NaturalNumber::operator>(MyMath::Fraction operand)const
{
	return operand < *this;
}

bool MyMath::NaturalNumber::operator<(MyMath::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return false;
	if(this->getBits().getSize() < operand.getBits().getSize())return true;
	for(MyMath::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return false;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return true;
	return false;
}

bool MyMath::NaturalNumber::operator<(MyMath::Integer operand)const
{
	return operand > *this;
}

bool MyMath::NaturalNumber::operator<(MyMath::Fraction operand)const
{
	return operand > *this;
}

bool MyMath::NaturalNumber::operator>=(MyMath::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return true;
	if(this->getBits().getSize() < operand.getBits().getSize())return false;
	for(MyMath::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return true;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return false;
	return true;
}

bool MyMath::NaturalNumber::operator>=(MyMath::Integer operand)const
{
	return operand <= *this;
}

bool MyMath::NaturalNumber::operator>=(MyMath::Fraction operand)const
{
	return operand <= *this;
}

bool MyMath::NaturalNumber::operator<=(MyMath::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return false;
	if(this->getBits().getSize() < operand.getBits().getSize())return true;
	for(MyMath::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return false;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return true;
	return true;
}

bool MyMath::NaturalNumber::operator<=(MyMath::Integer operand)const
{
	return operand >= *this;
}

bool MyMath::NaturalNumber::operator<=(MyMath::Fraction operand)const
{
	return operand >= *this;
}

bool MyMath::NaturalNumber::operator!(void)const
{
	MyMath::Bits bitZero = MyMath::Bits("0");
	const MyMath::NaturalNumber zero = MyMath::NaturalNumber(bitZero);
	if(*this == zero)return true;
	return false;
}

MyMath::NaturalNumber::operator MyMath::Integer(void)const
{
	return MyMath::Integer(MyMath::plus, *this);
}

MyMath::NaturalNumber::operator MyMath::Fraction(void)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::Fraction(MyMath::plus, *this, one);
}

MyMath::NaturalNumber::operator MyMath::ComplexNumber(void)const
{
	MyMath::Fraction zero;
	MyMath::NaturalNumber one;
	zero = "0/1";
	one = "1";
	return MyMath::ComplexNumber(MyMath::Fraction(MyMath::plus, *this, one), zero);
}

MyMath::NaturalNumber::operator std::string(void)const
{
	std::string result = "";
	MyMath::NaturalNumber copyThis = *this;
	MyMath::Bits bitTen;
	bitTen = "0101";
	const MyMath::NaturalNumber ten = MyMath::NaturalNumber(bitTen);
	const MyMath::NaturalNumber zero = MyMath::NaturalNumber();
	if(copyThis == zero)return "0";
	while(copyThis != zero)
	{
		char c = 0;
		for(MyMath::BitsSizeType i = (copyThis % ten).getBits().getSize() - 1; i < (copyThis % ten).getBits().getSize(); i--)
		{
			c *= 2;
			if((copyThis % ten).getBits().getBit(i))c++;
		}
		c += '0';
		result = c + result;
		copyThis /= ten;
	}
	return result;
}

std::istream &MyMath::operator>>(std::istream &is, MyMath::NaturalNumber &naturalNumber)
{
	std::string str;
	is >> str;
	for(std::string::size_type i = 0; i < str.size(); i++)if(str.c_str()[i] < '0' || '9' < str.c_str()[i])
	{
		std::cerr << "Input data is not a natural number. @ std::istream &MyMath::operator>>(std::istream &is, MyMath::NaturalNumber &naturalNumber)" << std::endl;
		naturalNumber = "0";
		return is;
	}
	naturalNumber = str;
	return is;
}

std::ostream &MyMath::operator<<(std::ostream &os,const MyMath::NaturalNumber &naturalNumber)
{
	std::string output = "";
	MyMath::NaturalNumber copyNaturalNumber = naturalNumber;
	MyMath::Bits bitTen;
	bitTen = "0101";
	const MyMath::NaturalNumber ten = MyMath::NaturalNumber(bitTen);
	const MyMath::NaturalNumber zero = MyMath::NaturalNumber();
	if(copyNaturalNumber == zero)
	{
		os << "0";
		return os;
	}
	while(copyNaturalNumber != zero)
	{
		char c = 0;
		for(MyMath::BitsSizeType i = (copyNaturalNumber % ten).getBits().getSize() - 1; i < (copyNaturalNumber % ten).getBits().getSize(); i--)
		{
			c *= 2;
			if((copyNaturalNumber % ten).getBits().getBit(i))c++;
		}
		c += '0';
		output = c + output;
		copyNaturalNumber /= ten;
	}
	os << output;
	return os;
}

MyMath::Sign MyMath::Integer::getSign(void)const
{
	return this->sign;
}

MyMath::NaturalNumber MyMath::Integer::getAbsoluteValue(void)const
{
	return this->absoluteValue;
}

void MyMath::Integer::setSign(MyMath::Sign sign)
{
	this->sign = sign;
	return;
}

void MyMath::Integer::setAbsoluteValue(MyMath::NaturalNumber absoluteValue)
{
	this->absoluteValue = absoluteValue;
	return;
}

MyMath::Integer::Integer(void)
{
	this->setSign(true);
	this->setAbsoluteValue(MyMath::NaturalNumber());
	return;
}

MyMath::Integer::Integer(MyMath::Sign sign, MyMath::NaturalNumber absoluteValue)
{
	this->setSign(sign);
	this->setAbsoluteValue(absoluteValue);
	return;
}

MyMath::Integer::Integer(const MyMath::Integer &object)
{
	this->setSign(object.getSign());
	this->setAbsoluteValue(object.getAbsoluteValue());
	return;
}

MyMath::Integer MyMath::Integer::operator=(MyMath::Integer operand)
{
	this->setSign(operand.getSign());
	this->setAbsoluteValue(operand.getAbsoluteValue());
	return *this;
}

MyMath::Integer MyMath::Integer::operator=(MyMath::NaturalNumber operand)
{
	this->setSign(true);
	this->setAbsoluteValue(operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator=(MyMath::Fraction operand)
{
	*this = (MyMath::Integer)operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::Integer)operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator=(std::string operand)
{
	MyMath::NaturalNumber absoluteValue;
	MyMath::NaturalNumber zero;
	zero = "0";
	if(operand.substr(0,1) == "-")
	{
		this->setSign(false);
		absoluteValue = operand.substr(1, operand.size() - 1);
		if(absoluteValue == zero)this->setSign(true);
	}
	else
	{
		this->setSign(true);
		absoluteValue = operand;
	}
	this->setAbsoluteValue(absoluteValue);
	return *this;
}

MyMath::Integer MyMath::Integer::operator+(MyMath::Integer operand)const
{
	MyMath::Sign sign;
	MyMath::NaturalNumber absoluteValue;
	if(this->getAbsoluteValue() > operand.getAbsoluteValue())sign = this->getSign();
	else if(this->getAbsoluteValue() < operand.getAbsoluteValue())sign = operand.getSign();
	else if(this->getSign() == operand.getSign())sign = this->getSign();
	else sign = MyMath::plus;
	if(this->getSign() == operand.getSign())absoluteValue = this->getAbsoluteValue() + operand.getAbsoluteValue();
	else if(this->getAbsoluteValue() > operand.getAbsoluteValue())absoluteValue = this->getAbsoluteValue() - operand.getAbsoluteValue();
	else absoluteValue = operand.getAbsoluteValue() - this->getAbsoluteValue();
	return MyMath::Integer(sign, absoluteValue);
}

MyMath::Integer MyMath::Integer::operator+(MyMath::NaturalNumber operand)const
{
	if(this->getSign() == MyMath::plus)return MyMath::Integer(MyMath::plus, this->getAbsoluteValue() + operand);
	else if(this->getAbsoluteValue() > operand)return MyMath::Integer(MyMath::minus, this->getAbsoluteValue() - operand);
	else return MyMath::Integer(MyMath::plus, operand - this->getAbsoluteValue());
}

MyMath::Fraction MyMath::Integer::operator+(MyMath::Fraction operand)const
{
	return operand + *this;
}

MyMath::ComplexNumber MyMath::Integer::operator+(MyMath::ComplexNumber operand)const
{
	return operand + *this;
}

MyMath::Integer MyMath::Integer::operator-(MyMath::Integer operand)const
{
	MyMath::Sign sign;
	MyMath::NaturalNumber absoluteValue;
	if(this->getAbsoluteValue() > operand.getAbsoluteValue())sign = this->getSign();
	else if(this->getAbsoluteValue() < operand.getAbsoluteValue())sign = !operand.getSign();
	else if(this->getSign() == operand.getSign())sign = MyMath::plus;
	else sign = this->getSign();
	if(this->getSign() != operand.getSign())absoluteValue = this->getAbsoluteValue() + operand.getAbsoluteValue();
	else if(this->getAbsoluteValue() > operand.getAbsoluteValue())absoluteValue = this->getAbsoluteValue() - operand.getAbsoluteValue();
	else absoluteValue = operand.getAbsoluteValue() - this->getAbsoluteValue();
	return MyMath::Integer(sign, absoluteValue);
}

MyMath::Integer MyMath::Integer::operator-(MyMath::NaturalNumber operand)const
{
	if(this->getSign())
		if(this->getAbsoluteValue() >= operand)return MyMath::Integer(MyMath::plus, this->getAbsoluteValue() - operand);
		else return MyMath::Integer(MyMath::minus, operand - this->getAbsoluteValue());
	else return MyMath::Integer(MyMath::minus, this->getAbsoluteValue() + operand);
}

MyMath::Fraction MyMath::Integer::operator-(MyMath::Fraction operand)const
{
	return (MyMath::Fraction)*this - operand;
}

MyMath::ComplexNumber MyMath::Integer::operator-(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this - operand;
}

MyMath::Integer MyMath::Integer::operator*(MyMath::Integer operand)const
{
	MyMath::Integer result = MyMath::Integer(this->getSign() == operand.getSign() ? MyMath::plus : MyMath::minus, this->getAbsoluteValue() * operand.getAbsoluteValue());
	MyMath::NaturalNumber zero;
	zero = "0";
	if(result.getAbsoluteValue() == zero)result.setSign(MyMath::plus);
	return result;
}

MyMath::Integer MyMath::Integer::operator*(MyMath::NaturalNumber operand)const
{
	MyMath::Integer result = MyMath::Integer(this->getSign(), this->getAbsoluteValue() * operand);
	MyMath::NaturalNumber zero;
	zero = "0";
	if(result.getAbsoluteValue() == zero)result.setSign(MyMath::plus);
	return result;
}

MyMath::Fraction MyMath::Integer::operator*(MyMath::Fraction operand)const
{
	return operand * *this;
}

MyMath::ComplexNumber MyMath::Integer::operator*(MyMath::ComplexNumber operand)const
{
	return operand * *this;
}

MyMath::Integer MyMath::Integer::operator/(MyMath::Integer operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::Integer(this->getSign() == operand.getSign() ? MyMath::plus : MyMath::minus, this->getSign() == MyMath::plus ? this->getAbsoluteValue() / operand.getAbsoluteValue() : this->getAbsoluteValue() / operand.getAbsoluteValue() + one);
}

MyMath::Integer MyMath::Integer::operator/(MyMath::NaturalNumber operand)const
{
	MyMath::Integer result = MyMath::Integer(this->getSign(), this->getAbsoluteValue() / operand);
	MyMath::NaturalNumber zero;
	zero = "0";
	if(result.getAbsoluteValue() == zero)result.setSign(MyMath::plus);
	return result;
}

MyMath::Fraction MyMath::Integer::operator/(MyMath::Fraction operand)const
{
	return (MyMath::Fraction)*this / operand;
}

MyMath::ComplexNumber MyMath::Integer::operator/(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this / operand;
}

MyMath::Integer MyMath::Integer::operator%(MyMath::Integer operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::Integer(MyMath::plus, this->getSign() == MyMath::plus ? this->getAbsoluteValue() % operand.getAbsoluteValue() : this->getAbsoluteValue() % operand.getAbsoluteValue() + one);
}

MyMath::Integer MyMath::Integer::operator%(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::Integer(MyMath::plus, this->getSign() == MyMath::plus ? this->getAbsoluteValue() % operand : this->getAbsoluteValue() % operand + one);
	return *this - *this / operand * operand;
}

MyMath::Integer MyMath::Integer::operator+=(MyMath::Integer operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator+=(MyMath::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator+=(MyMath::Fraction operand)
{
	*this = (MyMath::Integer)((MyMath::Fraction)*this + operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator+=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::Integer)((MyMath::ComplexNumber)*this + operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator-=(MyMath::Integer operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator-=(MyMath::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator-=(MyMath::Fraction operand)
{
	*this = (MyMath::Integer)((MyMath::Fraction)*this - operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator-=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::Integer)((MyMath::ComplexNumber)*this - operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator*=(MyMath::Integer operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator*=(MyMath::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator*=(MyMath::Fraction operand)
{
	*this = (MyMath::Integer)((MyMath::Fraction)*this * operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator*=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::Integer)((MyMath::ComplexNumber)*this * operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator/=(MyMath::Integer operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator/=(MyMath::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator/=(MyMath::Fraction operand)
{
	*this = (MyMath::Integer)((MyMath::Fraction)*this / operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator/=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::Integer)((MyMath::ComplexNumber)*this / operand);
	return *this;
}

MyMath::Integer MyMath::Integer::operator%=(MyMath::Integer operand)
{
	*this = *this % operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator%=(MyMath::NaturalNumber operand)
{
	*this = *this % operand;
	return *this;
}

MyMath::Integer MyMath::Integer::operator++(void)
{
	MyMath::Integer one;
	one = "1";
	*this += one;
	return *this;
}

MyMath::Integer MyMath::Integer::operator++(int)
{
	MyMath::Integer result = *this;
	MyMath::Integer one;
	one = "1";
	*this += one;
	return result;
}

MyMath::Integer MyMath::Integer::operator--(void)
{
	MyMath::Integer one;
	one = "1";
	*this -= one;
	return *this;
}

MyMath::Integer MyMath::Integer::operator--(int)
{
	MyMath::Integer result = *this;
	MyMath::Integer one;
	one = "1";
	*this -= one;
	return result;
}

bool MyMath::Integer::operator==(MyMath::Integer operand)const
{
	return this->getSign() == operand.getSign() && this->getAbsoluteValue() == operand.getAbsoluteValue();
}

bool MyMath::Integer::operator==(MyMath::NaturalNumber operand)const
{
	return this->getSign() == MyMath::plus && this->getAbsoluteValue() == operand;
}

bool MyMath::Integer::operator==(MyMath::Fraction operand)const
{
	return operand == *this;
}

bool MyMath::Integer::operator==(MyMath::ComplexNumber operand)const
{
	return operand == *this;
}

bool MyMath::Integer::operator!=(MyMath::Integer operand)const
{
	return this->getSign() != operand.getSign() || this->getAbsoluteValue() != operand.getAbsoluteValue();
}

bool MyMath::Integer::operator!=(MyMath::NaturalNumber operand)const
{
	return this->getSign() == MyMath::minus || this->getAbsoluteValue() != operand;
}

bool MyMath::Integer::operator!=(MyMath::Fraction operand)const
{
	return operand != *this;
}

bool MyMath::Integer::operator!=(MyMath::ComplexNumber operand)const
{
	return operand != *this;
}

bool MyMath::Integer::operator>(MyMath::Integer operand)const
{
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::plus)return this->getAbsoluteValue() > operand.getAbsoluteValue();
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::minus)return true;
	if(this->getSign() == MyMath::minus && operand.getSign() == MyMath::plus)return false;
	else return this->getAbsoluteValue() < operand.getAbsoluteValue();
}

bool MyMath::Integer::operator>(MyMath::NaturalNumber operand)const
{
	if(this->getSign() == MyMath::plus)return this->getAbsoluteValue() > operand;
	else return false;
}

bool MyMath::Integer::operator>(MyMath::Fraction operand)const
{
	return operand < *this;
}

bool MyMath::Integer::operator<(MyMath::Integer operand)const
{
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::plus)return this->getAbsoluteValue() < operand.getAbsoluteValue();
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::minus)return false;
	if(this->getSign() == MyMath::minus && operand.getSign() == MyMath::plus)return true;
	else return this->getAbsoluteValue() > operand.getAbsoluteValue();
}

bool MyMath::Integer::operator<(MyMath::NaturalNumber operand)const
{
	if(this->getSign() == MyMath::plus)return this->getAbsoluteValue() < operand;
	else return true;
}

bool MyMath::Integer::operator<(MyMath::Fraction operand)const
{
	return operand > *this;
}

bool MyMath::Integer::operator>=(MyMath::Integer operand)const
{
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::plus)return this->getAbsoluteValue() >= operand.getAbsoluteValue();
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::minus)return true;
	if(this->getSign() == MyMath::minus && operand.getSign() == MyMath::plus)return false;
	else return this->getAbsoluteValue() <= operand.getAbsoluteValue();
}

bool MyMath::Integer::operator>=(MyMath::NaturalNumber operand)const
{
	if(this->getSign() == MyMath::plus)return this->getAbsoluteValue() >= operand;
	else return false;
}

bool MyMath::Integer::operator>=(MyMath::Fraction operand)const
{
	return operand <= *this;
}

bool MyMath::Integer::operator<=(MyMath::Integer operand)const
{
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::plus)return this->getAbsoluteValue() <= operand.getAbsoluteValue();
	if(this->getSign() == MyMath::plus && operand.getSign() == MyMath::minus)return false;
	if(this->getSign() == MyMath::minus && operand.getSign() == MyMath::plus)return true;
	else return this->getAbsoluteValue() >= operand.getAbsoluteValue();
}

bool MyMath::Integer::operator<=(MyMath::NaturalNumber operand)const
{
	//return *this < operand || *this == operand;
	if(this->getSign() == MyMath::plus)return this->getAbsoluteValue() <= operand;
	else return true;
}

bool MyMath::Integer::operator<=(MyMath::Fraction operand)const
{
	return operand >= *this;
}

bool MyMath::Integer::operator!(void)const
{
	MyMath::Integer zero;
	zero = "0";
	return *this == zero;
}

MyMath::Integer::operator MyMath::NaturalNumber(void)const
{
	MyMath::Integer integerZero;
	MyMath::NaturalNumber naturalNumberZero;
	integerZero = "0";
	naturalNumberZero = "0";
	if(*this < integerZero)
	{
		std::cerr << "*this < zero @ MyMath::Integer::operator MyMath::NaturalNumber(void)const" << std::endl;
		return naturalNumberZero;
	}
	return this->getAbsoluteValue();
}

MyMath::Integer::operator MyMath::Fraction(void)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::Fraction(this->getSign(), this->getAbsoluteValue(), one);
}

MyMath::Integer::operator MyMath::ComplexNumber(void)const
{
	MyMath::NaturalNumber one;
	MyMath::Fraction zero;
	one = "1";
	zero = "0/1";
	return MyMath::ComplexNumber(MyMath::Fraction(this->getSign(), this->getAbsoluteValue(), one), zero);
}

MyMath::Integer::operator std::string(void)const
{
	std::string result = "";
	if(!this->getSign())result = "-";
	result = result + (std::string)this->getAbsoluteValue();
	return result;
}

std::istream &MyMath::operator>>(std::istream &is, MyMath::Integer &integer)
{
	std::string str;
	is >> str;
	if(str.c_str()[0] != '-' && (str.c_str()[0] < '0' || '9' < str.c_str()[0]))
	{
		std::cerr << "Input data is not an integer. @ std::istream &MyMath::operator>>(std::istream &is, MyMath::Integer &integer)" << std::endl;
		integer = "0";
		return is;
	}
	for(std::string::size_type i = 1; i < str.size(); i++)if(str.c_str()[i] < '0' || '9' < str.c_str()[i])
	{
		std::cerr << "Input data is not an integer. @ std::istream &MyMath::operator>>(std::istream &is, MyMath::Integer &integer)" << std::endl;
		integer = "0";
		return is;
	}
	integer = str;
	return is;
}

std::ostream &MyMath::operator<<(std::ostream &os, const MyMath::Integer &integer)
{
	if(integer.getSign() == MyMath::minus)os << "-";
	os << integer.getAbsoluteValue();
	return os;
}

MyMath::Sign MyMath::Fraction::getSign(void)const
{
	return this->sign;
}

MyMath::NaturalNumber MyMath::Fraction::getNumerator(void)const
{
	return this->numerator;
}

MyMath::NaturalNumber MyMath::Fraction::getDenominator(void)const
{
	return this->denominator;
}

void MyMath::Fraction::setSign(MyMath::Sign newSign)
{
	this->sign = newSign;
	return;
}

void MyMath::Fraction::setNumerator(MyMath::NaturalNumber newNumerator)
{
	this->numerator = newNumerator;
	return;
}

void MyMath::Fraction::setDenominator(MyMath::NaturalNumber newDenominator)
{
	MyMath::NaturalNumber zero;
	zero = "0";
	if(newDenominator == zero)
	{
		std::cerr << "newDenominator == zero @ void MyMath::Fraction::setDenominator(MyMath::NaturalNumber newDenominator)" << std::endl;
		return;
	}
	this->denominator = newDenominator;
	return;
}

void MyMath::Fraction::reduce(void)
{
	MyMath::NaturalNumber numerator = this->numerator;
	MyMath::NaturalNumber denominator = this->denominator;
	MyMath::NaturalNumber zero;
	MyMath::NaturalNumber one;
	zero = "0";
	one = "1";
	if(numerator == zero)
	{
		this->setSign(MyMath::plus);
		this->setNumerator(zero);
		this->setDenominator(one);
		return;
	}
	while(numerator != denominator)
		if(numerator > denominator)
		{
			numerator %= denominator;
			if(numerator == zero)numerator = denominator;
		}
		else
		{
			denominator %= numerator;
			if(denominator == zero)denominator = numerator;
		}
	this->setNumerator(this->getNumerator() / numerator);
	this->setDenominator(this->getDenominator() / numerator);
	return;
}

MyMath::Fraction::Fraction(void)
{
	MyMath::NaturalNumber zero;
	MyMath::NaturalNumber one;
	zero = "0";
	one = "1";
	this->setSign(MyMath::plus);
	this->setNumerator(zero);
	this->setDenominator(one);
}

MyMath::Fraction::Fraction(MyMath::Sign sign, MyMath::NaturalNumber numerator, MyMath::NaturalNumber denominator)
{
	MyMath::NaturalNumber zero;
	zero = "0";
	if(denominator == zero)
	{
		std::cerr << "denominator == zero @ MyMath::Fraction::Fraction(MyMath::Sign sign, MyMath::NaturalNumber numerator, MyMath::NaturalNumber denominator)" << std::endl;
		denominator = "1";
	}
	if(!sign && numerator == zero)
	{
		std::cerr << "!sign && numerator == zero @ MyMath::Fraction::Fraction(MyMath::Sign sign, MyMath::NaturalNumber numerator, MyMath::NaturalNumber denominator)" << std::endl;
		sign = MyMath::plus;
	}
	this->setSign(sign);
	this->setNumerator(numerator);
	this->setDenominator(denominator);
	this->reduce();
}

MyMath::Fraction::Fraction(const MyMath::Fraction &object)
{
	this->setSign(object.getSign());
	this->setNumerator(object.getNumerator());
	this->setDenominator(object.getDenominator());
}

MyMath::Fraction MyMath::Fraction::operator=(MyMath::Fraction operand)
{
	this->setSign(operand.getSign());
	this->setNumerator(operand.getNumerator());
	this->setDenominator(operand.getDenominator());
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator=(MyMath::NaturalNumber operand)
{
	MyMath::NaturalNumber denominator;
	denominator = "1";
	this->setSign(MyMath::plus);
	this->setNumerator(operand);
	this->setDenominator(denominator);
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator=(MyMath::Integer operand)
{
	MyMath::NaturalNumber numerator, denominator;
	MyMath::Integer zero;
	denominator = "1";
	zero = "0";
	this->setSign(operand >= zero ? MyMath::plus : MyMath::minus);
	this->setNumerator((MyMath::NaturalNumber)operand);
	this->setDenominator(denominator);
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator=(MyMath::ComplexNumber operand)
{
	*this = (MyMath::Fraction)operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator=(std::string operand)
{
	std::string::size_type cursor = 0;
	std::string::size_type readSlash = 0;
	MyMath::NaturalNumber numerator;
	MyMath::NaturalNumber denominator;
	while(cursor < operand.size())if((cursor == 0 && operand[cursor] != '-'  && (operand[cursor] < '0' || operand[cursor] > '9')) || (cursor != 0 && !readSlash && operand[cursor] != '/' && (operand[cursor] < '0' || operand[cursor] > '9')) || (readSlash && (operand[cursor] < '0' || operand[cursor] > '9')))
	{
		std::cerr << "Input is wrong @ MyMath::Fraction MyMath::Fraction::operator=(std::string operand)" << std::endl;
		return *this;
	}
	else if(operand[cursor] == '/')
	{
		readSlash = cursor;
		cursor++;
	}
	else cursor++;
	if(!readSlash)
	{
		std::cerr << "Input is wrong @ std::istream &MyMath::operator=(std::istream &is, MyMath::Fraction &fraction)" << std::endl;
		return *this;
	}
	if(operand.substr(0, 1) == "-")
	{
		this->setSign(MyMath::minus);
		operand = operand.substr(1, operand.size() - 1);
		readSlash--;
	}
	else this->setSign(MyMath::plus);
	numerator = operand.substr(0, readSlash);
	denominator = operand.substr(readSlash + 1, operand.size() - readSlash - 1);
	this->setNumerator(numerator);
	this->setDenominator(denominator);
	this->reduce();
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator+(MyMath::Fraction operand)const
{
	MyMath::Fraction result;
	MyMath::Fraction copyThis;
	MyMath::Fraction copyOperand;
	MyMath::Integer resultNumerator;
	MyMath::Integer thisNumerator;
	MyMath::Integer operandNumerator;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	copyThis = *this;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	copyThis.setNumerator(copyThis.getNumerator() * copyOperand.getDenominator());
	copyThis.setDenominator(copyThis.getDenominator() * copyOperand.getDenominator());
	copyOperand.setNumerator(copyOperand.getNumerator() * this->getDenominator());
	copyOperand.setDenominator(copyThis.getDenominator());
	thisNumerator = MyMath::Integer(copyThis.getSign(), copyThis.getNumerator());
	operandNumerator = MyMath::Integer(copyOperand.getSign(), copyOperand.getNumerator());
	resultNumerator = thisNumerator + operandNumerator;
	result = MyMath::Fraction(resultNumerator >= zero ? MyMath::plus : MyMath::minus, (MyMath::NaturalNumber)(resultNumerator >= zero ? resultNumerator : minusOne * resultNumerator), copyThis.getDenominator());
	result.reduce();
	return result;
}

MyMath::Fraction MyMath::Fraction::operator+(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this + MyMath::Fraction(MyMath::plus, operand, one);
}

MyMath::Fraction MyMath::Fraction::operator+(MyMath::Integer operand)const
{
	MyMath::Fraction copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= minusOne;
	}
	return *this + MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, one);
}

MyMath::ComplexNumber MyMath::Fraction::operator+(MyMath::ComplexNumber operand)const
{
	return operand + *this;
}

MyMath::Fraction MyMath::Fraction::operator-(MyMath::Fraction operand)const
{
	MyMath::Fraction result;
	MyMath::Fraction copyThis;
	MyMath::Fraction copyOperand;
	MyMath::Integer resultNumerator;
	MyMath::Integer thisNumerator;
	MyMath::Integer operandNumerator;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	copyThis = *this;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	copyThis.setNumerator(copyThis.getNumerator() * copyOperand.getDenominator());
	copyThis.setDenominator(copyThis.getDenominator() * copyOperand.getDenominator());
	copyOperand.setNumerator(copyOperand.getNumerator() * this->getDenominator());
	copyOperand.setDenominator(copyThis.getDenominator());
	thisNumerator = MyMath::Integer(copyThis.getSign(), copyThis.getNumerator());
	operandNumerator = MyMath::Integer(copyOperand.getSign(), copyOperand.getNumerator());
	resultNumerator = thisNumerator - operandNumerator;
	result = MyMath::Fraction(resultNumerator >= zero ? MyMath::plus : MyMath::minus, (MyMath::NaturalNumber)(resultNumerator >= zero ? resultNumerator : minusOne * resultNumerator), copyThis.getDenominator());
	result.reduce();
	return result;
}


MyMath::Fraction MyMath::Fraction::operator-(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this - MyMath::Fraction(MyMath::plus, operand, one);
}


MyMath::Fraction MyMath::Fraction::operator-(MyMath::Integer operand)const
{
	MyMath::Fraction copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= minusOne;
	}
	return *this - MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, one);
}

MyMath::ComplexNumber MyMath::Fraction::operator-(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this - operand;
}

MyMath::Fraction MyMath::Fraction::operator*(MyMath::Fraction operand)const
{
	MyMath::Fraction result = MyMath::Fraction(MyMath::plus, this->getNumerator() * operand.getNumerator(), this->getDenominator() * operand.getDenominator());
	MyMath::NaturalNumber zero;
	zero = "0";
	if(result.getNumerator() != zero && this->getSign() != operand.getSign())result.setSign(MyMath::minus);
	result.reduce();
	return result;
}

MyMath::Fraction MyMath::Fraction::operator*(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this * MyMath::Fraction(MyMath::plus, operand, one);
}

MyMath::Fraction MyMath::Fraction::operator*(MyMath::Integer operand)const
{
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= minusOne;
	}
	return *this * MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, one);
}

MyMath::ComplexNumber MyMath::Fraction::operator*(MyMath::ComplexNumber operand)const
{
	return operand * *this;
}

MyMath::Fraction MyMath::Fraction::operator/(MyMath::Fraction operand)const
{
	MyMath::NaturalNumber zero;
	MyMath::NaturalNumber one;
	zero = "0";
	one = "1";
	if(operand.getNumerator() == zero)
	{
		std::cerr << "operand == zero @ MyMath::Fraction MyMath::Fraction::operator/(const MyMath::Fraction operand)const" << std::endl;
		return MyMath::Fraction(MyMath::plus, zero, one);
	}
	return *this * MyMath::Fraction(operand.getSign(), operand.getDenominator(), operand.getNumerator());
}

MyMath::Fraction MyMath::Fraction::operator/(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber zero;
	MyMath::NaturalNumber one;
	zero = "0";
	one = "1";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MyMath::Fraction MyMath::Fraction::operator/(MyMath::NaturalNumber operand)const" << std::endl;
		return MyMath::Fraction(MyMath::plus, zero, one);
	}
	return *this / MyMath::Fraction(MyMath::plus, operand, one);
}

MyMath::Fraction MyMath::Fraction::operator/(MyMath::Integer operand)const
{
	MyMath::Fraction copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MyMath::Fraction MyMath::Fraction::operator/(MyMath::Integer operand)const" << std::endl;
		return MyMath::Fraction(MyMath::plus, (MyMath::NaturalNumber)zero, one);
	}
	if(operand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= minusOne;
	}
	return *this / MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, one);
}

MyMath::ComplexNumber MyMath::Fraction::operator/(MyMath::ComplexNumber operand)const
{
	return (MyMath::ComplexNumber)*this / operand;
}

MyMath::Fraction MyMath::Fraction::operator+=(MyMath::Fraction operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator+=(MyMath::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator+=(MyMath::Integer operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator+=(MyMath::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MyMath::Fraction MyMath::Fraction::operator+=(MyMath::ComplexNumber operand)" << std::endl;
	*this = *this + (MyMath::Fraction)operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator-=(MyMath::Fraction operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator-=(MyMath::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator-=(MyMath::Integer operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator-=(MyMath::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MyMath::Fraction MyMath::Fraction::operator+=(MyMath::ComplexNumber operand)" << std::endl;
	*this = *this - (MyMath::Fraction)operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator*=(MyMath::Fraction operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator*=(MyMath::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator*=(MyMath::Integer operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator*=(MyMath::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MyMath::Fraction MyMath::Fraction::operator+=(MyMath::ComplexNumber operand)" << std::endl;
	*this = *this * (MyMath::Fraction)operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator/=(MyMath::Fraction operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator/=(MyMath::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator/=(MyMath::Integer operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator/=(MyMath::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MyMath::Fraction MyMath::Fraction::operator+=(MyMath::ComplexNumber operand)" << std::endl;
	*this = *this / (MyMath::Fraction)operand;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator++(void)
{
	MyMath::Fraction one;
	one = "1/1";
	*this += one;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator++(int)
{
	MyMath::Fraction result = *this;
	MyMath::Fraction one;
	one = "1/1";
	*this += one;
	return result;
}

MyMath::Fraction MyMath::Fraction::operator--(void)
{
	MyMath::Fraction one;
	one = "1/1";
	*this -= one;
	return *this;
}

MyMath::Fraction MyMath::Fraction::operator--(int)
{
	MyMath::Fraction result = *this;
	MyMath::Fraction one;
	one = "1/1";
	*this += one;
	return result;
}

bool MyMath::Fraction::operator==(MyMath::Fraction operand)const
{
	return this->getSign() == operand.getSign() && this->getNumerator() == operand.getNumerator() && this->getDenominator() == operand.getDenominator();
}

bool MyMath::Fraction::operator==(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this == MyMath::Fraction(MyMath::plus, operand, one);
}

bool MyMath::Fraction::operator==(MyMath::Integer operand)const
{
	MyMath::Integer copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		copyOperand *= minusOne;
	}
	return *this == MyMath::Fraction(operandSign, (MyMath::NaturalNumber)copyOperand, one);
}

bool MyMath::Fraction::operator==(MyMath::ComplexNumber operand)const
{
	return operand == *this;
}

bool MyMath::Fraction::operator!=(MyMath::Fraction operand)const
{
	return this->getSign() != operand.getSign() || this->getNumerator() != operand.getNumerator() || this->getDenominator() != operand.getDenominator();
}

bool MyMath::Fraction::operator!=(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this != MyMath::Fraction(MyMath::plus, operand, one);
}

bool MyMath::Fraction::operator!=(MyMath::Integer operand)const
{
	MyMath::Integer copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		copyOperand *= minusOne;
	}
	return *this != MyMath::Fraction(operandSign, (MyMath::NaturalNumber)copyOperand, one);
}

bool MyMath::Fraction::operator!=(MyMath::ComplexNumber operand)const
{
	return operand != *this;
}

bool MyMath::Fraction::operator>(MyMath::Fraction operand)const
{
	if(this->getSign() == MyMath::plus)
		if(operand.getSign() == MyMath::plus)return this->getNumerator() * operand.getDenominator() > operand.getNumerator() * this->getDenominator();
		else return true;
	else
		if(operand.getSign() == MyMath::plus)return false;
		else return this->getNumerator() * operand.getDenominator() < operand.getNumerator() * this->getDenominator();
}

bool MyMath::Fraction::operator>(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this > MyMath::Fraction(MyMath::plus, operand, one);
}

bool MyMath::Fraction::operator>(MyMath::Integer operand)const
{
	MyMath::Integer copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		copyOperand *= minusOne;
	}
	return *this > MyMath::Fraction(operandSign, (MyMath::NaturalNumber)copyOperand, one);
}

bool MyMath::Fraction::operator<(MyMath::Fraction operand)const
{
	if(this->getSign() == MyMath::plus)
		if(operand.getSign() == MyMath::plus)return this->getNumerator() * operand.getDenominator() < operand.getNumerator() * this->getDenominator();
		else return false;
	else
		if(operand.getSign() == MyMath::plus)return true;
		else return this->getNumerator() * operand.getDenominator() > operand.getNumerator() * this->getDenominator();
}

bool MyMath::Fraction::operator<(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this < MyMath::Fraction(MyMath::plus, operand, one);
}

bool MyMath::Fraction::operator<(MyMath::Integer operand)const
{
	MyMath::Integer copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		copyOperand *= minusOne;
	}
	return *this < MyMath::Fraction(operandSign, (MyMath::NaturalNumber)copyOperand, one);
}

bool MyMath::Fraction::operator>=(MyMath::Fraction operand)const
{
	if(this->getSign() == MyMath::plus)
		if(operand.getSign() == MyMath::plus)return this->getNumerator() * operand.getDenominator() >= operand.getNumerator() * this->getDenominator();
		else return true;
	else
		if(operand.getSign() == MyMath::plus)return false;
		else return this->getNumerator() * operand.getDenominator() <= operand.getNumerator() * this->getDenominator();
}

bool MyMath::Fraction::operator>=(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this >= MyMath::Fraction(MyMath::plus, operand, one);
}

bool MyMath::Fraction::operator>=(MyMath::Integer operand)const
{
	MyMath::Integer copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		copyOperand *= minusOne;
	}
	return *this >= MyMath::Fraction(operandSign, (MyMath::NaturalNumber)copyOperand, one);
}

bool MyMath::Fraction::operator<=(MyMath::Fraction operand)const
{
	if(this->getSign() == MyMath::plus)
		if(operand.getSign() == MyMath::plus)return this->getNumerator() * operand.getDenominator() <= operand.getNumerator() * this->getDenominator();
		else return false;
	else
		if(operand.getSign() == MyMath::plus)return true;
		else return this->getNumerator() * operand.getDenominator() >= operand.getNumerator() * this->getDenominator();
}

bool MyMath::Fraction::operator<=(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return *this <= MyMath::Fraction(MyMath::plus, operand, one);
}

bool MyMath::Fraction::operator<=(MyMath::Integer operand)const
{
	MyMath::Integer copyOperand;
	MyMath::Integer zero;
	MyMath::Integer minusOne;
	MyMath::NaturalNumber one;
	MyMath::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		copyOperand *= minusOne;
	}
	return *this <= MyMath::Fraction(operandSign, (MyMath::NaturalNumber)copyOperand, one);
}

bool MyMath::Fraction::operator!(void)const
{
	MyMath::Fraction zero;
	zero = "0/1";
	return *this == zero;
}

MyMath::Fraction::operator MyMath::NaturalNumber(void)const
{
	MyMath::NaturalNumber result = this->getNumerator() / this->getDenominator();
	MyMath::NaturalNumber one;
	one = "1";
	if(*this != MyMath::Fraction(MyMath::plus, result, one))std::cerr << "A value has been changed. @ MyMath::Fraction::operator MyMath::NaturalNumber(void)const" << std::endl;
	return result;
}

MyMath::Fraction::operator MyMath::Integer(void)const
{
	MyMath::NaturalNumber one;
	MyMath::NaturalNumber zero;
	one = "1";
	zero = "0";
	if(*this != MyMath::Fraction(this->getSign(), this->getNumerator() / this->getDenominator(), one))std::cerr << "A value has been changed. @ MyMath::Fraction::operator MyMath::Integer(void)const" << std::endl;
	return MyMath::Integer(this->getNumerator() / this->getDenominator() ==zero ? MyMath::plus : this->getSign(), this->getNumerator() / this->getDenominator());
}

MyMath::Fraction::operator MyMath::ComplexNumber(void)const
{
	MyMath::Fraction zero;
	zero = "0/1";
	return MyMath::ComplexNumber(*this, zero);
}

MyMath::Fraction::operator std::string(void)const
{
	std::string result = "";
	if(this->getSign() == MyMath::minus)result = "-";
	result = result + (std::string)this->getNumerator() + "/" + (std::string)this->getDenominator();
	return result;
}

std::string MyMath::Fraction::toDecimal(unsigned int digit)const
{
	std::string result = "";
	MyMath::NaturalNumber numerator = this->getNumerator();
	MyMath::NaturalNumber ten;
	ten = "10";
	if(this->getSign() == MyMath::minus)result = "-";
	result = result + (std::string)(this->getNumerator() / this->getDenominator()) + ".";
	for(unsigned int i = 0; i < digit; i++)
	{
		numerator = ten * (numerator % this->getDenominator());
		result = result + (std::string)(numerator / this->getDenominator());
	}
	return result;
}

std::istream &MyMath::operator>>(std::istream &is, MyMath::Fraction &fraction)
{
	std::string str;
	std::string::size_type cursor = 0;
	std::string::size_type readSlash = 0;
	MyMath::NaturalNumber numerator;
	MyMath::NaturalNumber denominator;
	is >> str;
	while(cursor < str.size())if((cursor == 0 && str[cursor] != '-'  && (str[cursor] < '0' || str[cursor] > '9')) || (cursor != 0 && !readSlash && str[cursor] != '/' && (str[cursor] < '0' || str[cursor] > '9')) || (readSlash && (str[cursor] < '0' || str[cursor] > '9')))
	{
		std::cerr << "Input is wrong @ std::istream &MyMath::operator>>(std::istream &is, MyMath::Fraction &fraction)" << std::endl;
		return is;
	}
	else if(str[cursor] == '/')
	{
		readSlash = cursor;
		cursor++;
	}
	else cursor++;
	if(!readSlash)
	{
		std::cerr << "Input is wrong @ std::istream &MyMath::operator>>(std::istream &is, MyMath::Fraction &fraction)" << std::endl;
		return is;
	}
	if(str.substr(0, 1) == "-")
	{
		fraction.setSign(MyMath::minus);
		str = str.substr(1, str.size() - 1);
		readSlash--;
	}
	else fraction.setSign(MyMath::plus);
	numerator = str.substr(0, readSlash);
	denominator = str.substr(readSlash + 1, str.size() - readSlash - 1);
	fraction.setNumerator(numerator);
	fraction.setDenominator(denominator);
	fraction.reduce();
	return is;
}

std::ostream &MyMath::operator<<(std::ostream &os, const MyMath::Fraction &fraction)
{
	if(fraction.getSign() == MyMath::minus)os << "-";
	os << fraction.getNumerator() << "/" << fraction.getDenominator();
	return os;
}

MyMath::Fraction MyMath::ComplexNumber::getRealPart(void)const
{
	return this->realPart;
}

MyMath::Fraction MyMath::ComplexNumber::getImaginaryPart(void)const
{
	return this->imaginaryPart;
}

void MyMath::ComplexNumber::setRealPart(const MyMath::Fraction &realPart)
{
	this->realPart = realPart;
	return;
}

void MyMath::ComplexNumber::setImaginaryPart(const MyMath::Fraction &imaginaryPart)
{
	this->imaginaryPart = imaginaryPart;
	return;
}

MyMath::ComplexNumber::ComplexNumber(void)
{
	MyMath::Fraction zero;
	zero = "0/1";
	this->setRealPart(zero);
	this->setImaginaryPart(zero);
	return;
}

MyMath::ComplexNumber::ComplexNumber(MyMath::Fraction realPart, MyMath::Fraction imaginaryPart)
{
	this->setRealPart(realPart);
	this->setImaginaryPart(imaginaryPart);
	return;
}

MyMath::ComplexNumber::ComplexNumber(const MyMath::ComplexNumber &object)
{
	this->setRealPart(object.getRealPart());
	this->setImaginaryPart(object.getImaginaryPart());
	return;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator=(MyMath::ComplexNumber operand)
{
	this->setRealPart(operand.getRealPart());
	this->setImaginaryPart(operand.getImaginaryPart());
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator=(MyMath::NaturalNumber operand)
{
	MyMath::NaturalNumber zero;
	MyMath::NaturalNumber one;
	zero = "0";
	one = "1";
	this->setRealPart(MyMath::Fraction(MyMath::plus, operand, one));
	this->setImaginaryPart(MyMath::Fraction(MyMath::plus, zero, one));
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator=(MyMath::Integer operand)
{
	MyMath::Integer integerZero;
	MyMath::Integer integerMinusOne;
	MyMath::NaturalNumber naturalNumberZero;
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Sign realPartSign;
	integerZero = "0";
	integerMinusOne = "-1";
	naturalNumberZero = "0";
	naturalNumberOne = "1";
	if(operand >= integerZero)realPartSign = MyMath::plus;
	else
	{
		operand *= integerMinusOne;
		realPartSign = MyMath::minus;
	}
	this->setRealPart(MyMath::Fraction(realPartSign, (MyMath::NaturalNumber)operand, naturalNumberOne));
	this->setImaginaryPart(MyMath::Fraction(MyMath::plus, naturalNumberZero, naturalNumberOne));
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator=(MyMath::Fraction operand)
{
	MyMath::Fraction zero;
	zero = "0/1";
	this->setRealPart(operand);
	this->setImaginaryPart(zero);
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator=(std::string operand)
{
	std::string::size_type cursor = 0;
	std::string::size_type readSign = 0;
	MyMath::Fraction realPart;
	MyMath::Fraction imaginaryPart;
	while(cursor < operand.size())
		if(operand[cursor] == '+' || operand[cursor] == '-')readSign = cursor++;
		else cursor++;
	if(!readSign || operand[operand.size() - 1] != 'i')
	{
		std::cerr << "Input is wrong @ MyMath::ComplexNumber MyMath::ComplexNumber::operator=(std::string operand)" << std::endl;
		return *this;
	}
	realPart = operand.substr(0, readSign);
	if(operand[readSign] == '+')imaginaryPart = operand.substr(readSign + 1, operand.size() - readSign - 2);
	if(operand[readSign] == '-')imaginaryPart = operand.substr(readSign, operand.size() - readSign - 1);
	this->setRealPart(realPart);
	this->setImaginaryPart(imaginaryPart);
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+(MyMath::ComplexNumber operand)const
{
	return MyMath::ComplexNumber(this->getRealPart() + operand.getRealPart(), this->getImaginaryPart() + operand.getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::ComplexNumber(this->getRealPart() + MyMath::Fraction(MyMath::plus, operand, one), this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+(MyMath::Integer operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Integer integerZero;
	MyMath::Integer integerMinusOne;
	MyMath::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand >= integerZero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= integerMinusOne;
	}
	return MyMath::ComplexNumber(this->getRealPart() + MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, naturalNumberOne), this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+(MyMath::Fraction operand)const
{
	return MyMath::ComplexNumber(this->getRealPart() + operand, this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-(MyMath::ComplexNumber operand)const
{
	return MyMath::ComplexNumber(this->getRealPart() - operand.getRealPart(), this->getImaginaryPart() - operand.getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::ComplexNumber(this->getRealPart() - MyMath::Fraction(MyMath::plus, operand, one), this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-(MyMath::Integer operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Integer integerZero;
	MyMath::Integer integerMinusOne;
	MyMath::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand >= integerZero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= integerMinusOne;
	}
	return MyMath::ComplexNumber(this->getRealPart() - MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, naturalNumberOne), this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-(MyMath::Fraction operand)const
{
	return MyMath::ComplexNumber(this->getRealPart() - operand, this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*(MyMath::ComplexNumber operand)const
{
	return MyMath::ComplexNumber(this->getRealPart() * operand.getRealPart() - this->getImaginaryPart() * operand.getImaginaryPart(), this->getRealPart() * operand.getImaginaryPart() + operand.getRealPart() * this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	one = "1";
	return MyMath::ComplexNumber(MyMath::Fraction(MyMath::plus, operand, one) * this->getRealPart(), MyMath::Fraction(MyMath::plus, operand, one) * this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*(MyMath::Integer operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Integer integerZero;
	MyMath::Integer integerMinusOne;
	MyMath::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand >= integerZero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= integerMinusOne;
	}
	return MyMath::ComplexNumber(MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, naturalNumberOne) * this->getRealPart(), MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, naturalNumberOne) * this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*(MyMath::Fraction operand)const
{
	return MyMath::ComplexNumber(operand * this->getRealPart(), operand * this->getImaginaryPart());
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::ComplexNumber operand)const
{
	MyMath::Fraction tre = this->getRealPart();
	MyMath::Fraction tim = this->getImaginaryPart();
	MyMath::Fraction ore = operand.getRealPart();
	MyMath::Fraction oim = operand.getImaginaryPart();
	MyMath::Fraction zero;
	zero = "0/1";
	if(ore == zero && oim == zero)
	{
		std::cerr << "operand == zero @ MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::ComplexNumber operand)const" << std::endl;
		return MyMath::ComplexNumber(zero, zero);
	}
	return MyMath::ComplexNumber((tre * ore + tim * oim) / (ore * ore + oim * oim), (tim * ore - tre * oim) / (ore * ore + oim * oim));
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber one;
	MyMath::NaturalNumber zero;
	one = "1";
	zero = "0";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::NaturalNumber operand)const" << std::endl;
		return MyMath::ComplexNumber(MyMath::Fraction(MyMath::plus, zero, one), MyMath::Fraction(MyMath::plus, zero, one));
	}
	return MyMath::ComplexNumber(this->getRealPart() / MyMath::Fraction(MyMath::plus, operand, one), this->getImaginaryPart() / MyMath::Fraction(MyMath::plus, operand, one));
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::Integer operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::NaturalNumber naturalNumberZero;
	MyMath::Integer integerZero;
	MyMath::Integer integerMinusOne;
	MyMath::Sign operandSign;
	naturalNumberOne = "1";
	naturalNumberZero = "0";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand == integerZero)
	{
		std::cerr << "operand == zero @ MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::Integer operand)const" << std::endl;
		return MyMath::ComplexNumber(MyMath::Fraction(MyMath::plus, naturalNumberZero, naturalNumberOne), MyMath::Fraction(MyMath::plus, naturalNumberZero, naturalNumberOne));
	}
	if(operand >= integerZero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= integerMinusOne;
	}
	return MyMath::ComplexNumber(this->getRealPart() / MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, naturalNumberOne), this->getImaginaryPart() / MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand , naturalNumberOne));
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::Fraction operand)const
{
	MyMath::Fraction zero;
	zero = "0/1";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MyMath::ComplexNumber MyMath::ComplexNumber::operator/(MyMath::Fraction operand)const" << std::endl;
		return MyMath::ComplexNumber(zero, zero);
	}
	return MyMath::ComplexNumber(this->getRealPart() / operand, this->getImaginaryPart() / operand);
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+=(MyMath::ComplexNumber operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+=(MyMath::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+=(MyMath::Integer operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator+=(MyMath::Fraction operand)
{
	*this = *this + operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-=(MyMath::ComplexNumber operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-=(MyMath::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-=(MyMath::Integer operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator-=(MyMath::Fraction operand)
{
	*this = *this - operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*=(MyMath::ComplexNumber operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*=(MyMath::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*=(MyMath::Integer operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator*=(MyMath::Fraction operand)
{
	*this = *this * operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/=(MyMath::ComplexNumber operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/=(MyMath::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/=(MyMath::Integer operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator/=(MyMath::Fraction operand)
{
	*this = *this / operand;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator++(void)
{
	MyMath::ComplexNumber one;
	one = "1/1+0/1i";
	*this += one;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator++(int)
{
	MyMath::ComplexNumber result = *this;
	MyMath::ComplexNumber one;
	one = "1/1+0/1i";
	*this += one;
	return result;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator--(void)
{
	MyMath::ComplexNumber one;
	one = "1/1+0/1i";
	*this -= one;
	return *this;
}

MyMath::ComplexNumber MyMath::ComplexNumber::operator--(int)
{
	MyMath::ComplexNumber result = *this;
	MyMath::ComplexNumber one;
	one = "1/1+0/1i";
	*this -= one;
	return result;
}

bool MyMath::ComplexNumber::operator==(MyMath::ComplexNumber operand)const
{
	return this->getRealPart() == operand.getRealPart() && this->getImaginaryPart() == operand.getImaginaryPart();
}

bool MyMath::ComplexNumber::operator==(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Fraction fractionZero;
	naturalNumberOne = "1";
	fractionZero = "0/1";
	return this->getRealPart() == MyMath::Fraction(MyMath::plus, operand, naturalNumberOne) && this->getImaginaryPart() == fractionZero;
}

bool MyMath::ComplexNumber::operator==(MyMath::Integer operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Integer integerZero;
	MyMath::Integer integerMinusOne;
	MyMath::Fraction fractionZero;
	MyMath::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	fractionZero = "0/1";
	if(operand >= integerZero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= integerMinusOne;
	}
	return this->getRealPart() == MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, naturalNumberOne) && this->getImaginaryPart() == fractionZero;
}

bool MyMath::ComplexNumber::operator==(MyMath::Fraction operand)const
{
	MyMath::Fraction fractionZero;
	fractionZero = "0/1";
	return this->getRealPart() == operand && this->getImaginaryPart() == fractionZero;
}

bool MyMath::ComplexNumber::operator!=(MyMath::ComplexNumber operand)const
{
	return this->getRealPart() != operand.getRealPart() || this->getImaginaryPart() != operand.getImaginaryPart();
}

bool MyMath::ComplexNumber::operator!=(MyMath::NaturalNumber operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Fraction fractionZero;
	naturalNumberOne = "1";
	fractionZero = "0/1";
	return this->getRealPart() != MyMath::Fraction(MyMath::plus, operand, naturalNumberOne) || this->getImaginaryPart() != fractionZero;
}

bool MyMath::ComplexNumber::operator!=(MyMath::Integer operand)const
{
	MyMath::NaturalNumber naturalNumberOne;
	MyMath::Integer integerZero;
	MyMath::Integer integerMinusOne;
	MyMath::Fraction fractionZero;
	MyMath::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	fractionZero = "0/1";
	if(operand >= integerZero)operandSign = MyMath::plus;
	else
	{
		operandSign = MyMath::minus;
		operand *= integerMinusOne;
	}
	return this->getRealPart() != MyMath::Fraction(operandSign, (MyMath::NaturalNumber)operand, naturalNumberOne) || this->getImaginaryPart() != fractionZero;
}

bool MyMath::ComplexNumber::operator!=(MyMath::Fraction operand)const
{
	MyMath::Fraction fractionZero;
	fractionZero = "0/1";
	return this->getRealPart() != operand || this->getImaginaryPart() != fractionZero;
}

MyMath::ComplexNumber::operator MyMath::NaturalNumber(void)const
{
	MyMath::Fraction fractionZero;
	MyMath::NaturalNumber naturalNumberZero;
	fractionZero = "0/1";
	naturalNumberZero = "0";
	if(this->getImaginaryPart() != fractionZero)std::cerr << "A value has been changed. @ MyMath::ComplexNumber::operator MyMath::NaturalNumber(void)const" << std::endl;
	return (MyMath::NaturalNumber)this->getRealPart();
}

MyMath::ComplexNumber::operator MyMath::Integer(void)const
{
	MyMath::NaturalNumber naturalNumberZero;
	MyMath::Fraction fractionZero;
	naturalNumberZero = "0";
	fractionZero = "0/1";
	if(this->getImaginaryPart() != fractionZero)std::cerr << "A value has been changed. @ MyMath::ComplexNumber::operator MyMath::Integer(void)const" << std::endl;
	return (MyMath::Integer)this->getRealPart();
}

MyMath::ComplexNumber::operator MyMath::Fraction(void)const
{
	MyMath::Fraction zero;
	MyMath::Fraction one;
	zero = "0/1";
	one = "1/1";
	if(this->getImaginaryPart() != zero)std::cerr << "A value has been changed. @ MyMath::ComplexNumber::operator MyMath::Fraction(void)const" << std::endl;
	return this->getRealPart();
}

MyMath::ComplexNumber::operator std::string(void)const
{
	std::string result = "";
	MyMath::Fraction zero;
	zero = "0/1";
	result = (std::string)this->getRealPart();
	if(this->getImaginaryPart() >= zero)result = result + "+";
	result = result + (std::string)this->getImaginaryPart() + "i";
	return result;
}

MyMath::ComplexNumber MyMath::ComplexNumber::conjugate(void)const
{
	MyMath::ComplexNumber minusOne;
	minusOne = "-1/1+0/1i";
	return MyMath::ComplexNumber(this->getRealPart(), minusOne * this->getImaginaryPart());
}

std::string MyMath::ComplexNumber::toDecimal(unsigned int digit)const
{
	MyMath::Fraction zero;
	zero = "0/1";
	return this->getRealPart().toDecimal(digit) + (this->getImaginaryPart() >= zero ? "+" : "") + this->getImaginaryPart().toDecimal(digit) + "i";
}

std::istream &MyMath::operator>>(std::istream &is, MyMath::ComplexNumber &complexNumber)
{
	std::string str;
	std::string::size_type cursor = 0;
	std::string::size_type readSign = 0;
	MyMath::Fraction realPart;
	MyMath::Fraction imaginaryPart;
	is >> str;
	while(cursor < str.size())
		if(str[cursor] == '+' || str[cursor] == '-')readSign = cursor++;
		else cursor++;
	if(!readSign || str[str.size() - 1] != 'i')
	{
		std::cerr << "Input is wrong @ std::istream &MyMath::operator>>(std::istream &is, MyMath::ComplexNumber &complexNumber)" << std::endl;
		return is;
	}
	realPart = str.substr(0, readSign);
	if(str[readSign] == '+')imaginaryPart = str.substr(readSign + 1, str.size() - readSign - 2);
	if(str[readSign] == '-')imaginaryPart = str.substr(readSign, str.size() - readSign - 1);
	complexNumber.setRealPart(realPart);
	complexNumber.setImaginaryPart(imaginaryPart);
	return is;
}

std::ostream &MyMath::operator<<(std::ostream &os, const MyMath::ComplexNumber &complexNumber)
{
	MyMath::Fraction zero;
	zero = "0/1";
	os << complexNumber.getRealPart();
	if(complexNumber.getImaginaryPart() >= zero)os << "+";
	os << complexNumber.getImaginaryPart() << "i";
	return os;
}

