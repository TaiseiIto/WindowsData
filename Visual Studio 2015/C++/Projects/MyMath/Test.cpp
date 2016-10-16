#include<iostream>
#include<stdlib.h>
#include"MyMath.h"

int main(int argc, char **argv)
{
	MyMath::ComplexNumber complexNumber1, complexNumber2;
	std::cin >> complexNumber1;
	std::cin >> complexNumber2;
	std::cout << (complexNumber1 / complexNumber2) << std::endl;
	return EXIT_SUCCESS;
}

