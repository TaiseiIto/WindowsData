rem It enabled the compiler to output x86 executable files.
call "D:\Taisei\Visual Studio 2015\vcvarsallx86.bat"
rem The compiler compiles RandomWalk.c.
cl /Tc..\RandomWalk.c /FoRandomWalk.obj /link /OUT:RandomWalk.scr
rem This file is not completed.
