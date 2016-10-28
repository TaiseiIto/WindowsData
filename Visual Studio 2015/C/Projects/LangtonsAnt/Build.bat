@echo off
cl LangtonsAnt.c /c /I..\..\Headers /FoLangtonsAnt.obj
link LangtonsAnt.obj ..\..\Libraries\MyLibrary.obj "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /OUT:LangtonsAnt.scr

