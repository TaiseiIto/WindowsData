#include<cstdio>
#include<iostream>
#include<string>
#include<sstream>
#include"FileLibrary.h"

FileLibrary::FileNumber FileLibrary::File::maxid = 0;
const std::string FileLibrary::File::readBinary = "rb";
const std::string FileLibrary::File::writeBinary = "wb";
const std::string FileLibrary::File::editFileExtention = ".edit";
const std::string FileLibrary::File::setSizeFileExtention = ".setSize";
const std::string FileLibrary::File::setCharacterFileExtention = ".setCharacter";
const std::string FileLibrary::File::insertFileExtention = ".insert";
const std::string FileLibrary::File::cutFileExtention = ".cut";

FileLibrary::File::File(void)
{
	this->id = 0;
	this->fileName = "";
}

FileLibrary::File::File(std::string fileName)
{
	FILE *filePointer;
	FILE *editFilePointer;
	std::stringstream editFileName;
	FileLibrary::File::maxid++;
	this->id = FileLibrary::File::maxid;
	this->fileName = fileName;
	filePointer = fopen(fileName.c_str(), FileLibrary::File::readBinary.c_str());
	editFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	if(filePointer == NULL)fclose(editFilePointer);
	else
	{
		int character = fgetc(filePointer);
		while(character != EOF)
		{
			fputc(character, editFilePointer);
			character = fgetc(filePointer);
		}
		fclose(filePointer);
		fclose(editFilePointer);
	}
	return;
}

