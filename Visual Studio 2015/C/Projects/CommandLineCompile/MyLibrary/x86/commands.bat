rem It enables the conpiler to output x86 object files.
call "D:\Taisei\Visual Studio 2015\vcvarsallx86.bat"
rem The compiler outputs an object file.
cl /c /Tc..\MyLibrary.c /FoMyLibrary.obj

