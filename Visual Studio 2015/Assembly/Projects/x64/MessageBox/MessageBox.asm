
; サンプル x64 アセンブリー・プログラム

; Chris Lomont 2009 www.lomont.org

extrn ExitProcess: PROC   ; システム・ライブラリーの外部関数

extrn MessageBoxA: PROC

includelib "user32.lib"

includelib "kernel32.lib"

.data

caption db "６４びっと", 0

message db "いやっほーい", 0

.code

Start PROC

  sub    rsp, 28h     ; シャドウ領域、スタックをアライメントする

  mov    rcx, 0

  lea    rdx, message

  lea    r8,  caption

  mov    r9, 0

  call   MessageBoxA

  mov    ecx, eax

  call   ExitProcess

Start ENDP

End

 

; /entry:Start

 

; fastcall（新しい関数呼び出し規約）

; 引数はrcx、rdx、r8、r9、r10、r11

; 戻り値はrax

; 浮動小数点数の戻り値はxmm0