FileLibrary::File::File(const FileLibrary::File &object)
{
	FILE *filePointer;
	FILE *editFilePointer;
	std::stringstream fileName;
	std::stringstream editFileName;
	FileLibrary::File::maxid++;
	this->id = FileLibrary::File::maxid;
	this->fileName = object.fileName;
	fileName << object.id << FileLibrary::File::editFileExtention;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	filePointer = fopen(fileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	if(filePointer == NULL)fclose(editFilePointer);
	else
	{
		int character = fgetc(filePointer);
		while(character != EOF)
		{
			fputc(character, editFilePointer);
			character = fgetc(filePointer);
		}
		fclose(filePointer);
		fclose(editFilePointer);
	}
	return;
}

FileLibrary::File::~File(void)
{
	std::stringstream editFileName;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	remove(editFileName.str().c_str());
}

FileLibrary::FilePosition FileLibrary::File::getSize(void)const
{
	FileLibrary::FilePosition result;
	FILE *editFilePointer;
	std::stringstream editFileName;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	fseek(editFilePointer, 0, SEEK_END);
	result = (FileLibrary::FilePosition)ftell(editFilePointer);
	fclose(editFilePointer);
	return result;
}

void FileLibrary::File::setSize(FileLibrary::FilePosition newSize)
{
	FILE *editFilePointer;
	FILE *setSizeFilePointer;
	std::stringstream editFileName;
	std::stringstream setSizeFileName;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	setSizeFileName << this->id << FileLibrary::File::setSizeFileExtention;
	if(newSize == this->getSize())return;
	else if(newSize > this->getSize())
	{
		editFilePointer = fopen(editFileName.str().c_str(), "ab");
		for(FileLibrary::FilePosition i = this->getSize(); i < newSize; i++)fputc('\0', editFilePointer);
		fclose(editFilePointer);
	}
	else if(newSize < this->getSize())
	{
		editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
		setSizeFilePointer = fopen(setSizeFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
		for(FileLibrary::FilePosition i = 0; i < newSize; i++)fputc(fgetc(editFilePointer), setSizeFilePointer);
		fclose(editFilePointer);
		fclose(setSizeFilePointer);
		editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
		setSizeFilePointer = fopen(setSizeFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
		for(FileLibrary::FilePosition i = 0; i < newSize; i++)fputc(fgetc(setSizeFilePointer), editFilePointer);
		fclose(editFilePointer);
		fclose(setSizeFilePointer);
		remove(setSizeFileName.str().c_str());
	}
	return;
}

char FileLibrary::File::getCharacter(FileLibrary::FilePosition position)const
{
	char result;
	FILE *editFilePointer;
	std::stringstream copyFileName;
	copyFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(copyFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	fseek(editFilePointer, position, SEEK_SET);
	result = fgetc(editFilePointer);
	fclose(editFilePointer);
	return result;
}

void FileLibrary::File::setCharacter(char newCharacter, FileLibrary::FilePosition position)
{
	FILE *editFilePointer;
	FILE *setCharacterFilePointer;
	std::stringstream editFileName;
	std::stringstream setCharacterFileName;
	int character;
	if(position >= this->getSize())this->setSize(position + 1);
	editFileName << this->id << FileLibrary::File::editFileExtention;
	setCharacterFileName << this->id << FileLibrary::File::setCharacterFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	setCharacterFilePointer = fopen(setCharacterFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	for(FileLibrary::FilePosition i = 0; i < position; i++)fputc(fgetc(editFilePointer), setCharacterFilePointer);
	fseek(editFilePointer, 1, SEEK_CUR);
	fputc(newCharacter, setCharacterFilePointer);
	character = fgetc(editFilePointer);
	while(character != EOF)
	{
		fputc(character, setCharacterFilePointer);
		character = fgetc(editFilePointer);
	}
	fclose(editFilePointer);
	fclose(setCharacterFilePointer);
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	setCharacterFilePointer = fopen(setCharacterFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	character = fgetc(setCharacterFilePointer);
	while(character != EOF)
	{
		fputc(character, editFilePointer);
		character = fgetc(setCharacterFilePointer);
	}
	fclose(editFilePointer);
	fclose(setCharacterFilePointer);
	remove(setCharacterFileName.str().c_str());
	return;
}

void FileLibrary::File::insert(std::string str, FileLibrary::FilePosition position)
{
	FILE *editFilePointer;
	FILE *insertFilePointer;
	std::stringstream editFileName;
	std::stringstream insertFileName;
	int character;
	if(position > this->getSize())this->setSize(position);
	editFileName << this->id << FileLibrary::File::editFileExtention;
	insertFileName << this->id << FileLibrary::File::insertFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	insertFilePointer = fopen(insertFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	for(FileLibrary::FilePosition i = 0; i < position; i++)fputc(fgetc(editFilePointer), insertFilePointer);
	for(FileLibrary::FilePosition i = 0; i < str.size(); i++)fputc(str[i], insertFilePointer);
	for(FileLibrary::FilePosition i = position; i < this->getSize(); i++)fputc(fgetc(editFilePointer), insertFilePointer);
	fclose(editFilePointer);
	fclose(insertFilePointer);
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	insertFilePointer = fopen(insertFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	character = fgetc(insertFilePointer);
	while(character != EOF)
	{
		fputc(character, editFilePointer);
		character = fgetc(insertFilePointer);
	}
	fclose(editFilePointer);
	fclose(insertFilePointer);
	remove(insertFileName.str().c_str());
	return;
}

void FileLibrary::File::cut(FileLibrary::FilePosition startingPoint, FileLibrary::FilePosition length)
{
	FILE *editFilePointer;
	FILE *cutFilePointer;
	std::stringstream editFileName;
	std::stringstream cutFileName;
	int character;
	if(startingPoint >= this->getSize())return;
	if(startingPoint + length >= this->getSize())return this->setSize(startingPoint);
	editFileName << this->id << FileLibrary::File::editFileExtention;
	cutFileName << this->id << FileLibrary::File::cutFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	cutFilePointer = fopen(cutFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	for(FileLibrary::FilePosition i = 0; i < startingPoint; i++)fputc(fgetc(editFilePointer), cutFilePointer);
	fseek(editFilePointer, (long)length, SEEK_CUR);
	for(FileLibrary::FilePosition i = startingPoint + length; i < this->getSize(); i++)fputc(fgetc(editFilePointer), cutFilePointer);
	fclose(editFilePointer);
	fclose(cutFilePointer);
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	cutFilePointer = fopen(cutFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	character = fgetc(cutFilePointer);
	while(character != EOF)
	{
		fputc(character, editFilePointer);
		character = fgetc(cutFilePointer);
	}
	fclose(editFilePointer);
	fclose(cutFilePointer);
	remove(cutFileName.str().c_str());
	return;
}

FileLibrary::FilePosition FileLibrary::File::countCharacter(char character)const
{
	FileLibrary::FilePosition result = 0;
	FILE *editFilePointer;
	std::stringstream editFileName;
	int readCharacter;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	readCharacter = fgetc(editFilePointer);
	while(readCharacter != EOF)
	{
		if(readCharacter == character)result++;
		readCharacter = fgetc(editFilePointer);
	}
	fclose(editFilePointer);
	return result;
}

FileLibrary::LineNumber FileLibrary::File::getLinage(void)const
{
	return (FileLibrary::LineNumber)this->countCharacter('\n') + 1;
}

std::string FileLibrary::File::getLine(FileLibrary::LineNumber lineNumber)const
{
	std::string result = "";
	FILE *editFilePointer;
	std::stringstream editFileName;
	FileLibrary::FilePosition lineCounter = 1;
	int character;
	if(lineNumber > this->getLinage())return result;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	while(lineCounter < lineNumber)if(fgetc(editFilePointer) == '\n')lineCounter++;
	character = fgetc(editFilePointer);
	while(character != '\n' && character != EOF)
	{
		result = result + (char)character;
		character = fgetc(editFilePointer);
	}
	fclose(editFilePointer);
	return result;
}

void FileLibrary::File::setLine(std::string str, FileLibrary::LineNumber lineNumber)
{
	FILE *editFilePointer;
	std::stringstream editFileName;
	FileLibrary::FilePosition lineCounter = 1;
	int character;
	if(lineNumber > this->getLinage())
	{
		for(FileLibrary::LineNumber i = this->getLinage(); i < lineNumber; i++)str = '\n' + str;
		this->insert(str, this->getSize());
		return;
	}
	editFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	while(lineCounter < lineNumber)if(fgetc(editFilePointer) == '\n')lineCounter++;
	this->cut((FileLibrary::FilePosition)ftell(editFilePointer), this->getLine(lineNumber).size());
	this->insert(str, (FileLibrary::FilePosition)ftell(editFilePointer));
	fclose(editFilePointer);
	return;
}

void FileLibrary::File::addLine(std::string str, FileLibrary::LineNumber lineNumber)
{
	FILE *editFilePointer;
	std::stringstream editFileName;
	FileLibrary::FilePosition lineCounter = 1;
	int character;
	if(lineNumber > this->getLinage())
	{
		for(FileLibrary::LineNumber i = this->getLinage(); i < lineNumber; i++)str = '\n' + str;
		this->insert(str, this->getSize());
		return;
	}
	editFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	while(lineCounter < lineNumber)if(fgetc(editFilePointer) == '\n')lineCounter++;
	this->insert(str + '\n', (FileLibrary::FilePosition)ftell(editFilePointer));
	fclose(editFilePointer);
	return;
}

void FileLibrary::File::cutLines(FileLibrary::LineNumber startLine, FileLibrary::LineNumber linage)
{
	FILE *editFilePointer;
	std::stringstream editFileName;
	FileLibrary::LineNumber lineCounter = 1;
	FileLibrary::FilePosition startingPosition, length;
	if(startLine > this->getLinage())return;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	while(lineCounter < startLine)if(fgetc(editFilePointer) == '\n')lineCounter++;
	startingPosition = (FileLibrary::FilePosition)ftell(editFilePointer);
	if(startLine + linage - 1 >= this->getLinage())
	{
		this->cut(startingPosition, this->getSize() - startingPosition);
		fclose(editFilePointer);
		return;
	}
	while(lineCounter < startLine + linage)if(fgetc(editFilePointer) == '\n')lineCounter++;
	length = (FileLibrary::FilePosition)ftell(editFilePointer) - startingPosition;
	this->cut(startingPosition, length);
	fclose(editFilePointer);
	return;
}

void FileLibrary::File::save(void)
{
	FILE *filePointer;
	FILE *editFilePointer;
	std::stringstream editFileName;
	int character;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	filePointer = fopen(this->fileName.c_str(), FileLibrary::File::writeBinary.c_str());
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	character = fgetc(editFilePointer);
	while(character != EOF)
	{
		fputc(character, filePointer);
		character = fgetc(editFilePointer);
	}
	fclose(filePointer);
	fclose(editFilePointer);
	return;
}

FileLibrary::File FileLibrary::File::operator=(FileLibrary::File operand)
{
	FILE *filePointer;
	FILE *editFilePointer;
	std::stringstream fileName;
	std::stringstream editFileName;
	FileLibrary::File::maxid++;
	this->id = FileLibrary::File::maxid;
	this->fileName = operand.fileName;
	fileName << operand.id << FileLibrary::File::editFileExtention;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	filePointer = fopen(fileName.str().c_str(), FileLibrary::File::readBinary.c_str());
	editFilePointer = fopen(editFileName.str().c_str(), FileLibrary::File::writeBinary.c_str());
	if(filePointer == NULL)fclose(editFilePointer);
	else
	{
		int character = fgetc(filePointer);
		while(character != EOF)
		{
			fputc(character, editFilePointer);
			character = fgetc(filePointer);
		}
		fclose(filePointer);
		fclose(editFilePointer);
	}
	return *this;
}

