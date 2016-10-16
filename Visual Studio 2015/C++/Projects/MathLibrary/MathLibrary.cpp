#include<climits>
#include<iostream>
#include<string>
#include"MathLibrary.h"

#ifdef MYMATH_DEBUG
std::string MathLibrary::Bits::getBitTest(MathLibrary::BitsSizeType position)const
{
	if(position < this->size)
	{
		MathLibrary::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
		MathLibrary::BitsSizeType elementPosition = position / elementSize;
		MathLibrary::BitsSizeType bitPosition = position % elementSize;
		if((this->data[elementPosition] & (1 << bitPosition)) >> bitPosition)return "1";
		else return "0";
	}
	else return "null";
}
#endif

MathLibrary::Bits::Bits(void)
{
	this->size = 0;
	this->data = new MathLibrary::BitsDataType(0);
	return;
}

MathLibrary::Bits::Bits(MathLibrary::BitsSizeType size)
{
	MathLibrary::BitsSizeType elementSize = sizeof(MathLibrary::BitsDataType) * CHAR_BIT;
	this->size = size;
	this->data = new MathLibrary::BitsDataType[size / elementSize + 1];
	for(MathLibrary::BitsSizeType i = 0; i <= size / elementSize; i++)this->data[i] = 0;
	return;
}

MathLibrary::Bits::Bits(std::string data)
{
	this->size = 0;
	this->data = new MathLibrary::BitsDataType(0);
	*this = data;
	return;
}

MathLibrary::Bits::Bits(const MathLibrary::Bits &object)
{
	MathLibrary::BitsSizeType elementSize = sizeof(MathLibrary::BitsDataType) * CHAR_BIT;
	this->size = object.size;
	this->data = new MathLibrary::BitsDataType[this->size / elementSize + 1];
	for(MathLibrary::BitsSizeType i = 0; i < this->size / elementSize + 1; i++)this->data[i] = object.data[i];
	return;
}

MathLibrary::Bits::~Bits()
{
	if(this->data != NULL)
	{
		delete [] this->data;
		this->data = NULL;
	}
	return;
}

bool MathLibrary::Bits::getBit(MathLibrary::BitsSizeType position)const
{
	if(position < this->size)
	{
		MathLibrary::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
		MathLibrary::BitsSizeType elementPosition = position / elementSize;
		MathLibrary::BitsSizeType bitPosition = position % elementSize;
		if((this->data[elementPosition] & (1 << bitPosition)) >> bitPosition)return true;
		else return false;
	}
	else
	{
		std::cerr << "position>=this->size @ bool MathLibrary::Bits::getBit(MathLibrary::BitsSizeType position)" << std::endl;
		std::cerr << "position == " << position << std::endl;
		std::cerr << "this->size == " << this->size << std::endl;
		return false;
	}
}

void MathLibrary::Bits::setBit(MathLibrary::BitsSizeType position, bool value)
{
	if(position < this->size)
	{
		if(value != this->getBit(position))
		{
			MathLibrary::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
			MathLibrary::BitsSizeType elementPosition = position / elementSize;
			MathLibrary::BitsSizeType bitPosition = position % elementSize;
			if(value)this->data[elementPosition] += 1 << bitPosition;
			else this->data[elementPosition] -= 1 << bitPosition;
		}
	}
	else
	{
		std::cerr << "position>=this->size @ void MathLibrary::Bits::setBit(MathLibrary::BitsSizeType position, bool value)" << std::endl;
		std::cerr << "position == " << position << std::endl;
		std::cerr << "this->size == " << this->size << std::endl;
	}
	return;
}

MathLibrary::BitsSizeType MathLibrary::Bits::getSize(void)const
{
	return this->size;
}

void MathLibrary::Bits::setSize(MathLibrary::BitsSizeType size)
{
	MathLibrary::BitsSizeType lastSize = this->size;
	MathLibrary::BitsSizeType elementSize = sizeof(this->data[0]) * CHAR_BIT;
	if(size / elementSize > this->size / elementSize)
	{
		MathLibrary::BitsDataType *newdata;
		newdata = new MathLibrary::BitsDataType[size / elementSize + 1];
		for(MathLibrary::BitsSizeType i = 0; i <= this->size / elementSize; i++)newdata[i] = this->data[i];
		for(MathLibrary::BitsSizeType i = this->size / elementSize + 1; i <= size / elementSize; i++)newdata[i] = 0;
		if(this->data != NULL)delete [] this->data;
		this->data = newdata;
	}
	else if(size / elementSize < this->size / elementSize)
	{
		MathLibrary::BitsDataType *newdata;
		newdata = new MathLibrary::BitsDataType[size / elementSize + 1];
		for(MathLibrary::BitsSizeType i = 0; i <= size / elementSize; i++)newdata[i] = this->data[i];
		delete [] this->data;
		this->data = newdata;
	}
	this->size = elementSize * (size / elementSize + 1);
	if(size > lastSize)for(MathLibrary::BitsSizeType i = lastSize; i < size; i++)this->setBit(i, false);
	this->size = size;
	return;
}

MathLibrary::Bits MathLibrary::Bits::operator=(MathLibrary::Bits operand)
{
	MathLibrary::Bits result(operand);
	this->setSize(operand.getSize());
	for(MathLibrary::BitsSizeType i = 0; i < this->getSize(); i++)this->setBit(i, operand.getBit(i));
	return result;
}

MathLibrary::Bits MathLibrary::Bits::operator=(std::string operand)
{
	for(std::string::size_type i = 0; i < operand.size(); i++)if(operand.substr(i, 1) != "0" && operand.substr(i, 1) != "1")
	{
		std::cerr << "An operand is not binary. @ MathLibrary::Bits MathLibrary::Bits::operator=(std::string operand)" << std::endl;
		this->setSize(0);
		return *this;
	}
	this->setSize(operand.size());
	for(MathLibrary::BitsSizeType i = 0; i < this->getSize(); i++)this->setBit(i, (operand.substr(i, 1) == "1") ? true : false);
	return *this;
}

MathLibrary::Bits MathLibrary::Bits::operator~(void)const
{
	MathLibrary::Bits result(this->getSize());
	for(MathLibrary::BitsSizeType i = 0; i < result.getSize(); i++)result.setBit(i, this->getBit(i) ? false : true);
	return result;
}

MathLibrary::Bits MathLibrary::Bits::operator&(MathLibrary::Bits operand)const
{
	MathLibrary::Bits result((this->getSize() < operand.getSize()) ? this->getSize() : operand.getSize());
	for(MathLibrary::BitsSizeType i = 0; i < result.getSize(); i++)result.setBit(i, this->getBit(i) & operand.getBit(i));
	return result;
}

MathLibrary::Bits MathLibrary::Bits::operator|(MathLibrary::Bits operand)const
{
	MathLibrary::Bits larger = (this->getSize() >= operand.getSize()) ? *this : operand;
	MathLibrary::Bits smaller = (this->getSize() < operand.getSize()) ? *this : operand;
	MathLibrary::Bits result(larger.getSize());
	for(MathLibrary::BitsSizeType i = 0; i < smaller.getSize(); i++)result.setBit(i, larger.getBit(i) | smaller.getBit(i));
	for(MathLibrary::BitsSizeType i = smaller.getSize(); i < larger.getSize(); i++)result.setBit(i, larger.getBit(i));
	return result;
}

MathLibrary::Bits MathLibrary::Bits::operator^(MathLibrary::Bits operand)const
{
	MathLibrary::Bits larger = (this->getSize() >= operand.getSize()) ? *this : operand;
	MathLibrary::Bits smaller = (this->getSize() < operand.getSize()) ? *this : operand;
	MathLibrary::Bits result(larger.getSize());
	for(MathLibrary::BitsSizeType i = 0; i < smaller.getSize(); i++)result.setBit(i, larger.getBit(i) ^ smaller.getBit(i));
	for(MathLibrary::BitsSizeType i = smaller.getSize(); i < larger.getSize(); i++)result.setBit(i, larger.getBit(i));
	return result;
}

MathLibrary::Bits MathLibrary::Bits::operator<<(MathLibrary::BitsSizeType operand)const
{
	MathLibrary::Bits result(this->getSize() + operand);
	for(MathLibrary::BitsSizeType i = 0; i < operand; i++)result.setBit(i, false);
	for(MathLibrary::BitsSizeType i = 0; i < this->getSize(); i++)result.setBit(operand + i, this->getBit(i));
	return result;
}

MathLibrary::Bits MathLibrary::Bits::operator>>(MathLibrary::BitsSizeType operand)const
{
	if(this->getSize() <= operand)return MathLibrary::Bits(0);
	MathLibrary::Bits result(this->getSize() - operand);
	for(MathLibrary::BitsSizeType i = 0; i < result.getSize(); i++)result.setBit(i, this->getBit(i + operand));
	return result;
}

MathLibrary::Bits MathLibrary::Bits::operator&=(MathLibrary::Bits operand)
{
	*this = *this & operand;
	return *this;
}

MathLibrary::Bits MathLibrary::Bits::operator|=(MathLibrary::Bits operand)
{
	*this = *this | operand;
	return *this;
}

MathLibrary::Bits MathLibrary::Bits::operator^=(MathLibrary::Bits operand)
{
	*this = *this ^ operand;
	return *this;
}

MathLibrary::Bits MathLibrary::Bits::operator<<=(MathLibrary::BitsSizeType operand)
{
	*this = *this << operand;
	return *this;
}

MathLibrary::Bits MathLibrary::Bits::operator>>=(MathLibrary::BitsSizeType operand)
{
	*this = *this >> operand;
	return *this;
}

bool MathLibrary::Bits::operator==(MathLibrary::Bits operand)const
{
	if(this->getSize() != operand.getSize())return false;
 	for(MathLibrary::BitsSizeType i = 0; i < this->getSize(); i++)if(this->getBit(i) != operand.getBit(i))return false;
	return true;
}

bool MathLibrary::Bits::operator!=(MathLibrary::Bits operand)const
{
	if(this->getSize() != operand.getSize())return true;
 	for(MathLibrary::BitsSizeType i = 0; i < this->getSize(); i++)if(this->getBit(i) != operand.getBit(i))return true;
	return false;
}

MathLibrary::Bits::operator std::string(void)const
{
	std::string result = "";
	for(MathLibrary::BitsSizeType i = 0; i < this->getSize(); i++)
		if(this->getBit(i))result = result + "1";
		else result = result + "0";
	return result;
}

