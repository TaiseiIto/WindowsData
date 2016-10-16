
extrn ExitProcess: PROC

includelib "user32.lib"

includelib "kernel32.lib"

.data

.code

Start PROC

  mov    ecx, eax

  call   ExitProcess

Start ENDP

End
