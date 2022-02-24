    jmp     start

%include "boot/config.inc"
SETUPLEN    equ     4       ; setup占4个扇区
SYSSIZE     equ     0x3000
BOOTSEG     equ     0x07c0
ENDSEG      equ     SYSSEG + SYSSIZE		; 0x4000

;root_dev定义在引导扇区508，509字节处
;当编译内核时，你可以在Makefile文件中指定自己的值。内核映像文件Image的
;创建程序tools/build会使用你指定的值来设置你的根文件系统所在设备号。
ROOT_DEV    equ     0x306


start:
    mov     ax, BOOTSEG
    mov     ds, ax
    mov     ax, INITSEG
    mov     es, ax
    mov     cx, 512/4
    mov     si, 0
    mov     di, 0

; 将bootsect从BOOTSEG复制到INITSEG处
    rep
    movsd   ;   一次移动32B
    jmp     INITSEG:go ; 跳转到复制后的bootsect继续执行

go:
    mov     ax, cs ;cs = 0x9000
    mov     ds, ax
    mov     es, ax
    ; 让栈位于0x9ff00,栈大小为65280
    mov     ss, ax
    mov     sp, 0xff00


load_setup:
    mov     bx, 0x0200
    mov     ax, 0x0204      ; 读盘，读4个扇区
    mov     cx, 0x0002      ; 0磁道， 扇区从1号开始，1号为引导扇区，所以从2号开始读
    mov     dx, 0x0000      ; 驱动器0，磁头0
    int     0x13
    jnc     load_setup_ok
    ; 失败重置驱动器， 重新读
    mov     dx, 0x0000
    mov     ax, 0x0000
    int     0x13
    jmp     load_setup

load_setup_ok:
; 获取驱动器参数
    mov     dl, 0x00
    mov     ax, 0x0800  ; INT 13h AH=08h: Read Drive Parameters
    int     0x13
    ; 返回值
    ; dl 硬盘数量,
    ; dh 最后一个head的下标,(数量-1)
    ; bl drive type (only AT/PS2 floppies)
    ; ch=最大磁道号低8位，cl=每磁道最大扇区数（0-5位），最大磁道号高2位（6-7位）
    ; ES:DI	pointer to drive parameter table (only for floppies)
    mov     [sectors], cl ; 存储扇区数
    mov     ax, INITSEG   ; 重置es段
    mov     es, ax

;   打印欢迎信息
    mov     si, start_msg
    call    show_msg

; 加载系统到0x10000        
    mov     ax, SYSSEG
    mov     es, ax
    call    read_it
    call    kill_motor

; 没明白
    mov     ax, [root_dev]
    cmp     ax, 0x0000
    jne     root_defined
    mov     bx, [sectors]
    mov     ax, 0x0208      ; 1.2M
    cmp     bx, 15
    je      root_defined
    mov	    ax, 0x021c		; /dev/PS0 - 1.44Mb
	cmp	    bx, 18
	je	    root_defined
undef_root:
	jmp     undef_root
root_defined:
	mov	[root_dev],ax

    jmp     SETUPSEG:0x0000

read_it:
    mov     bx, 0
repeat_read:
; ax 记录读到哪了
    mov     ax, es
	cmp     ax, ENDSEG
    jb      ok1_read
    ret

ok1_read:
; 取当前磁道的扇区数，计算是否超过64kB
; 是，计算能读取的最大值；否，执行ok2_read
    mov     ax, [sectors]   ; 扇区总数
    sub     ax, [sread]     ; 总数-当前 有多少个扇区需要读取 存在ax中
    mov     cx, ax          ; 
    shl     cx, 9           ; cx *= 512, 13 * 512 = 6656
    add     cx, bx          ; cx + bx 当前偏移，是否溢出
    jnc     ok2_read        ; 没有产生进位 cx + bx < 64kB
    je      ok2_read

    mov     ax, 0
    sub     ax, bx
    shr     ax, 9           ; 读完之后 还能读多少扇区
    
ok2_read:
; 执行读取操作（跳转到了read_track）
; 传输的扇区数存储在AL中，判断是否已经读完当前磁道的所有扇区
; 是，顺序执行，如果当前磁头是0，则磁道号+1，执行ok4_read
; 如果磁头号是1，则直接跳转到ok4_read；否，执行ok3_read
    call    read_track      ;  读取当前磁道 磁头 扇区
    mov     cx, ax          ;  ax 未读
    add     ax, [sread]     ;  未读 + 已读
    cmp     ax, [sectors]   ; 
    jne     ok3_read        ;  未读 + 已读 != 18   
    mov     ax, 0x01        
    sub     ax, [head]
    jne     ok4_read        ; 1 - head != 0, to ok4
                            ; head = 0, 磁道号+1
    inc     word [track]

ok4_read:
; 保存磁道号，清空ax
; 如果未读完，进入ok3_read；否则，调整基址跳转到rp_read
	mov     [head], ax
	xor     ax, ax      

ok3_read:
; 计算当前已读扇区数量，将读取位置存储在bx中
; 跳转到rp_read，继续读取
	mov     [sread], ax ; 保存已读扇区数
	shl     cx, 0x09    ; 上次已读 * 512
	add     bx, cx      ; bx 偏移增长
	jnc     repeat_read     ; 没溢出就接着读
	mov     ax, es      ; 溢出了就新开一个段,接着读
	add     ax, 0x1000
	mov     es, ax
	xor     bx, bx
	jmp     repeat_read

read_track:
    push    ax
    push    bx
    push    cx
    push    dx
    mov     dx, [track]
	mov     cx, [sread]
	inc     cx
	mov     ch, dl
	mov     dx, [head]
	mov     dh, dl
	mov     dl, 0
	and     dx, 0x0100
	mov     ah, 2
	int     0x13
    jc      bad_rt  ; 失败重置驱动器，重新读
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    ret
bad_rt:	
    mov     ax, 0
	mov     dx, 0
	int     0x13
	pop     dx
	pop     cx
	pop     bx
	pop     ax
	jmp     read_track

kill_motor:
; 这个子程序用于关闭软驱的马达，这样进入内核后就能知道它所处的状态
; 0x3f2是软盘控制器的一个端口，被称为数字输出寄存器（DOR）端口。
	push    dx
	mov     dx, 0x3f2
	mov     al, 0
	outsb   ;将al中的内容输出到dx指定的的地方
	pop     dx
	ret

sectors:    dw      0
sread:	    dw      1 + SETUPLEN; 当前扇区
head:       dw      0			; 当前磁头
track:	    dw      0			; 当前磁道

start_msg:  db      "Welcome PianOS!!!", '$'

; 最后填充整个扇区
    times   508 - ($ - $$) db 0

root_dev:
	dw      0x306
boot_flag:
    dw      0xaa55 
