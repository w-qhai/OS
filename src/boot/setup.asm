    jmp     start
    %include    "boot/config.inc"

start:
; 改为图形模式 vga
    mov     ax, 0x0013 
    int     0x10

    mov     ax, INITSEG ; 把数据存在原来bootsect的位置
    mov     ds, ax

    ;  读取光标位置
    mov     ah, 0x03
    mov     bh, 0
    int     0x10

    mov     [0], dx

    ; 读取内存大小
    ; mov     ah, 0x88
    ; int     0x15
    ; mov     [2], ax
    mov     ax, 0xe801
    int     0x15
    mov     [2], ax
    mov     [4], bx

    ; 读取显卡数据
    mov     ah, 0x0f
    int     0x10
    mov     [6], bx ; bh = display page
    mov     [8], ax ; al = video mode, ah = window width

    ; 检查ega, vga 和一些配置数据
    mov     ah, 0x12
    mov     bl, 0x10
    int     0x10

    mov     [10], ax
    mov     [12], bx
    mov     [14], cx

    ; 硬盘数据 hd0
    ; mov     ax, 0x0000
    ; mov     ds, ax
    ; lds     si, [4 * 0x41]
    ; mov     ax, INITSEG
    ; mov     es, ax
    ; mov     di, 0x0000
    ; mov     cx, 0x10
    ; rep
    ; movsb

    ; 硬盘数据 hd1
    ; mov     ax, 0x0000
    ; mov     ds, ax
    ; lds     si, [4 * 0x46]
    ; mov     ax, INITSEG
    ; mov     es, ax
    ; mov     di, 0x0090
    ; mov     cx, 0x10
    ; rep
    ; movsb

    ; 检查是不是hd1
    mov     ax, 0x1500
    mov     dl, 0x81
    int     0x13
    jc      no_disk1
    cmp     ah, 3
    je      is_disk1

no_disk1:
    ; mov     ax, INITSEG
    ; mov     es, ax
    ; mov     di, 0x0090
    ; mov     cx, 0x10
    ; mov     ax, 0x00
    ; rep
    ; stosb

is_disk1:
; 开始进入保护模式
    cli     ; 禁止中断
; 首先将系统移动到0x00000处
    mov     ax, 0x0000
    cld     ; df = 0

do_move:
    ; 将 0x10000~0x90000处的数据移动到0x00000处
    mov     es, ax
    add     ax, 0x1000  ; 目的段
    cmp     ax, 0x9000
    jz      end_move
    mov     ds, ax      ; 源段
    mov     si, 0
    mov     di, 0
    ; 每次移动0x10000-65536字节, 每次移动double word
    mov     cx, 0x10000 / 4 ; 
    ; 从
    rep
    movsd
    jmp     do_move

; 然后加载段描述符

end_move:
    mov     ax, SETUPSEG
    mov     ds, ax

    lidt    [idt_48]
    lgdt    [gdt_48]

;   开启A20
enable_A20:
    call    empty_8042
    mov     al, 0xd1
    out     0x64, al; al的值写入0x64端口
    call    empty_8042
    mov     al, 0xdf
    out     0x60, al
    call    empty_8042

;   8259编程
    mov	    al, 0x11		; initialization sequence
	out	    0x20, al		; send it to 8259A-1
	dw	    0x00eb, 0x00eb  ; jmp $+2, jmp $+2
	out	    0xa0, al		; and to 8259A-2
	dw	    0x00eb, 0x00eb
	mov	    al, 0x20		; start of hardware int's (0x20)
	out	    0x21, al
	dw	    0x00eb, 0x00eb
	mov	    al, 0x28		; start of hardware int's 2 (0x28)
	out	    0xa1, al
	dw	    0x00eb, 0x00eb
	mov	    al, 0x04		; 8259-1 is master
	out	    0x21, al
	dw	    0x00eb, 0x00eb
	mov	    al, 0x02		; 8259-2 is slave
	out	    0xa1, al
	dw	    0x00eb, 0x00eb
	mov	    al, 0x01		; 8086 mode for both
	out 	0x21, al
	dw	    0x00eb, 0x00eb
	out	    0xa1, al
	dw	    0x00eb, 0x00eb
	mov	    al, 0xff		; mask off all interrupts for now
	out	    0x21, al
	dw	    0x00eb, 0x00eb
	out	    0xa1, al

;;;;;;;;;;;;;;;
    ; 开启保护模式标志(PE)
    mov     ax, 0x0001
    lmsw    ax
    ; jmp     8:0 ; 32位寻址

;   更改显示模式为图形模式
    jmp     dword 1*8:((SETUPSEG << 4) + test32)

empty_8042:
    dw      0x00eb, 0x00eb
    in	    al, 0x64	; 8042 status port
	test	al, 2		; is input buffer full?
	jnz	    empty_8042	; yes - loop
	ret     
;
 gdt:
	dw	0,0,0,0		; dummy

	dw	0x07FF		; 8Mb - limit=2047 (2048*4k=8Mb)
	dw	0x0000		; base address=0
	dw	0x9A00		; code read/exec
	dw	0x00C0		; granularity=4096, 386

	dw	0x07FF		; 8Mb - limit=2047 (2048*4k=8Mb)
	dw	0x0000		; base address=0
	dw	0x9200		; data read/write
	dw	0x00C0		; granularity=4096, 386

idt_48:
	dw	0			; idt limit=0
	dw	0,0			; idt base=0L

gdt_48:
	dw	0x800		    ; gdt limit=2048, 256 GDT entries
	dw	512 + gdt, 0x9	; gdt base = 0X9xxxx
    ; 0x0009 2000 + gdt 就是gdt的起始地址

msg:    db  "Load Successfully", '$'

[bits 32]   ; 测试32位程序
test32:
    ; mov     eax, 2 * 8
    ; mov     ds, eax

    ; mov     esi, (SETUPSEG << 4) + sysmsg
    ; mov     edi, 0xb8000 + 18 * 160
    ; ; call    print_str
    jmp     1*8:0

print_str:                       ;保护模式下显示字符串, 以'$'为结束标记
        mov  bl ,[ds:esi]
        cmp  bl, '$'
        je   print_over
        mov  byte [ds:edi],bl
        inc  edi
        mov  byte [ds:edi],0x0c  ;字符红色 
        inc  esi
        inc  edi
        jmp  print_str
print_over:
        ret

sysmsg      db  '(iii) Welcome Linux---system!','$'