std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::Bits &bits)
{
	std::string str;
	is >> str;
	for(std::string::size_type i = 0; i < str.size(); i++)if(str.substr(i, 1) != "0" && str.substr(i, 1) != "1")
	{
		std::cerr << "Input data is not a binary. @ std::istream &MathLibrary::operator(std::istream &is, const MathLibrary::Bits &bits)" << std::endl;
		bits.setSize(0);
		return is;
	}
	bits = str;
	return is;
}

std::ostream &MathLibrary::operator<<(std::ostream &os, const MathLibrary::Bits &bits)
{
	for(MathLibrary::BitsSizeType i = 0; i < bits.getSize(); i++)
		if(bits.getBit(i))os << "1";
		else os << "0";
	return os;
}

MathLibrary::Bits MathLibrary::NaturalNumber::getBits(void)const
{
	return this->bits;
}

void MathLibrary::NaturalNumber::setBits(MathLibrary::Bits bits)
{
	this->bits = bits;
	this->cutExtraZeros();
	return;
}

void MathLibrary::NaturalNumber::cutExtraZeros(void)
{
	MathLibrary::BitsSizeType countExtraZeros = 0;
	for(MathLibrary::BitsSizeType i = this->bits.getSize() - 1; i < this->bits.getSize(); i--)
		if(!this->bits.getBit(i))countExtraZeros++;
		else break;
	this->bits.setSize(this->bits.getSize() - countExtraZeros);
	return;
}

MathLibrary::NaturalNumber::NaturalNumber(void)
{
	this->setBits(MathLibrary::Bits());
	return;
}

MathLibrary::NaturalNumber::NaturalNumber(MathLibrary::Bits data)
{
	this->setBits(data);
	this->cutExtraZeros();
	return;
}

