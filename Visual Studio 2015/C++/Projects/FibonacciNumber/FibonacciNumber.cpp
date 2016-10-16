#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<string>
#include<iostream>
#include"FileLibrary.h"
#include"MathLibrary.h"

int main(int argc, char** argv)
{
	MathLibrary::NaturalNumber fibonacci1, fibonacci2, zero;
	FileLibrary::File file;
	fibonacci1 = "1";
	fibonacci2 = "1";
	zero = "0";
	if(argc == 1)
	{
		std::cerr << "File name is not found." << std::endl;
		return EXIT_FAILURE;
	}
	file = FileLibrary::File(argv[1]);
	if(file.getSize() == 0)file.insert("1\n1\n",0);
	fibonacci1 = file.getLine(file.getLinage() - 2);
	fibonacci2 = file.getLine(file.getLinage() - 1);
	while(!_kbhit())
	{
		MathLibrary::NaturalNumber newFibonacci = fibonacci1 + fibonacci2;
		std::string output;
		fibonacci1 = fibonacci2;
		fibonacci2 = newFibonacci;
		output = (std::string)newFibonacci;
		std::cout << output << std::endl;
		file.addLine(output, file.getLinage());
	}
	getch();
	file.save();
	return EXIT_SUCCESS;
}

