
; �T���v�� x64 �A�Z���u���[�E�v���O����

; Chris Lomont 2009 www.lomont.org

extrn ExitProcess: PROC   ; �V�X�e���E���C�u�����[�̊O���֐�

extrn MessageBoxA: PROC

includelib "user32.lib"

includelib "kernel32.lib"

.data

caption db "�U�S�т���", 0

message db "������ف[��", 0

.code

Start PROC

  sub    rsp, 28h     ; �V���h�E�̈�A�X�^�b�N���A���C�����g����

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

 

; fastcall�i�V�����֐��Ăяo���K��j

; ������rcx�Ardx�Ar8�Ar9�Ar10�Ar11

; �߂�l��rax

; ���������_���̖߂�l��xmm0