MathLibrary::NaturalNumber::NaturalNumber(const MathLibrary::NaturalNumber &object)
{
	this->setBits(object.getBits());
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator=(MathLibrary::NaturalNumber operand)
{
	this->setBits(operand.getBits());
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator=(MathLibrary::Integer operand)
{
	*this = (MathLibrary::NaturalNumber)operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::NaturalNumber)operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::NaturalNumber)operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator=(MathLibrary::Bits operand)
{
	this->setBits(operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator=(std::string operand)
{
	MathLibrary::Bits bitTen;
	bitTen = "0101";
	const MathLibrary::NaturalNumber ten = MathLibrary::NaturalNumber(bitTen);
	this->setBits(MathLibrary::Bits());
	for(std::string::size_type i = 0; i < operand.size(); i++)if(operand.c_str()[i] < '0' || '9' < operand.c_str()[i])
	{
		std::cerr << "operand is not natural number. @ MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator=(std::string operand)" << std::endl;
		return *this;
	}
	for(std::string::size_type i = 0; i < operand.size(); i++)
	{
		*this *= ten;
		for(char j = operand.c_str()[i]; j != '0'; j--)(*this)++;
	}
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator~(void)const
{
	MathLibrary::NaturalNumber result(~this->getBits());
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator&(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() & operand.getBits());
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator&(MathLibrary::Bits operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() & operand);
	result.cutExtraZeros();
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator|(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() | operand.getBits());
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator|(MathLibrary::Bits operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() | operand);
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator^(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() ^ operand.getBits());
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator^(MathLibrary::Bits operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() ^ operand);
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator<<(MathLibrary::BitsSizeType operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() << operand);
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator>>(MathLibrary::BitsSizeType operand)const
{
	MathLibrary::NaturalNumber result(this->getBits() >> operand);
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator+(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::Bits longerBits = (this->getBits().getSize() >= operand.getBits().getSize()) ? this->getBits() : operand.getBits();
	MathLibrary::Bits shorterBits = (this->getBits().getSize() < operand.getBits().getSize()) ? this->getBits() : operand.getBits();
	MathLibrary::Bits resultBits(longerBits.getSize() + 1);
	bool carry = false;
	for(MathLibrary::BitsSizeType i = 0; i < shorterBits.getSize(); i++)
	{
		resultBits.setBit(i, carry ^ longerBits.getBit(i) ^ shorterBits.getBit(i));
		carry = (longerBits.getBit(i) & shorterBits.getBit(i)) | (carry & longerBits.getBit(i)) | (carry & shorterBits.getBit(i));
	}
	for(MathLibrary::BitsSizeType i = shorterBits.getSize(); i < longerBits.getSize(); i++)
	{
		resultBits.setBit(i, carry ^ longerBits.getBit(i));
		carry = carry & longerBits.getBit(i);
	}
	resultBits.setBit(resultBits.getSize() - 1, carry);
	return MathLibrary::NaturalNumber(resultBits);
}

MathLibrary::Integer MathLibrary::NaturalNumber::operator+(MathLibrary::Integer operand)const
{
	return (MathLibrary::Integer)*this + operand;
}

MathLibrary::Fraction MathLibrary::NaturalNumber::operator+(MathLibrary::Fraction operand)const
{
	return (MathLibrary::Fraction)*this + operand;
}

MathLibrary::ComplexNumber MathLibrary::NaturalNumber::operator+(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this + operand;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator-(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::Bits largerBits = (*this >= operand) ? this->getBits() : operand.getBits();
	MathLibrary::Bits smallerBits = (*this < operand) ? this->getBits() : operand.getBits();
	MathLibrary::Bits resultBits(largerBits.getSize());
	bool borrow = false;
	if(*this < operand)
	{
		std::cerr << "*this < operand @ MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator-(MathLibrary::NaturalNumber operand)const" << std::endl;
		return MathLibrary::NaturalNumber();
	}
	for(MathLibrary::BitsSizeType i = 0; i < smallerBits.getSize(); i++)
	{
		resultBits.setBit(i, borrow ^ largerBits.getBit(i) ^ smallerBits.getBit(i));
		borrow = (!largerBits.getBit(i) & smallerBits.getBit(i)) | (borrow & !largerBits.getBit(i)) | (borrow & smallerBits.getBit(i));
	}
	for(MathLibrary::BitsSizeType i = smallerBits.getSize(); i < largerBits.getSize(); i++)
	{
		resultBits.setBit(i, borrow ^ largerBits.getBit(i));
		borrow = borrow & !largerBits.getBit(i);
	}
	return MathLibrary::NaturalNumber(resultBits);
}

MathLibrary::Integer MathLibrary::NaturalNumber::operator-(MathLibrary::Integer operand)const
{
	return (MathLibrary::Integer)*this - operand;
}

MathLibrary::Fraction MathLibrary::NaturalNumber::operator-(MathLibrary::Fraction operand)const
{
	return (MathLibrary::Fraction)*this - operand;
}

MathLibrary::ComplexNumber MathLibrary::NaturalNumber::operator-(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this - operand;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator*(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber result = MathLibrary::NaturalNumber();
	for(MathLibrary::BitsSizeType i = 0; i < this->getBits().getSize(); i++)if(this->getBits().getBit(i))result = result + (operand << i);
	return result;
}

MathLibrary::Integer MathLibrary::NaturalNumber::operator*(MathLibrary::Integer operand)const
{
	return (MathLibrary::Integer)*this * operand;
}

MathLibrary::Fraction MathLibrary::NaturalNumber::operator*(MathLibrary::Fraction operand)const
{
	return (MathLibrary::Fraction)*this * operand;
}

MathLibrary::ComplexNumber MathLibrary::NaturalNumber::operator*(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this * operand;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator/(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber result = MathLibrary::NaturalNumber();
	MathLibrary::NaturalNumber copyThis = *this;
	MathLibrary::Bits bitsOne = MathLibrary::Bits(1);
	bitsOne.setBit(0, true);
	const MathLibrary::NaturalNumber one = MathLibrary::NaturalNumber(bitsOne);
	if(operand.getBits().getSize() == 0)
	{
		std::cerr << "operand.getBits().getSize() == 0 @ MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator/(MathLibrary::NaturalNumber operand)const" << std::endl;
		return result;
	}
	if(*this < operand)return result;
	for(MathLibrary::BitsSizeType i = this->getBits().getSize() - operand.getBits().getSize(); i <= this->getBits().getSize() - operand.getBits().getSize(); i--)if(copyThis >= (operand << i))
	{
		result = result + (one << i);
		copyThis = copyThis - (operand << i);
	}
	return result;
}

MathLibrary::Integer MathLibrary::NaturalNumber::operator/(MathLibrary::Integer operand)const
{
	return (MathLibrary::Integer)*this / operand;
}

MathLibrary::Fraction MathLibrary::NaturalNumber::operator/(MathLibrary::Fraction operand)const
{
	return (MathLibrary::Fraction)*this / operand;
}

MathLibrary::ComplexNumber MathLibrary::NaturalNumber::operator/(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this / operand;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator%(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber result = *this;
	MathLibrary::Bits bitsOne = MathLibrary::Bits(1);
	bitsOne.setBit(0, true);
	const MathLibrary::NaturalNumber one = MathLibrary::NaturalNumber(bitsOne);
	if(operand.getBits().getSize() == 0)
	{
		std::cerr << "operand.getBits().getSize() == 0 @ MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator%(MathLibrary::NaturalNumber operand)const" << std::endl;
		return result;
	}
	if(*this < operand)return *this;
	for(MathLibrary::BitsSizeType i = this->getBits().getSize() - operand.getBits().getSize(); i <= this->getBits().getSize() - operand.getBits().getSize(); i--)if(result >= (operand << i))
	{
		result = result - (operand << i);
	}
	return result;
}

MathLibrary::Integer MathLibrary::NaturalNumber::operator%(MathLibrary::Integer operand)const
{
	return (MathLibrary::Integer)*this % operand;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator++(void)
{
	MathLibrary::Bits bitsOne = MathLibrary::Bits(1);
	bitsOne.setBit(0, true);
	const MathLibrary::NaturalNumber one = MathLibrary::NaturalNumber(bitsOne);
	*this += one;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator++(int)
{
	MathLibrary::NaturalNumber result = *this;
	MathLibrary::Bits bitsOne = MathLibrary::Bits(1);
	bitsOne.setBit(0, true);
	const MathLibrary::NaturalNumber one = MathLibrary::NaturalNumber(bitsOne);
	*this += one;
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator--(void)
{
	MathLibrary::Bits bitsOne = MathLibrary::Bits(1);
	bitsOne.setBit(0, true);
	const MathLibrary::NaturalNumber one = MathLibrary::NaturalNumber(bitsOne);
	*this -= one;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator--(int)
{
	MathLibrary::NaturalNumber result = *this;
	MathLibrary::Bits bitsOne = MathLibrary::Bits(1);
	bitsOne.setBit(0, true);
	const MathLibrary::NaturalNumber one = MathLibrary::NaturalNumber(bitsOne);
	*this -= one;
	return result;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator&=(MathLibrary::NaturalNumber operand)
{
	*this = *this & operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator&=(MathLibrary::Bits operand)
{
	this->setBits(this->getBits() & operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator|=(MathLibrary::NaturalNumber operand)
{
	*this = *this | operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator|=(MathLibrary::Bits operand)
{
	this->setBits(this->getBits() | operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator^=(MathLibrary::NaturalNumber operand)
{
	*this = *this ^ operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator^=(MathLibrary::Bits operand)
{
	this->setBits(this->getBits() ^ operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator<<=(MathLibrary::BitsSizeType operand)
{
	*this = *this << operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator>>=(MathLibrary::BitsSizeType operand)
{
	*this = *this >> operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator+=(MathLibrary::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator+=(MathLibrary::Integer operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Integer)*this + operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator+=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Fraction)*this + operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator+=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::ComplexNumber)*this + operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator-=(MathLibrary::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator-=(MathLibrary::Integer operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Integer)*this - operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator-=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Fraction)*this - operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator-=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::ComplexNumber)*this - operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator*=(MathLibrary::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator*=(MathLibrary::Integer operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Integer)*this * operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator*=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Fraction)*this * operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator*=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::ComplexNumber)*this * operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator/=(MathLibrary::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator/=(MathLibrary::Integer operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Integer)*this / operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator/=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Fraction)*this / operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator/=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::ComplexNumber)*this / operand);
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator%=(MathLibrary::NaturalNumber operand)
{
	*this = *this % operand;
	return *this;
}

MathLibrary::NaturalNumber MathLibrary::NaturalNumber::operator%=(MathLibrary::Integer operand)
{
	*this = (MathLibrary::NaturalNumber)((MathLibrary::Integer)*this % operand);
	return *this;
}

bool MathLibrary::NaturalNumber::operator==(MathLibrary::NaturalNumber operand)const
{
	return this->getBits() == operand.getBits();
}

bool MathLibrary::NaturalNumber::operator==(MathLibrary::Integer operand)const
{
	return operand == *this;
}

bool MathLibrary::NaturalNumber::operator==(MathLibrary::Fraction operand)const
{
	return operand == *this;
}

bool MathLibrary::NaturalNumber::operator==(MathLibrary::ComplexNumber operand)const
{
	return operand == *this;
}

bool MathLibrary::NaturalNumber::operator!=(MathLibrary::NaturalNumber operand)const
{
	return !(*this == operand);
}

bool MathLibrary::NaturalNumber::operator!=(MathLibrary::Integer operand)const
{
	return operand != *this;
}

bool MathLibrary::NaturalNumber::operator!=(MathLibrary::Fraction operand)const
{
	return operand != *this;
}

bool MathLibrary::NaturalNumber::operator!=(MathLibrary::ComplexNumber operand)const
{
	return operand != *this;
}

bool MathLibrary::NaturalNumber::operator>(MathLibrary::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return true;
	if(this->getBits().getSize() < operand.getBits().getSize())return false;
	for(MathLibrary::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return true;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return false;
	return false;
}

bool MathLibrary::NaturalNumber::operator>(MathLibrary::Integer operand)const
{
	return operand < *this;
}

bool MathLibrary::NaturalNumber::operator>(MathLibrary::Fraction operand)const
{
	return operand < *this;
}

bool MathLibrary::NaturalNumber::operator<(MathLibrary::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return false;
	if(this->getBits().getSize() < operand.getBits().getSize())return true;
	for(MathLibrary::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return false;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return true;
	return false;
}

bool MathLibrary::NaturalNumber::operator<(MathLibrary::Integer operand)const
{
	return operand > *this;
}

bool MathLibrary::NaturalNumber::operator<(MathLibrary::Fraction operand)const
{
	return operand > *this;
}

bool MathLibrary::NaturalNumber::operator>=(MathLibrary::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return true;
	if(this->getBits().getSize() < operand.getBits().getSize())return false;
	for(MathLibrary::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return true;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return false;
	return true;
}

bool MathLibrary::NaturalNumber::operator>=(MathLibrary::Integer operand)const
{
	return operand <= *this;
}

bool MathLibrary::NaturalNumber::operator>=(MathLibrary::Fraction operand)const
{
	return operand <= *this;
}

bool MathLibrary::NaturalNumber::operator<=(MathLibrary::NaturalNumber operand)const
{
	if(this->getBits().getSize() > operand.getBits().getSize())return false;
	if(this->getBits().getSize() < operand.getBits().getSize())return true;
	for(MathLibrary::BitsSizeType i = this->getBits().getSize() - 1; i < this->getBits().getSize(); i--)
		if(this->getBits().getBit(i) && !operand.getBits().getBit(i))return false;
		else if(!this->getBits().getBit(i) && operand.getBits().getBit(i))return true;
	return true;
}

bool MathLibrary::NaturalNumber::operator<=(MathLibrary::Integer operand)const
{
	return operand >= *this;
}

bool MathLibrary::NaturalNumber::operator<=(MathLibrary::Fraction operand)const
{
	return operand >= *this;
}

bool MathLibrary::NaturalNumber::operator!(void)const
{
	MathLibrary::Bits bitZero = MathLibrary::Bits("0");
	const MathLibrary::NaturalNumber zero = MathLibrary::NaturalNumber(bitZero);
	if(*this == zero)return true;
	return false;
}

MathLibrary::NaturalNumber::operator MathLibrary::Integer(void)const
{
	return MathLibrary::Integer(MathLibrary::plus, *this);
}

MathLibrary::NaturalNumber::operator MathLibrary::Fraction(void)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::Fraction(MathLibrary::plus, *this, one);
}

MathLibrary::NaturalNumber::operator MathLibrary::ComplexNumber(void)const
{
	MathLibrary::Fraction zero;
	MathLibrary::NaturalNumber one;
	zero = "0/1";
	one = "1";
	return MathLibrary::ComplexNumber(MathLibrary::Fraction(MathLibrary::plus, *this, one), zero);
}

MathLibrary::NaturalNumber::operator std::string(void)const
{
	std::string result = "";
	MathLibrary::NaturalNumber copyThis = *this;
	MathLibrary::Bits bitTen;
	bitTen = "0101";
	const MathLibrary::NaturalNumber ten = MathLibrary::NaturalNumber(bitTen);
	const MathLibrary::NaturalNumber zero = MathLibrary::NaturalNumber();
	if(copyThis == zero)return "0";
	while(copyThis != zero)
	{
		char c = 0;
		for(MathLibrary::BitsSizeType i = (copyThis % ten).getBits().getSize() - 1; i < (copyThis % ten).getBits().getSize(); i--)
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

std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::NaturalNumber &naturalNumber)
{
	std::string str;
	is >> str;
	for(std::string::size_type i = 0; i < str.size(); i++)if(str.c_str()[i] < '0' || '9' < str.c_str()[i])
	{
		std::cerr << "Input data is not a natural number. @ std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::NaturalNumber &naturalNumber)" << std::endl;
		naturalNumber = "0";
		return is;
	}
	naturalNumber = str;
	return is;
}

std::ostream &MathLibrary::operator<<(std::ostream &os,const MathLibrary::NaturalNumber &naturalNumber)
{
	std::string output = "";
	MathLibrary::NaturalNumber copyNaturalNumber = naturalNumber;
	MathLibrary::Bits bitTen;
	bitTen = "0101";
	const MathLibrary::NaturalNumber ten = MathLibrary::NaturalNumber(bitTen);
	const MathLibrary::NaturalNumber zero = MathLibrary::NaturalNumber();
	if(copyNaturalNumber == zero)
	{
		os << "0";
		return os;
	}
	while(copyNaturalNumber != zero)
	{
		char c = 0;
		for(MathLibrary::BitsSizeType i = (copyNaturalNumber % ten).getBits().getSize() - 1; i < (copyNaturalNumber % ten).getBits().getSize(); i--)
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

MathLibrary::Sign MathLibrary::Integer::getSign(void)const
{
	return this->sign;
}

MathLibrary::NaturalNumber MathLibrary::Integer::getAbsoluteValue(void)const
{
	return this->absoluteValue;
}

void MathLibrary::Integer::setSign(MathLibrary::Sign sign)
{
	this->sign = sign;
	return;
}

void MathLibrary::Integer::setAbsoluteValue(MathLibrary::NaturalNumber absoluteValue)
{
	this->absoluteValue = absoluteValue;
	return;
}

MathLibrary::Integer::Integer(void)
{
	this->setSign(true);
	this->setAbsoluteValue(MathLibrary::NaturalNumber());
	return;
}

MathLibrary::Integer::Integer(MathLibrary::Sign sign, MathLibrary::NaturalNumber absoluteValue)
{
	this->setSign(sign);
	this->setAbsoluteValue(absoluteValue);
	return;
}

MathLibrary::Integer::Integer(const MathLibrary::Integer &object)
{
	this->setSign(object.getSign());
	this->setAbsoluteValue(object.getAbsoluteValue());
	return;
}

MathLibrary::Integer MathLibrary::Integer::operator=(MathLibrary::Integer operand)
{
	this->setSign(operand.getSign());
	this->setAbsoluteValue(operand.getAbsoluteValue());
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator=(MathLibrary::NaturalNumber operand)
{
	this->setSign(true);
	this->setAbsoluteValue(operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::Integer)operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::Integer)operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator=(std::string operand)
{
	MathLibrary::NaturalNumber absoluteValue;
	MathLibrary::NaturalNumber zero;
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

MathLibrary::Integer MathLibrary::Integer::operator+(MathLibrary::Integer operand)const
{
	MathLibrary::Sign sign;
	MathLibrary::NaturalNumber absoluteValue;
	if(this->getAbsoluteValue() > operand.getAbsoluteValue())sign = this->getSign();
	else if(this->getAbsoluteValue() < operand.getAbsoluteValue())sign = operand.getSign();
	else if(this->getSign() == operand.getSign())sign = this->getSign();
	else sign = MathLibrary::plus;
	if(this->getSign() == operand.getSign())absoluteValue = this->getAbsoluteValue() + operand.getAbsoluteValue();
	else if(this->getAbsoluteValue() > operand.getAbsoluteValue())absoluteValue = this->getAbsoluteValue() - operand.getAbsoluteValue();
	else absoluteValue = operand.getAbsoluteValue() - this->getAbsoluteValue();
	return MathLibrary::Integer(sign, absoluteValue);
}

MathLibrary::Integer MathLibrary::Integer::operator+(MathLibrary::NaturalNumber operand)const
{
	if(this->getSign() == MathLibrary::plus)return MathLibrary::Integer(MathLibrary::plus, this->getAbsoluteValue() + operand);
	else if(this->getAbsoluteValue() > operand)return MathLibrary::Integer(MathLibrary::minus, this->getAbsoluteValue() - operand);
	else return MathLibrary::Integer(MathLibrary::plus, operand - this->getAbsoluteValue());
}

MathLibrary::Fraction MathLibrary::Integer::operator+(MathLibrary::Fraction operand)const
{
	return operand + *this;
}

MathLibrary::ComplexNumber MathLibrary::Integer::operator+(MathLibrary::ComplexNumber operand)const
{
	return operand + *this;
}

MathLibrary::Integer MathLibrary::Integer::operator-(MathLibrary::Integer operand)const
{
	MathLibrary::Sign sign;
	MathLibrary::NaturalNumber absoluteValue;
	if(this->getAbsoluteValue() > operand.getAbsoluteValue())sign = this->getSign();
	else if(this->getAbsoluteValue() < operand.getAbsoluteValue())sign = !operand.getSign();
	else if(this->getSign() == operand.getSign())sign = MathLibrary::plus;
	else sign = this->getSign();
	if(this->getSign() != operand.getSign())absoluteValue = this->getAbsoluteValue() + operand.getAbsoluteValue();
	else if(this->getAbsoluteValue() > operand.getAbsoluteValue())absoluteValue = this->getAbsoluteValue() - operand.getAbsoluteValue();
	else absoluteValue = operand.getAbsoluteValue() - this->getAbsoluteValue();
	return MathLibrary::Integer(sign, absoluteValue);
}

MathLibrary::Integer MathLibrary::Integer::operator-(MathLibrary::NaturalNumber operand)const
{
	if(this->getSign())
		if(this->getAbsoluteValue() >= operand)return MathLibrary::Integer(MathLibrary::plus, this->getAbsoluteValue() - operand);
		else return MathLibrary::Integer(MathLibrary::minus, operand - this->getAbsoluteValue());
	else return MathLibrary::Integer(MathLibrary::minus, this->getAbsoluteValue() + operand);
}

MathLibrary::Fraction MathLibrary::Integer::operator-(MathLibrary::Fraction operand)const
{
	return (MathLibrary::Fraction)*this - operand;
}

MathLibrary::ComplexNumber MathLibrary::Integer::operator-(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this - operand;
}

MathLibrary::Integer MathLibrary::Integer::operator*(MathLibrary::Integer operand)const
{
	MathLibrary::Integer result = MathLibrary::Integer(this->getSign() == operand.getSign() ? MathLibrary::plus : MathLibrary::minus, this->getAbsoluteValue() * operand.getAbsoluteValue());
	MathLibrary::NaturalNumber zero;
	zero = "0";
	if(result.getAbsoluteValue() == zero)result.setSign(MathLibrary::plus);
	return result;
}

MathLibrary::Integer MathLibrary::Integer::operator*(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::Integer result = MathLibrary::Integer(this->getSign(), this->getAbsoluteValue() * operand);
	MathLibrary::NaturalNumber zero;
	zero = "0";
	if(result.getAbsoluteValue() == zero)result.setSign(MathLibrary::plus);
	return result;
}

MathLibrary::Fraction MathLibrary::Integer::operator*(MathLibrary::Fraction operand)const
{
	return operand * *this;
}

MathLibrary::ComplexNumber MathLibrary::Integer::operator*(MathLibrary::ComplexNumber operand)const
{
	return operand * *this;
}

MathLibrary::Integer MathLibrary::Integer::operator/(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::Integer(this->getSign() == operand.getSign() ? MathLibrary::plus : MathLibrary::minus, this->getSign() == MathLibrary::plus ? this->getAbsoluteValue() / operand.getAbsoluteValue() : this->getAbsoluteValue() / operand.getAbsoluteValue() + one);
}

MathLibrary::Integer MathLibrary::Integer::operator/(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::Integer result = MathLibrary::Integer(this->getSign(), this->getAbsoluteValue() / operand);
	MathLibrary::NaturalNumber zero;
	zero = "0";
	if(result.getAbsoluteValue() == zero)result.setSign(MathLibrary::plus);
	return result;
}

MathLibrary::Fraction MathLibrary::Integer::operator/(MathLibrary::Fraction operand)const
{
	return (MathLibrary::Fraction)*this / operand;
}

MathLibrary::ComplexNumber MathLibrary::Integer::operator/(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this / operand;
}

MathLibrary::Integer MathLibrary::Integer::operator%(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::Integer(MathLibrary::plus, this->getSign() == MathLibrary::plus ? this->getAbsoluteValue() % operand.getAbsoluteValue() : this->getAbsoluteValue() % operand.getAbsoluteValue() + one);
}

MathLibrary::Integer MathLibrary::Integer::operator%(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::Integer(MathLibrary::plus, this->getSign() == MathLibrary::plus ? this->getAbsoluteValue() % operand : this->getAbsoluteValue() % operand + one);
	return *this - *this / operand * operand;
}

MathLibrary::Integer MathLibrary::Integer::operator+=(MathLibrary::Integer operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator+=(MathLibrary::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator+=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::Fraction)*this + operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator+=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::ComplexNumber)*this + operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator-=(MathLibrary::Integer operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator-=(MathLibrary::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator-=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::Fraction)*this - operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator-=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::ComplexNumber)*this - operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator*=(MathLibrary::Integer operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator*=(MathLibrary::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator*=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::Fraction)*this * operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator*=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::ComplexNumber)*this * operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator/=(MathLibrary::Integer operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator/=(MathLibrary::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator/=(MathLibrary::Fraction operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::Fraction)*this / operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator/=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::Integer)((MathLibrary::ComplexNumber)*this / operand);
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator%=(MathLibrary::Integer operand)
{
	*this = *this % operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator%=(MathLibrary::NaturalNumber operand)
{
	*this = *this % operand;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator++(void)
{
	MathLibrary::Integer one;
	one = "1";
	*this += one;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator++(int)
{
	MathLibrary::Integer result = *this;
	MathLibrary::Integer one;
	one = "1";
	*this += one;
	return result;
}

MathLibrary::Integer MathLibrary::Integer::operator--(void)
{
	MathLibrary::Integer one;
	one = "1";
	*this -= one;
	return *this;
}

MathLibrary::Integer MathLibrary::Integer::operator--(int)
{
	MathLibrary::Integer result = *this;
	MathLibrary::Integer one;
	one = "1";
	*this -= one;
	return result;
}

bool MathLibrary::Integer::operator==(MathLibrary::Integer operand)const
{
	return this->getSign() == operand.getSign() && this->getAbsoluteValue() == operand.getAbsoluteValue();
}

bool MathLibrary::Integer::operator==(MathLibrary::NaturalNumber operand)const
{
	return this->getSign() == MathLibrary::plus && this->getAbsoluteValue() == operand;
}

bool MathLibrary::Integer::operator==(MathLibrary::Fraction operand)const
{
	return operand == *this;
}

bool MathLibrary::Integer::operator==(MathLibrary::ComplexNumber operand)const
{
	return operand == *this;
}

bool MathLibrary::Integer::operator!=(MathLibrary::Integer operand)const
{
	return this->getSign() != operand.getSign() || this->getAbsoluteValue() != operand.getAbsoluteValue();
}

bool MathLibrary::Integer::operator!=(MathLibrary::NaturalNumber operand)const
{
	return this->getSign() == MathLibrary::minus || this->getAbsoluteValue() != operand;
}

bool MathLibrary::Integer::operator!=(MathLibrary::Fraction operand)const
{
	return operand != *this;
}

bool MathLibrary::Integer::operator!=(MathLibrary::ComplexNumber operand)const
{
	return operand != *this;
}

bool MathLibrary::Integer::operator>(MathLibrary::Integer operand)const
{
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::plus)return this->getAbsoluteValue() > operand.getAbsoluteValue();
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::minus)return true;
	if(this->getSign() == MathLibrary::minus && operand.getSign() == MathLibrary::plus)return false;
	else return this->getAbsoluteValue() < operand.getAbsoluteValue();
}

bool MathLibrary::Integer::operator>(MathLibrary::NaturalNumber operand)const
{
	if(this->getSign() == MathLibrary::plus)return this->getAbsoluteValue() > operand;
	else return false;
}

bool MathLibrary::Integer::operator>(MathLibrary::Fraction operand)const
{
	return operand < *this;
}

bool MathLibrary::Integer::operator<(MathLibrary::Integer operand)const
{
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::plus)return this->getAbsoluteValue() < operand.getAbsoluteValue();
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::minus)return false;
	if(this->getSign() == MathLibrary::minus && operand.getSign() == MathLibrary::plus)return true;
	else return this->getAbsoluteValue() > operand.getAbsoluteValue();
}

bool MathLibrary::Integer::operator<(MathLibrary::NaturalNumber operand)const
{
	if(this->getSign() == MathLibrary::plus)return this->getAbsoluteValue() < operand;
	else return true;
}

bool MathLibrary::Integer::operator<(MathLibrary::Fraction operand)const
{
	return operand > *this;
}

bool MathLibrary::Integer::operator>=(MathLibrary::Integer operand)const
{
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::plus)return this->getAbsoluteValue() >= operand.getAbsoluteValue();
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::minus)return true;
	if(this->getSign() == MathLibrary::minus && operand.getSign() == MathLibrary::plus)return false;
	else return this->getAbsoluteValue() <= operand.getAbsoluteValue();
}

bool MathLibrary::Integer::operator>=(MathLibrary::NaturalNumber operand)const
{
	if(this->getSign() == MathLibrary::plus)return this->getAbsoluteValue() >= operand;
	else return false;
}

bool MathLibrary::Integer::operator>=(MathLibrary::Fraction operand)const
{
	return operand <= *this;
}

bool MathLibrary::Integer::operator<=(MathLibrary::Integer operand)const
{
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::plus)return this->getAbsoluteValue() <= operand.getAbsoluteValue();
	if(this->getSign() == MathLibrary::plus && operand.getSign() == MathLibrary::minus)return false;
	if(this->getSign() == MathLibrary::minus && operand.getSign() == MathLibrary::plus)return true;
	else return this->getAbsoluteValue() >= operand.getAbsoluteValue();
}

bool MathLibrary::Integer::operator<=(MathLibrary::NaturalNumber operand)const
{
	//return *this < operand || *this == operand;
	if(this->getSign() == MathLibrary::plus)return this->getAbsoluteValue() <= operand;
	else return true;
}

bool MathLibrary::Integer::operator<=(MathLibrary::Fraction operand)const
{
	return operand >= *this;
}

bool MathLibrary::Integer::operator!(void)const
{
	MathLibrary::Integer zero;
	zero = "0";
	return *this == zero;
}

MathLibrary::Integer::operator MathLibrary::NaturalNumber(void)const
{
	MathLibrary::Integer integerZero;
	MathLibrary::NaturalNumber naturalNumberZero;
	integerZero = "0";
	naturalNumberZero = "0";
	if(*this < integerZero)
	{
		std::cerr << "*this < zero @ MathLibrary::Integer::operator MathLibrary::NaturalNumber(void)const" << std::endl;
		return naturalNumberZero;
	}
	return this->getAbsoluteValue();
}

MathLibrary::Integer::operator MathLibrary::Fraction(void)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::Fraction(this->getSign(), this->getAbsoluteValue(), one);
}

MathLibrary::Integer::operator MathLibrary::ComplexNumber(void)const
{
	MathLibrary::NaturalNumber one;
	MathLibrary::Fraction zero;
	one = "1";
	zero = "0/1";
	return MathLibrary::ComplexNumber(MathLibrary::Fraction(this->getSign(), this->getAbsoluteValue(), one), zero);
}

MathLibrary::Integer::operator std::string(void)const
{
	std::string result = "";
	if(!this->getSign())result = "-";
	result = result + (std::string)this->getAbsoluteValue();
	return result;
}

std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::Integer &integer)
{
	std::string str;
	is >> str;
	if(str.c_str()[0] != '-' && (str.c_str()[0] < '0' || '9' < str.c_str()[0]))
	{
		std::cerr << "Input data is not an integer. @ std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::Integer &integer)" << std::endl;
		integer = "0";
		return is;
	}
	for(std::string::size_type i = 1; i < str.size(); i++)if(str.c_str()[i] < '0' || '9' < str.c_str()[i])
	{
		std::cerr << "Input data is not an integer. @ std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::Integer &integer)" << std::endl;
		integer = "0";
		return is;
	}
	integer = str;
	return is;
}

std::ostream &MathLibrary::operator<<(std::ostream &os, const MathLibrary::Integer &integer)
{
	if(integer.getSign() == MathLibrary::minus)os << "-";
	os << integer.getAbsoluteValue();
	return os;
}

MathLibrary::Sign MathLibrary::Fraction::getSign(void)const
{
	return this->sign;
}

MathLibrary::NaturalNumber MathLibrary::Fraction::getNumerator(void)const
{
	return this->numerator;
}

MathLibrary::NaturalNumber MathLibrary::Fraction::getDenominator(void)const
{
	return this->denominator;
}

void MathLibrary::Fraction::setSign(MathLibrary::Sign newSign)
{
	this->sign = newSign;
	return;
}

void MathLibrary::Fraction::setNumerator(MathLibrary::NaturalNumber newNumerator)
{
	this->numerator = newNumerator;
	return;
}

void MathLibrary::Fraction::setDenominator(MathLibrary::NaturalNumber newDenominator)
{
	MathLibrary::NaturalNumber zero;
	zero = "0";
	if(newDenominator == zero)
	{
		std::cerr << "newDenominator == zero @ void MathLibrary::Fraction::setDenominator(MathLibrary::NaturalNumber newDenominator)" << std::endl;
		return;
	}
	this->denominator = newDenominator;
	return;
}

void MathLibrary::Fraction::reduce(void)
{
	MathLibrary::NaturalNumber numerator = this->numerator;
	MathLibrary::NaturalNumber denominator = this->denominator;
	MathLibrary::NaturalNumber zero;
	MathLibrary::NaturalNumber one;
	zero = "0";
	one = "1";
	if(numerator == zero)
	{
		this->setSign(MathLibrary::plus);
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

MathLibrary::Fraction::Fraction(void)
{
	MathLibrary::NaturalNumber zero;
	MathLibrary::NaturalNumber one;
	zero = "0";
	one = "1";
	this->setSign(MathLibrary::plus);
	this->setNumerator(zero);
	this->setDenominator(one);
}

MathLibrary::Fraction::Fraction(MathLibrary::Sign sign, MathLibrary::NaturalNumber numerator, MathLibrary::NaturalNumber denominator)
{
	MathLibrary::NaturalNumber zero;
	zero = "0";
	if(denominator == zero)
	{
		std::cerr << "denominator == zero @ MathLibrary::Fraction::Fraction(MathLibrary::Sign sign, MathLibrary::NaturalNumber numerator, MathLibrary::NaturalNumber denominator)" << std::endl;
		denominator = "1";
	}
	if(!sign && numerator == zero)
	{
		std::cerr << "!sign && numerator == zero @ MathLibrary::Fraction::Fraction(MathLibrary::Sign sign, MathLibrary::NaturalNumber numerator, MathLibrary::NaturalNumber denominator)" << std::endl;
		sign = MathLibrary::plus;
	}
	this->setSign(sign);
	this->setNumerator(numerator);
	this->setDenominator(denominator);
	this->reduce();
}

MathLibrary::Fraction::Fraction(const MathLibrary::Fraction &object)
{
	this->setSign(object.getSign());
	this->setNumerator(object.getNumerator());
	this->setDenominator(object.getDenominator());
}

MathLibrary::Fraction MathLibrary::Fraction::operator=(MathLibrary::Fraction operand)
{
	this->setSign(operand.getSign());
	this->setNumerator(operand.getNumerator());
	this->setDenominator(operand.getDenominator());
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator=(MathLibrary::NaturalNumber operand)
{
	MathLibrary::NaturalNumber denominator;
	denominator = "1";
	this->setSign(MathLibrary::plus);
	this->setNumerator(operand);
	this->setDenominator(denominator);
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator=(MathLibrary::Integer operand)
{
	MathLibrary::NaturalNumber numerator, denominator;
	MathLibrary::Integer zero;
	denominator = "1";
	zero = "0";
	this->setSign(operand >= zero ? MathLibrary::plus : MathLibrary::minus);
	this->setNumerator((MathLibrary::NaturalNumber)operand);
	this->setDenominator(denominator);
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator=(MathLibrary::ComplexNumber operand)
{
	*this = (MathLibrary::Fraction)operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator=(std::string operand)
{
	std::string::size_type cursor = 0;
	std::string::size_type readSlash = 0;
	MathLibrary::NaturalNumber numerator;
	MathLibrary::NaturalNumber denominator;
	while(cursor < operand.size())if((cursor == 0 && operand[cursor] != '-'  && (operand[cursor] < '0' || operand[cursor] > '9')) || (cursor != 0 && !readSlash && operand[cursor] != '/' && (operand[cursor] < '0' || operand[cursor] > '9')) || (readSlash && (operand[cursor] < '0' || operand[cursor] > '9')))
	{
		std::cerr << "Input is wrong @ MathLibrary::Fraction MathLibrary::Fraction::operator=(std::string operand)" << std::endl;
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
		std::cerr << "Input is wrong @ std::istream &MathLibrary::operator=(std::istream &is, MathLibrary::Fraction &fraction)" << std::endl;
		return *this;
	}
	if(operand.substr(0, 1) == "-")
	{
		this->setSign(MathLibrary::minus);
		operand = operand.substr(1, operand.size() - 1);
		readSlash--;
	}
	else this->setSign(MathLibrary::plus);
	numerator = operand.substr(0, readSlash);
	denominator = operand.substr(readSlash + 1, operand.size() - readSlash - 1);
	this->setNumerator(numerator);
	this->setDenominator(denominator);
	this->reduce();
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator+(MathLibrary::Fraction operand)const
{
	MathLibrary::Fraction result;
	MathLibrary::Fraction copyThis;
	MathLibrary::Fraction copyOperand;
	MathLibrary::Integer resultNumerator;
	MathLibrary::Integer thisNumerator;
	MathLibrary::Integer operandNumerator;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	copyThis = *this;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	copyThis.setNumerator(copyThis.getNumerator() * copyOperand.getDenominator());
	copyThis.setDenominator(copyThis.getDenominator() * copyOperand.getDenominator());
	copyOperand.setNumerator(copyOperand.getNumerator() * this->getDenominator());
	copyOperand.setDenominator(copyThis.getDenominator());
	thisNumerator = MathLibrary::Integer(copyThis.getSign(), copyThis.getNumerator());
	operandNumerator = MathLibrary::Integer(copyOperand.getSign(), copyOperand.getNumerator());
	resultNumerator = thisNumerator + operandNumerator;
	result = MathLibrary::Fraction(resultNumerator >= zero ? MathLibrary::plus : MathLibrary::minus, (MathLibrary::NaturalNumber)(resultNumerator >= zero ? resultNumerator : minusOne * resultNumerator), copyThis.getDenominator());
	result.reduce();
	return result;
}

MathLibrary::Fraction MathLibrary::Fraction::operator+(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this + MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

MathLibrary::Fraction MathLibrary::Fraction::operator+(MathLibrary::Integer operand)const
{
	MathLibrary::Fraction copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= minusOne;
	}
	return *this + MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, one);
}

MathLibrary::ComplexNumber MathLibrary::Fraction::operator+(MathLibrary::ComplexNumber operand)const
{
	return operand + *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator-(MathLibrary::Fraction operand)const
{
	MathLibrary::Fraction result;
	MathLibrary::Fraction copyThis;
	MathLibrary::Fraction copyOperand;
	MathLibrary::Integer resultNumerator;
	MathLibrary::Integer thisNumerator;
	MathLibrary::Integer operandNumerator;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	copyThis = *this;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	copyThis.setNumerator(copyThis.getNumerator() * copyOperand.getDenominator());
	copyThis.setDenominator(copyThis.getDenominator() * copyOperand.getDenominator());
	copyOperand.setNumerator(copyOperand.getNumerator() * this->getDenominator());
	copyOperand.setDenominator(copyThis.getDenominator());
	thisNumerator = MathLibrary::Integer(copyThis.getSign(), copyThis.getNumerator());
	operandNumerator = MathLibrary::Integer(copyOperand.getSign(), copyOperand.getNumerator());
	resultNumerator = thisNumerator - operandNumerator;
	result = MathLibrary::Fraction(resultNumerator >= zero ? MathLibrary::plus : MathLibrary::minus, (MathLibrary::NaturalNumber)(resultNumerator >= zero ? resultNumerator : minusOne * resultNumerator), copyThis.getDenominator());
	result.reduce();
	return result;
}


MathLibrary::Fraction MathLibrary::Fraction::operator-(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this - MathLibrary::Fraction(MathLibrary::plus, operand, one);
}


MathLibrary::Fraction MathLibrary::Fraction::operator-(MathLibrary::Integer operand)const
{
	MathLibrary::Fraction copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= minusOne;
	}
	return *this - MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, one);
}

MathLibrary::ComplexNumber MathLibrary::Fraction::operator-(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this - operand;
}

MathLibrary::Fraction MathLibrary::Fraction::operator*(MathLibrary::Fraction operand)const
{
	MathLibrary::Fraction result = MathLibrary::Fraction(MathLibrary::plus, this->getNumerator() * operand.getNumerator(), this->getDenominator() * operand.getDenominator());
	MathLibrary::NaturalNumber zero;
	zero = "0";
	if(result.getNumerator() != zero && this->getSign() != operand.getSign())result.setSign(MathLibrary::minus);
	result.reduce();
	return result;
}

MathLibrary::Fraction MathLibrary::Fraction::operator*(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this * MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

MathLibrary::Fraction MathLibrary::Fraction::operator*(MathLibrary::Integer operand)const
{
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= minusOne;
	}
	return *this * MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, one);
}

MathLibrary::ComplexNumber MathLibrary::Fraction::operator*(MathLibrary::ComplexNumber operand)const
{
	return operand * *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator/(MathLibrary::Fraction operand)const
{
	MathLibrary::NaturalNumber zero;
	MathLibrary::NaturalNumber one;
	zero = "0";
	one = "1";
	if(operand.getNumerator() == zero)
	{
		std::cerr << "operand == zero @ MathLibrary::Fraction MathLibrary::Fraction::operator/(const MathLibrary::Fraction operand)const" << std::endl;
		return MathLibrary::Fraction(MathLibrary::plus, zero, one);
	}
	return *this * MathLibrary::Fraction(operand.getSign(), operand.getDenominator(), operand.getNumerator());
}

MathLibrary::Fraction MathLibrary::Fraction::operator/(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber zero;
	MathLibrary::NaturalNumber one;
	zero = "0";
	one = "1";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MathLibrary::Fraction MathLibrary::Fraction::operator/(MathLibrary::NaturalNumber operand)const" << std::endl;
		return MathLibrary::Fraction(MathLibrary::plus, zero, one);
	}
	return *this / MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

MathLibrary::Fraction MathLibrary::Fraction::operator/(MathLibrary::Integer operand)const
{
	MathLibrary::Fraction copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MathLibrary::Fraction MathLibrary::Fraction::operator/(MathLibrary::Integer operand)const" << std::endl;
		return MathLibrary::Fraction(MathLibrary::plus, (MathLibrary::NaturalNumber)zero, one);
	}
	if(operand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= minusOne;
	}
	return *this / MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, one);
}

MathLibrary::ComplexNumber MathLibrary::Fraction::operator/(MathLibrary::ComplexNumber operand)const
{
	return (MathLibrary::ComplexNumber)*this / operand;
}

MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::Fraction operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::Integer operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::ComplexNumber operand)" << std::endl;
	*this = *this + (MathLibrary::Fraction)operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator-=(MathLibrary::Fraction operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator-=(MathLibrary::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator-=(MathLibrary::Integer operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator-=(MathLibrary::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::ComplexNumber operand)" << std::endl;
	*this = *this - (MathLibrary::Fraction)operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator*=(MathLibrary::Fraction operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator*=(MathLibrary::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator*=(MathLibrary::Integer operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator*=(MathLibrary::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::ComplexNumber operand)" << std::endl;
	*this = *this * (MathLibrary::Fraction)operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator/=(MathLibrary::Fraction operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator/=(MathLibrary::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator/=(MathLibrary::Integer operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator/=(MathLibrary::ComplexNumber operand)
{
	if(operand != operand.conjugate())std::cerr << "operand != operand.conjugate() @ MathLibrary::Fraction MathLibrary::Fraction::operator+=(MathLibrary::ComplexNumber operand)" << std::endl;
	*this = *this / (MathLibrary::Fraction)operand;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator++(void)
{
	MathLibrary::Fraction one;
	one = "1/1";
	*this += one;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator++(int)
{
	MathLibrary::Fraction result = *this;
	MathLibrary::Fraction one;
	one = "1/1";
	*this += one;
	return result;
}

MathLibrary::Fraction MathLibrary::Fraction::operator--(void)
{
	MathLibrary::Fraction one;
	one = "1/1";
	*this -= one;
	return *this;
}

MathLibrary::Fraction MathLibrary::Fraction::operator--(int)
{
	MathLibrary::Fraction result = *this;
	MathLibrary::Fraction one;
	one = "1/1";
	*this += one;
	return result;
}

bool MathLibrary::Fraction::operator==(MathLibrary::Fraction operand)const
{
	return this->getSign() == operand.getSign() && this->getNumerator() == operand.getNumerator() && this->getDenominator() == operand.getDenominator();
}

bool MathLibrary::Fraction::operator==(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this == MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

bool MathLibrary::Fraction::operator==(MathLibrary::Integer operand)const
{
	MathLibrary::Integer copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		copyOperand *= minusOne;
	}
	return *this == MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)copyOperand, one);
}

bool MathLibrary::Fraction::operator==(MathLibrary::ComplexNumber operand)const
{
	return operand == *this;
}

bool MathLibrary::Fraction::operator!=(MathLibrary::Fraction operand)const
{
	return this->getSign() != operand.getSign() || this->getNumerator() != operand.getNumerator() || this->getDenominator() != operand.getDenominator();
}

bool MathLibrary::Fraction::operator!=(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this != MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

bool MathLibrary::Fraction::operator!=(MathLibrary::Integer operand)const
{
	MathLibrary::Integer copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		copyOperand *= minusOne;
	}
	return *this != MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)copyOperand, one);
}

bool MathLibrary::Fraction::operator!=(MathLibrary::ComplexNumber operand)const
{
	return operand != *this;
}

bool MathLibrary::Fraction::operator>(MathLibrary::Fraction operand)const
{
	if(this->getSign() == MathLibrary::plus)
		if(operand.getSign() == MathLibrary::plus)return this->getNumerator() * operand.getDenominator() > operand.getNumerator() * this->getDenominator();
		else return true;
	else
		if(operand.getSign() == MathLibrary::plus)return false;
		else return this->getNumerator() * operand.getDenominator() < operand.getNumerator() * this->getDenominator();
}

bool MathLibrary::Fraction::operator>(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this > MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

bool MathLibrary::Fraction::operator>(MathLibrary::Integer operand)const
{
	MathLibrary::Integer copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		copyOperand *= minusOne;
	}
	return *this > MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)copyOperand, one);
}

bool MathLibrary::Fraction::operator<(MathLibrary::Fraction operand)const
{
	if(this->getSign() == MathLibrary::plus)
		if(operand.getSign() == MathLibrary::plus)return this->getNumerator() * operand.getDenominator() < operand.getNumerator() * this->getDenominator();
		else return false;
	else
		if(operand.getSign() == MathLibrary::plus)return true;
		else return this->getNumerator() * operand.getDenominator() > operand.getNumerator() * this->getDenominator();
}

bool MathLibrary::Fraction::operator<(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this < MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

bool MathLibrary::Fraction::operator<(MathLibrary::Integer operand)const
{
	MathLibrary::Integer copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		copyOperand *= minusOne;
	}
	return *this < MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)copyOperand, one);
}

bool MathLibrary::Fraction::operator>=(MathLibrary::Fraction operand)const
{
	if(this->getSign() == MathLibrary::plus)
		if(operand.getSign() == MathLibrary::plus)return this->getNumerator() * operand.getDenominator() >= operand.getNumerator() * this->getDenominator();
		else return true;
	else
		if(operand.getSign() == MathLibrary::plus)return false;
		else return this->getNumerator() * operand.getDenominator() <= operand.getNumerator() * this->getDenominator();
}

bool MathLibrary::Fraction::operator>=(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this >= MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

bool MathLibrary::Fraction::operator>=(MathLibrary::Integer operand)const
{
	MathLibrary::Integer copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		copyOperand *= minusOne;
	}
	return *this >= MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)copyOperand, one);
}

bool MathLibrary::Fraction::operator<=(MathLibrary::Fraction operand)const
{
	if(this->getSign() == MathLibrary::plus)
		if(operand.getSign() == MathLibrary::plus)return this->getNumerator() * operand.getDenominator() <= operand.getNumerator() * this->getDenominator();
		else return false;
	else
		if(operand.getSign() == MathLibrary::plus)return true;
		else return this->getNumerator() * operand.getDenominator() >= operand.getNumerator() * this->getDenominator();
}

bool MathLibrary::Fraction::operator<=(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return *this <= MathLibrary::Fraction(MathLibrary::plus, operand, one);
}

bool MathLibrary::Fraction::operator<=(MathLibrary::Integer operand)const
{
	MathLibrary::Integer copyOperand;
	MathLibrary::Integer zero;
	MathLibrary::Integer minusOne;
	MathLibrary::NaturalNumber one;
	MathLibrary::Sign operandSign;
	copyOperand = operand;
	zero = "0";
	minusOne = "-1";
	one = "1";
	if(copyOperand >= zero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		copyOperand *= minusOne;
	}
	return *this <= MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)copyOperand, one);
}

bool MathLibrary::Fraction::operator!(void)const
{
	MathLibrary::Fraction zero;
	zero = "0/1";
	return *this == zero;
}

MathLibrary::Fraction::operator MathLibrary::NaturalNumber(void)const
{
	MathLibrary::NaturalNumber result = this->getNumerator() / this->getDenominator();
	MathLibrary::NaturalNumber one;
	one = "1";
	if(*this != MathLibrary::Fraction(MathLibrary::plus, result, one))std::cerr << "A value has been changed. @ MathLibrary::Fraction::operator MathLibrary::NaturalNumber(void)const" << std::endl;
	return result;
}

MathLibrary::Fraction::operator MathLibrary::Integer(void)const
{
	MathLibrary::NaturalNumber one;
	MathLibrary::NaturalNumber zero;
	one = "1";
	zero = "0";
	if(*this != MathLibrary::Fraction(this->getSign(), this->getNumerator() / this->getDenominator(), one))std::cerr << "A value has been changed. @ MathLibrary::Fraction::operator MathLibrary::Integer(void)const" << std::endl;
	return MathLibrary::Integer(this->getNumerator() / this->getDenominator() ==zero ? MathLibrary::plus : this->getSign(), this->getNumerator() / this->getDenominator());
}

MathLibrary::Fraction::operator MathLibrary::ComplexNumber(void)const
{
	MathLibrary::Fraction zero;
	zero = "0/1";
	return MathLibrary::ComplexNumber(*this, zero);
}

MathLibrary::Fraction::operator std::string(void)const
{
	std::string result = "";
	if(this->getSign() == MathLibrary::minus)result = "-";
	result = result + (std::string)this->getNumerator() + "/" + (std::string)this->getDenominator();
	return result;
}

std::string MathLibrary::Fraction::toDecimal(unsigned int digit)const
{
	std::string result = "";
	MathLibrary::NaturalNumber numerator = this->getNumerator();
	MathLibrary::NaturalNumber ten;
	ten = "10";
	if(this->getSign() == MathLibrary::minus)result = "-";
	result = result + (std::string)(this->getNumerator() / this->getDenominator()) + ".";
	for(unsigned int i = 0; i < digit; i++)
	{
		numerator = ten * (numerator % this->getDenominator());
		result = result + (std::string)(numerator / this->getDenominator());
	}
	return result;
}

std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::Fraction &fraction)
{
	std::string str;
	std::string::size_type cursor = 0;
	std::string::size_type readSlash = 0;
	MathLibrary::NaturalNumber numerator;
	MathLibrary::NaturalNumber denominator;
	is >> str;
	while(cursor < str.size())if((cursor == 0 && str[cursor] != '-'  && (str[cursor] < '0' || str[cursor] > '9')) || (cursor != 0 && !readSlash && str[cursor] != '/' && (str[cursor] < '0' || str[cursor] > '9')) || (readSlash && (str[cursor] < '0' || str[cursor] > '9')))
	{
		std::cerr << "Input is wrong @ std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::Fraction &fraction)" << std::endl;
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
		std::cerr << "Input is wrong @ std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::Fraction &fraction)" << std::endl;
		return is;
	}
	if(str.substr(0, 1) == "-")
	{
		fraction.setSign(MathLibrary::minus);
		str = str.substr(1, str.size() - 1);
		readSlash--;
	}
	else fraction.setSign(MathLibrary::plus);
	numerator = str.substr(0, readSlash);
	denominator = str.substr(readSlash + 1, str.size() - readSlash - 1);
	fraction.setNumerator(numerator);
	fraction.setDenominator(denominator);
	fraction.reduce();
	return is;
}

std::ostream &MathLibrary::operator<<(std::ostream &os, const MathLibrary::Fraction &fraction)
{
	if(fraction.getSign() == MathLibrary::minus)os << "-";
	os << fraction.getNumerator() << "/" << fraction.getDenominator();
	return os;
}

MathLibrary::Fraction MathLibrary::ComplexNumber::getRealPart(void)const
{
	return this->realPart;
}

MathLibrary::Fraction MathLibrary::ComplexNumber::getImaginaryPart(void)const
{
	return this->imaginaryPart;
}

void MathLibrary::ComplexNumber::setRealPart(const MathLibrary::Fraction &realPart)
{
	this->realPart = realPart;
	return;
}

void MathLibrary::ComplexNumber::setImaginaryPart(const MathLibrary::Fraction &imaginaryPart)
{
	this->imaginaryPart = imaginaryPart;
	return;
}

MathLibrary::ComplexNumber::ComplexNumber(void)
{
	MathLibrary::Fraction zero;
	zero = "0/1";
	this->setRealPart(zero);
	this->setImaginaryPart(zero);
	return;
}

MathLibrary::ComplexNumber::ComplexNumber(MathLibrary::Fraction realPart, MathLibrary::Fraction imaginaryPart)
{
	this->setRealPart(realPart);
	this->setImaginaryPart(imaginaryPart);
	return;
}

MathLibrary::ComplexNumber::ComplexNumber(const MathLibrary::ComplexNumber &object)
{
	this->setRealPart(object.getRealPart());
	this->setImaginaryPart(object.getImaginaryPart());
	return;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator=(MathLibrary::ComplexNumber operand)
{
	this->setRealPart(operand.getRealPart());
	this->setImaginaryPart(operand.getImaginaryPart());
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator=(MathLibrary::NaturalNumber operand)
{
	MathLibrary::NaturalNumber zero;
	MathLibrary::NaturalNumber one;
	zero = "0";
	one = "1";
	this->setRealPart(MathLibrary::Fraction(MathLibrary::plus, operand, one));
	this->setImaginaryPart(MathLibrary::Fraction(MathLibrary::plus, zero, one));
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator=(MathLibrary::Integer operand)
{
	MathLibrary::Integer integerZero;
	MathLibrary::Integer integerMinusOne;
	MathLibrary::NaturalNumber naturalNumberZero;
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Sign realPartSign;
	integerZero = "0";
	integerMinusOne = "-1";
	naturalNumberZero = "0";
	naturalNumberOne = "1";
	if(operand >= integerZero)realPartSign = MathLibrary::plus;
	else
	{
		operand *= integerMinusOne;
		realPartSign = MathLibrary::minus;
	}
	this->setRealPart(MathLibrary::Fraction(realPartSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne));
	this->setImaginaryPart(MathLibrary::Fraction(MathLibrary::plus, naturalNumberZero, naturalNumberOne));
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator=(MathLibrary::Fraction operand)
{
	MathLibrary::Fraction zero;
	zero = "0/1";
	this->setRealPart(operand);
	this->setImaginaryPart(zero);
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator=(std::string operand)
{
	std::string::size_type cursor = 0;
	std::string::size_type readSign = 0;
	MathLibrary::Fraction realPart;
	MathLibrary::Fraction imaginaryPart;
	while(cursor < operand.size())
		if(operand[cursor] == '+' || operand[cursor] == '-')readSign = cursor++;
		else cursor++;
	if(!readSign || operand[operand.size() - 1] != 'i')
	{
		std::cerr << "Input is wrong @ MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator=(std::string operand)" << std::endl;
		return *this;
	}
	realPart = operand.substr(0, readSign);
	if(operand[readSign] == '+')imaginaryPart = operand.substr(readSign + 1, operand.size() - readSign - 2);
	if(operand[readSign] == '-')imaginaryPart = operand.substr(readSign, operand.size() - readSign - 1);
	this->setRealPart(realPart);
	this->setImaginaryPart(imaginaryPart);
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+(MathLibrary::ComplexNumber operand)const
{
	return MathLibrary::ComplexNumber(this->getRealPart() + operand.getRealPart(), this->getImaginaryPart() + operand.getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::ComplexNumber(this->getRealPart() + MathLibrary::Fraction(MathLibrary::plus, operand, one), this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Integer integerZero;
	MathLibrary::Integer integerMinusOne;
	MathLibrary::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand >= integerZero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= integerMinusOne;
	}
	return MathLibrary::ComplexNumber(this->getRealPart() + MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne), this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+(MathLibrary::Fraction operand)const
{
	return MathLibrary::ComplexNumber(this->getRealPart() + operand, this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-(MathLibrary::ComplexNumber operand)const
{
	return MathLibrary::ComplexNumber(this->getRealPart() - operand.getRealPart(), this->getImaginaryPart() - operand.getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::ComplexNumber(this->getRealPart() - MathLibrary::Fraction(MathLibrary::plus, operand, one), this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Integer integerZero;
	MathLibrary::Integer integerMinusOne;
	MathLibrary::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand >= integerZero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= integerMinusOne;
	}
	return MathLibrary::ComplexNumber(this->getRealPart() - MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne), this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-(MathLibrary::Fraction operand)const
{
	return MathLibrary::ComplexNumber(this->getRealPart() - operand, this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*(MathLibrary::ComplexNumber operand)const
{
	return MathLibrary::ComplexNumber(this->getRealPart() * operand.getRealPart() - this->getImaginaryPart() * operand.getImaginaryPart(), this->getRealPart() * operand.getImaginaryPart() + operand.getRealPart() * this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	one = "1";
	return MathLibrary::ComplexNumber(MathLibrary::Fraction(MathLibrary::plus, operand, one) * this->getRealPart(), MathLibrary::Fraction(MathLibrary::plus, operand, one) * this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Integer integerZero;
	MathLibrary::Integer integerMinusOne;
	MathLibrary::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand >= integerZero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= integerMinusOne;
	}
	return MathLibrary::ComplexNumber(MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne) * this->getRealPart(), MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne) * this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*(MathLibrary::Fraction operand)const
{
	return MathLibrary::ComplexNumber(operand * this->getRealPart(), operand * this->getImaginaryPart());
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::ComplexNumber operand)const
{
	MathLibrary::Fraction tre = this->getRealPart();
	MathLibrary::Fraction tim = this->getImaginaryPart();
	MathLibrary::Fraction ore = operand.getRealPart();
	MathLibrary::Fraction oim = operand.getImaginaryPart();
	MathLibrary::Fraction zero;
	zero = "0/1";
	if(ore == zero && oim == zero)
	{
		std::cerr << "operand == zero @ MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::ComplexNumber operand)const" << std::endl;
		return MathLibrary::ComplexNumber(zero, zero);
	}
	return MathLibrary::ComplexNumber((tre * ore + tim * oim) / (ore * ore + oim * oim), (tim * ore - tre * oim) / (ore * ore + oim * oim));
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber one;
	MathLibrary::NaturalNumber zero;
	one = "1";
	zero = "0";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::NaturalNumber operand)const" << std::endl;
		return MathLibrary::ComplexNumber(MathLibrary::Fraction(MathLibrary::plus, zero, one), MathLibrary::Fraction(MathLibrary::plus, zero, one));
	}
	return MathLibrary::ComplexNumber(this->getRealPart() / MathLibrary::Fraction(MathLibrary::plus, operand, one), this->getImaginaryPart() / MathLibrary::Fraction(MathLibrary::plus, operand, one));
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::NaturalNumber naturalNumberZero;
	MathLibrary::Integer integerZero;
	MathLibrary::Integer integerMinusOne;
	MathLibrary::Sign operandSign;
	naturalNumberOne = "1";
	naturalNumberZero = "0";
	integerZero = "0";
	integerMinusOne = "-1";
	if(operand == integerZero)
	{
		std::cerr << "operand == zero @ MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::Integer operand)const" << std::endl;
		return MathLibrary::ComplexNumber(MathLibrary::Fraction(MathLibrary::plus, naturalNumberZero, naturalNumberOne), MathLibrary::Fraction(MathLibrary::plus, naturalNumberZero, naturalNumberOne));
	}
	if(operand >= integerZero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= integerMinusOne;
	}
	return MathLibrary::ComplexNumber(this->getRealPart() / MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne), this->getImaginaryPart() / MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand , naturalNumberOne));
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::Fraction operand)const
{
	MathLibrary::Fraction zero;
	zero = "0/1";
	if(operand == zero)
	{
		std::cerr << "operand == zero @ MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/(MathLibrary::Fraction operand)const" << std::endl;
		return MathLibrary::ComplexNumber(zero, zero);
	}
	return MathLibrary::ComplexNumber(this->getRealPart() / operand, this->getImaginaryPart() / operand);
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+=(MathLibrary::ComplexNumber operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+=(MathLibrary::NaturalNumber operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+=(MathLibrary::Integer operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator+=(MathLibrary::Fraction operand)
{
	*this = *this + operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-=(MathLibrary::ComplexNumber operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-=(MathLibrary::NaturalNumber operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-=(MathLibrary::Integer operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator-=(MathLibrary::Fraction operand)
{
	*this = *this - operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*=(MathLibrary::ComplexNumber operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*=(MathLibrary::NaturalNumber operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*=(MathLibrary::Integer operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator*=(MathLibrary::Fraction operand)
{
	*this = *this * operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/=(MathLibrary::ComplexNumber operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/=(MathLibrary::NaturalNumber operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/=(MathLibrary::Integer operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator/=(MathLibrary::Fraction operand)
{
	*this = *this / operand;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator++(void)
{
	MathLibrary::ComplexNumber one;
	one = "1/1+0/1i";
	*this += one;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator++(int)
{
	MathLibrary::ComplexNumber result = *this;
	MathLibrary::ComplexNumber one;
	one = "1/1+0/1i";
	*this += one;
	return result;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator--(void)
{
	MathLibrary::ComplexNumber one;
	one = "1/1+0/1i";
	*this -= one;
	return *this;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::operator--(int)
{
	MathLibrary::ComplexNumber result = *this;
	MathLibrary::ComplexNumber one;
	one = "1/1+0/1i";
	*this -= one;
	return result;
}

bool MathLibrary::ComplexNumber::operator==(MathLibrary::ComplexNumber operand)const
{
	return this->getRealPart() == operand.getRealPart() && this->getImaginaryPart() == operand.getImaginaryPart();
}

bool MathLibrary::ComplexNumber::operator==(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Fraction fractionZero;
	naturalNumberOne = "1";
	fractionZero = "0/1";
	return this->getRealPart() == MathLibrary::Fraction(MathLibrary::plus, operand, naturalNumberOne) && this->getImaginaryPart() == fractionZero;
}

bool MathLibrary::ComplexNumber::operator==(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Integer integerZero;
	MathLibrary::Integer integerMinusOne;
	MathLibrary::Fraction fractionZero;
	MathLibrary::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	fractionZero = "0/1";
	if(operand >= integerZero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= integerMinusOne;
	}
	return this->getRealPart() == MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne) && this->getImaginaryPart() == fractionZero;
}

bool MathLibrary::ComplexNumber::operator==(MathLibrary::Fraction operand)const
{
	MathLibrary::Fraction fractionZero;
	fractionZero = "0/1";
	return this->getRealPart() == operand && this->getImaginaryPart() == fractionZero;
}

bool MathLibrary::ComplexNumber::operator!=(MathLibrary::ComplexNumber operand)const
{
	return this->getRealPart() != operand.getRealPart() || this->getImaginaryPart() != operand.getImaginaryPart();
}

bool MathLibrary::ComplexNumber::operator!=(MathLibrary::NaturalNumber operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Fraction fractionZero;
	naturalNumberOne = "1";
	fractionZero = "0/1";
	return this->getRealPart() != MathLibrary::Fraction(MathLibrary::plus, operand, naturalNumberOne) || this->getImaginaryPart() != fractionZero;
}

bool MathLibrary::ComplexNumber::operator!=(MathLibrary::Integer operand)const
{
	MathLibrary::NaturalNumber naturalNumberOne;
	MathLibrary::Integer integerZero;
	MathLibrary::Integer integerMinusOne;
	MathLibrary::Fraction fractionZero;
	MathLibrary::Sign operandSign;
	naturalNumberOne = "1";
	integerZero = "0";
	integerMinusOne = "-1";
	fractionZero = "0/1";
	if(operand >= integerZero)operandSign = MathLibrary::plus;
	else
	{
		operandSign = MathLibrary::minus;
		operand *= integerMinusOne;
	}
	return this->getRealPart() != MathLibrary::Fraction(operandSign, (MathLibrary::NaturalNumber)operand, naturalNumberOne) || this->getImaginaryPart() != fractionZero;
}

bool MathLibrary::ComplexNumber::operator!=(MathLibrary::Fraction operand)const
{
	MathLibrary::Fraction fractionZero;
	fractionZero = "0/1";
	return this->getRealPart() != operand || this->getImaginaryPart() != fractionZero;
}

MathLibrary::ComplexNumber::operator MathLibrary::NaturalNumber(void)const
{
	MathLibrary::Fraction fractionZero;
	MathLibrary::NaturalNumber naturalNumberZero;
	fractionZero = "0/1";
	naturalNumberZero = "0";
	if(this->getImaginaryPart() != fractionZero)std::cerr << "A value has been changed. @ MathLibrary::ComplexNumber::operator MathLibrary::NaturalNumber(void)const" << std::endl;
	return (MathLibrary::NaturalNumber)this->getRealPart();
}

MathLibrary::ComplexNumber::operator MathLibrary::Integer(void)const
{
	MathLibrary::NaturalNumber naturalNumberZero;
	MathLibrary::Fraction fractionZero;
	naturalNumberZero = "0";
	fractionZero = "0/1";
	if(this->getImaginaryPart() != fractionZero)std::cerr << "A value has been changed. @ MathLibrary::ComplexNumber::operator MathLibrary::Integer(void)const" << std::endl;
	return (MathLibrary::Integer)this->getRealPart();
}

MathLibrary::ComplexNumber::operator MathLibrary::Fraction(void)const
{
	MathLibrary::Fraction zero;
	MathLibrary::Fraction one;
	zero = "0/1";
	one = "1/1";
	if(this->getImaginaryPart() != zero)std::cerr << "A value has been changed. @ MathLibrary::ComplexNumber::operator MathLibrary::Fraction(void)const" << std::endl;
	return this->getRealPart();
}

MathLibrary::ComplexNumber::operator std::string(void)const
{
	std::string result = "";
	MathLibrary::Fraction zero;
	zero = "0/1";
	result = (std::string)this->getRealPart();
	if(this->getImaginaryPart() >= zero)result = result + "+";
	result = result + (std::string)this->getImaginaryPart() + "i";
	return result;
}

MathLibrary::ComplexNumber MathLibrary::ComplexNumber::conjugate(void)const
{
	MathLibrary::ComplexNumber minusOne;
	minusOne = "-1/1+0/1i";
	return MathLibrary::ComplexNumber(this->getRealPart(), minusOne * this->getImaginaryPart());
}

std::string MathLibrary::ComplexNumber::toDecimal(unsigned int digit)const
{
	MathLibrary::Fraction zero;
	zero = "0/1";
	return this->getRealPart().toDecimal(digit) + (this->getImaginaryPart() >= zero ? "+" : "") + this->getImaginaryPart().toDecimal(digit) + "i";
}

std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::ComplexNumber &complexNumber)
{
	std::string str;
	std::string::size_type cursor = 0;
	std::string::size_type readSign = 0;
	MathLibrary::Fraction realPart;
	MathLibrary::Fraction imaginaryPart;
	is >> str;
	while(cursor < str.size())
		if(str[cursor] == '+' || str[cursor] == '-')readSign = cursor++;
		else cursor++;
	if(!readSign || str[str.size() - 1] != 'i')
	{
		std::cerr << "Input is wrong @ std::istream &MathLibrary::operator>>(std::istream &is, MathLibrary::ComplexNumber &complexNumber)" << std::endl;
		return is;
	}
	realPart = str.substr(0, readSign);
	if(str[readSign] == '+')imaginaryPart = str.substr(readSign + 1, str.size() - readSign - 2);
	if(str[readSign] == '-')imaginaryPart = str.substr(readSign, str.size() - readSign - 1);
	complexNumber.setRealPart(realPart);
	complexNumber.setImaginaryPart(imaginaryPart);
	return is;
}

std::ostream &MathLibrary::operator<<(std::ostream &os, const MathLibrary::ComplexNumber &complexNumber)
{
	MathLibrary::Fraction zero;
	zero = "0/1";
	os << complexNumber.getRealPart();
	if(complexNumber.getImaginaryPart() >= zero)os << "+";
	os << complexNumber.getImaginaryPart() << "i";
	return os;
}

