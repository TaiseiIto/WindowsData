rem It enables the compiler to output x86 executable files.
call "D:\Taisei\Visual Studio 2015\vcvarsallx86.bat"
rem set INCLUDE=%INCLUDE%;D:\Taisei\Visual Studio 2015\C\Headers
rem The compiler compiles Names.c.
cl /Tc..\Names.c /I "D:\Taisei\Visual Studio 2015\C\Projects\CommandLineCompile\MyLibrary" /FoNames.obj
link /OUT:Names.exe "D:\Taisei\Visual Studio 2015\C\Projects\CommandLineCompile\MyLibrary\x86\MyLibrary.obj" Names.obj
rem This file is not completed.(Error:LNK2019)
