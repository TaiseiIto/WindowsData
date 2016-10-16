#include<cstdlib>
#include<conio.h>
#include<string>
#include<iostream>
#include"FileLibrary.h"
#include"MathLibrary.h"

int main(int argc, char** argv)
{
	FileLibrary::File file;
	MathLibrary::NaturalNumber naturalNumber, zero, two;
	zero = "0";
	two = "2";
	if(argc == 1)
	{
		std::cerr << "File name is not found." << std::endl;
		return EXIT_FAILURE;
	}
	file = FileLibrary::File(argv[1]);
	if(file.getSize() == 0)file.insert("2\n3\n",0);
	naturalNumber = file.getLine(file.getLinage() - 1);
	while(!kbhit())
	{
		bool isPrime = true;
		MathLibrary::NaturalNumber denominator;
		FileLibrary::LineNumber line = 2;
		denominator = file.getLine(line);
		naturalNumber += two;
		while(denominator * denominator <= naturalNumber)
		{
			denominator = file.getLine(line);
			if(naturalNumber % denominator == zero)
			{
				isPrime = false;
				break;
			}
			line++;
		}
		if(isPrime)
		{
			std::string output;
			output = (std::string)naturalNumber;
			std::cout << output << std::endl;
			file.addLine(output, file.getLinage());
		}
	}
	getch();
	file.save();
	return EXIT_SUCCESS;
}

