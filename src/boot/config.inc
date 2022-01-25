INITSEG     equ     0x9000
SYSSEG      equ     0x1000
SETUPSEG    equ     0x9020

show_msg:
    call    _printstr
    call    _newline
    ret

_printstr:
    mov     al, [si]
    cmp     al, '$'
    je      _print_over
    mov     ah, 0x0e
    int     10h
    inc     si
    jmp     _printstr
_print_over:
    ret

_newline:                     ;显示回车换行
      mov   ah, 0x0e
      mov   al, 0x0d
      int   0x10
      mov   al, 0x0a
      int   0x10
      ret