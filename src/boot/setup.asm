INITSEG     equ     0x9000
SYSSEG      equ     0x1000
SETUPSEG    equ     0x9020

    jmp     start


start:

    mov     ax, INITSEG ; 把数据存在原来bootsect的位置
    mov     ds, ax
    mov		es, ax
    mov		di, 0x30

;取得画面模式
V640x480 equ   0x101
V1280x1024 equ   0x107
    mov        CX,V640x480
    mov        AX,0x4f01
    INT        0x10
    CMP        AX,0x004f
    JNE        scrn320

    mov        AX,[ES:DI+0x12]
    mov        [0x20],AX
    mov        AX,[ES:DI+0x14]
    mov        [0x22],AX
    mov        EAX,[ES:DI+0x28]
    mov        [0x24],EAX

    mov        BX,0x400+V640x480
    mov        AX,0x4f02
    INT        0x10

    JMP        after

scrn320:
    mov     ax, 0x0013 
    int     0x10

after:
    ; 读取内存大小
    mov     ax, 0xe801
    int     0x15
    mov     [0x02], ax
    mov     [0x04], bx


; 文件系统读取64KB
    mov     ax, 0x8000 ; 把数据存在原来bootsect的位置
    mov		es, ax
    mov     bx, 0x00; 移动到0x90030

; 读取磁盘
    mov     ax, 0x0211;  读一个扇区
    mov     ch, 0x0a; 磁道号
    mov     cl, 0x02; 扇区号
    mov     dh, 0x01; 磁头号
    mov		dl, 0x00; A驱动器
    int     0x13

    ; mov     ax, es
    ; add     ax, 0x20
    ; mov     es, ax
    ; mov     ax, 0x0201;  读一个扇区
    ; mov     dh, 0x01; 磁头号
    ; mov     ch, 0x0a; 磁道号
    ; mov     cl, 3; 扇区号
    ; mov		dl, 0x00; A驱动器    
    ; int     0x13

; readloop:
; 	mov		SI,0			; 记录失败次数寄存器

; retry:
;     mov		dl, 0x00		; A驱动器
;     INT		0x13			; 调用磁盘BIOS
;     JNC		next			; 没出错则跳转到fin
;     ADD		SI,1			; 往SI加1
;     CMP		SI,5			; 比较SI与5
;     JAE		error			; SI >= 5 跳转到error
;     mov		AH,0x00
;     mov		DL,0x00			; A驱动器
;     INT		0x13			; 
;     JMP		retry
; next:
;     mov		AX,ES			; 把内存地址后移0x200（512/16十六进制转换）
;     ADD		AX,0x0020
;     mov		ES,AX			; ADD ES,0x020因为没有ADD ES，只能通过AX进行
;     ADD		CL,1			; 往CL里面加1
;     CMP		CL,18			; 比较CL与18
;     JBE		readloop		; CL <= 18 跳转到readloop
;     mov		CL,1
;     ADD		DH,1
;     CMP		DH,2
;     JB		readloop		; DH < 2 跳转到readloop
;     mov		DH,0
;     ADD		CH,1
;     CMP		CH,10      ; !!!!!!! 读取30个柱面 也就是 30*36个扇区，30*36&512/1024 540KB
;     JB		readloop		; CH < CYLS 跳转到readloop
    
    ; 检查是不是hd1
    ; mov     ax, 0x1500
    ; mov     dl, 0x81
    ; int     0x13
    ; jc      no_disk1
    ; cmp     ah, 3
    ; je      is_disk1

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
    cmp     ax, 0x8000
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

error:
    jmp $

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
