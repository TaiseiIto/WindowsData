@echo off
REM cl LangtonsAnt.cpp /EHsc /c /I..\..\Headers /I..\..\..\C\Headers /FoLangtonsAnt.obj
cl LangtonsAnt.cpp /EHsc /c /I..\..\Headers /FoLangtonsAnt.obj
REM link LangtonsAnt.obj ..\..\Libraries\MathLibrary.obj ..\..\..\C\Libraries\MyLibrary.obj "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /OUT:LangtonsAnt.scr
link LangtonsAnt.obj ..\..\Libraries\MathLibrary.obj "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /OUT:LangtonsAnt.exe

