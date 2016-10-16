#define MYMATH_DEBUG
#include<iostream>
#include<stdlib.h>
#include"MyMath.h"

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));
	MyMath::Bits bits1(rand() % 10);
	MyMath::Bits bits2(rand() % 10);
	for(unsigned int i = 0; i < bits1.getSize(); i++)bits1.setBit(i, rand() % 2);
	for(unsigned int i = 0; i < bits2.getSize(); i++)bits2.setBit(i, rand() % 2);
	MyMath::NaturalNumber naturalNumber1(bits1);
	MyMath::NaturalNumber naturalNumber2(bits2);
	std::cout << naturalNumber1 << std::endl;
	std::cout << naturalNumber2 << std::endl;
	std::cout << (naturalNumber1 % naturalNumber2) << std::endl;
	return EXIT_SUCCESS;
}

