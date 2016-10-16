#ifndef FILE_LIBRARY
#define FILE_LIBRARY
#include<cstdio>
#include<iostream>
#include<string>
namespace FileLibrary
{
	typedef long FileNumber;
	typedef long FilePosition;
	typedef long LineNumber;
	class File
	{
	private:
		FileLibrary::FileNumber id;
		static FileLibrary::FileNumber maxid;
		std::string fileName;
		static const std::string readBinary;
		static const std::string writeBinary;
		static const std::string editFileExtention;
		static const std::string setSizeFileExtention;
		static const std::string setCharacterFileExtention;
		static const std::string insertFileExtention;
		static const std::string cutFileExtention;
	public:
		File(void);
		File(std::string fileName);
		File(const FileLibrary::File &object);
		~File(void);
		FileLibrary::FilePosition getSize(void)const;
		void setSize(FileLibrary::FilePosition newSize);
		char getCharacter(FileLibrary::FilePosition position)const;
		void setCharacter(char newCharacter, FileLibrary::FilePosition position);
		void insert(std::string str, FileLibrary::FilePosition position);
		void cut(FileLibrary::FilePosition startingPosition, FileLibrary::FilePosition length);
		FileLibrary::FilePosition countCharacter(char character)const;
		FileLibrary::LineNumber getLinage(void)const;
		std::string getLine(FileLibrary::LineNumber lineNumber)const;
		void setLine(std::string str, FileLibrary::LineNumber lineNumber);
		void addLine(std::string str, FileLibrary::LineNumber lineNumber);
		void cutLines(FileLibrary::LineNumber startLine, FileLibrary::LineNumber linage);
		//template<class X>FileLibrary::File operator<<(X operand);
		//template<class X>FileLibrary::File operator>>(X operand);
		void save(void);
		FileLibrary::File operator=(FileLibrary::File operand);
	};
}
/*
template<class X>FileLibrary::File FileLibrary::File::operator<<(X operand)
{
	std::ofstream ofs;
	std::stringstream editFileName;
	editFileName << this->id << FileLibrary::File::editFileExtention;
	ofs = std::ofstream(editFileName.str());
	ofs << operand;
	return *this;
}
*/
#endif

