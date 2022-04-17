global start

_pg_dir     equ     0x0000  ;   页目录地址
pg0         equ     0x1000
pg1         equ     0x2000
pg2         equ     0x3000
pg3         equ     0x4000

extern main
extern response_keyboard
extern response_mouse
extern response_pit
extern switch_task

global get_gdt
global get_idt
global asm_response_keyboard
global asm_response_mouse
global asm_response_pit
global final

_tmp_floppy_area    equ     0x5000;     软盘缓冲区地址
len_floppy_area     equ     0x400;      缓冲区大小1KB
[bits 32]
    jmp     start
    times _tmp_floppy_area+len_floppy_area-($-$$) db 0  ;
start:
    mov     eax, 2 * 8
    mov     ds, eax
    mov     es, eax
    mov     fs, eax
    mov     gs, eax
    mov     gs, eax
    mov     ss, eax ; lss

    mov     esp, 0x1e25c        ; 重新设置堆栈，暂时设置值参见书
                                ;《Linux内核设计的艺术_图解Linux操作系统架构
                                ; 设计与实现原理》P27
                                ; Linus源程序中是lss _stack_start,%esp 
                                ; _stack_start,。定义在kernel/sched.c，82-87行
                                ; 它是指向 user_stack数组末端的一个长指针 

    call    setup_idt
    call    setup_gdt
	MOV		EAX,CR0
	AND		EAX,0x7fffffff	; 设bit31为0（禁用分页）
	OR		EAX,0x00000001	; bit0到1转换（保护模式过渡）
	MOV		CR0,EAX
	

	call  A20open

;前面3个入栈0值分别表示main函数的参数envp、argv指针和argc，但main()没有用到。
;push _main入栈操作是模拟调用main时将返回地址入栈的操作，所以如果main.c程序
;真的退出时，就会返回到这里的标号L6处继续执行下去，也即死循环。push _main将
;main.c的地址压入堆栈。这样，在设置分页处理（setup_paging）结束后执行'ret'
;返回指令时就会将main.c;程序的地址弹出堆栈，并去执行main.c程序了。

push 0 ;These are the parameters to main :-)
push 0 ;这些是调用main程序的参数（指init/main.c）。
push 0  
push L6 ;return address for main, if it decides to.
push main ;'_main'是编译程序对main的内部表示方法。
jmp  setup_paging   ;这里用的JMP而不是call，就是为了在setup_paging结束后的
                    ;ret指令能去执行C程序的main(),ret 弹出栈顶的地址，并跳转到该地址执行
L6:
jmp L6 ;main程序绝对不应该返回到这里。不过为了以防万一，
     ;所以添加了该语句。这样我们就知道发生什么问题了。

;Linux将内核的内存页表直接放在页目录之后，使用了4个表来寻址16 MB的物理内存。
;如果你有多于16 Mb的内存，就需要在这里进行扩充修改。
;每个页表长为4KB（1页内存页面），而每个页表项需要4个字节，因此一个页表共可存
;1024个表项。一个页表项寻址4KB的地址空间，则一个页表就可以寻址4MB的物理内存。
setup_paging:

;下面4句设置页目录表中的项。因为内核共有4个页表，所以只需设置4项(索引)。
;页目录项的结构与页表中项的结构一样，4个字节为1项。
;例如"pg0+7"表示：0x00001007，是页目录表中的第1项。
;则第1个页表所在的地址 = 0x00001007 & 0xfffff000 = 0x1000；
;第1个页表的属性标志 = 0x00001007&0x00000fff = 0x07,表示该页存在、用户可读写。
;一句指令就把页表的地址和属性完全完整定义了，这个写法设计得有点巧妙。    
; mov dword [_pg_dir],pg0+7       ;页表0索引 将直接覆盖0地址处的3字节长度jmp指令 
; mov dword [_pg_dir+4],pg1+7     ;页表1索引
; mov dword [_pg_dir+8],pg2+7     ;页表2索引
; mov dword [_pg_dir+12],pg3+7    ;页表3索引 


;下面填写4个页表中所有项的内容，共有：4(页表)*1024(项/页表)=4096项(0-0xfff)，
;也即能映射物理内存 4096*4Kb = 16Mb。
;每项的内容是：当前项所映射的物理内存地址 + 该页的标志（这里均为7）。
;填写使用的方法是从最后一个页表的最后一项开始按倒退顺序填写。
;每一个页表中最后一项在表中的位置是1023*4 = 4092.
;此最后一页的最后一项的位置就是pg3+4092。
; mov edi,pg3+4092;edi->最后一页的最后一项。
; mov eax,0xfff007;16Mb - 4096 + 7 (r/w user,p) */
; ;最后1项对应物理内存页面的地址是0xfff000，
; ;加上属性标志7，即为0xfff007。
; std ;方向位置位，edi值递减(4字节)。
; goon:
; stosd  
; sub eax,0x1000;每填写好一项，物理地址值减0x1000。
; jge goon ;如果小于0则说明全添写好了。  jge是大于或等于转移指令


; ;现在设置页目录表基址寄存器cr3，指向页目录表。cr3中保存的是页目录表的物理地址
; ;再设置启动使用分页处理（cr0的PG标志，位31）
; xor eax,eax ;pg_dir is at 0x0000 */ # 页目录表在0x0000处。
; mov cr3,eax ;cr3 - page directory start */
; mov eax,cr0
; or eax,0x80000000  ;添上PG标志。
; mov cr0,eax ; set paging (PG) bit */
     
ret  ;setup_paging这里用的是返回指令ret。
;该返回指令的另一个作用是将压入堆栈中的main程序的地址弹出，
;并跳转到/init/main.c程序去运行。本程序到此就真正结束了。      
 
;用于测试A20地址线是否已经开启。采用的方法是向内存地址0x000000处写入任意
;一个数值，然后看内存地址0x100000(1M)处是否也是这个数值。如果一直相同的话，
;就一直比较下去，也即死循环表示地址A20线没有选通，就不能使用1MB以上内存。
A20open:
       xor   eax, eax
       inc   eax 
       mov   [0x000000],eax   
       cmp   eax,[0x100000]
       je    A20open
       ret

setup_idt:
          ;暂时将所有的中断全部指向一个中断服务程序:ignore_int 
          lea  edx,[ignore_int]   ;将ignore_int的有效地址（偏移值）值送edx 
          mov  eax,0x00080000  ;将选择符0x0008置入eax的高16位中。
          mov  ax,dx           ;selector = 0x0008 = cs */
                               ;偏移值的低16位置入eax的低16位中。此时eax含有门
                               ;描述符低4字节的值。
          mov dx,0x8E00        ;interrupt gate - dpl=0, present 
                               ;此时edx含有门描述符高4字节值,偏移地址高16位是0 
          lea edi,[_idt]       ;_idt是中断描述符表的地址。
          ;以上为单独一个中断描述符的设置方法 
          
          mov ecx,256          ;IDT表中创建256个中断描述符 
;将上面的中断描述符重复放置256次，让所有的中断全部指向一个中断服务程序:哑中断
 rp_sidt:
          mov [edi],eax       ;将哑中断门描述符存入表中。
          mov [edi+4],edx     ;edx内容放到 edi+4 所指内存位置处。
          add  edi,8           ; edi指向表中下一项。
          loop rp_sidt    
              
          lidt [idt_descr]       ;加载中断描述符表寄存器值。
          ret          
                               
 
;让所有的256中断都指向这个统一的中断服务程序                        
ignore_int:
           cli               ;首先应禁止中断,以免中断嵌套 
           pushad            ;进入中断服务程序首先保存32位寄存器

           push ds           ;再保存所有的段寄存器
	   push es
	   push fs
	   push gs
	   push ss
	   mov  eax,2*8      ;进入断服务程序后所有数据类段寄存器都转到内核段
           mov ds,eax
           mov es,eax
           mov fs,eax
           mov gs,eax
           mov ss,eax

	;   mov  esi,intmsg                ;保护模式DS=0,数据用绝对地址访问
        ;   mov  cl, 0x09                  ;蓝色
        ;   mov  edi, 0xb8000+18*160       ;指定显示在某行,显卡内存需用绝对地址
          ;call print_str

           pop ss             ;恢复所有的段寄存器
	   pop gs
	   pop fs
	   pop es
	   pop ds
	   
           popad              ; 所有32位寄存器出栈恢复
           iret                ;中断服务返回指令 


align 2 ;按4字节方式对齐内存地址边界。
dw    0 ;这里先空出2字节，这样_idt长字是4字节对齐的。 
                               
;下面是加载中断描述符表寄存器idtr的指令lidt要求的6字节操作数。
;前2字节是idt表的限长，后4字节是idt表在线性地址空间中的32位基地址。
idt_descr:
         dw 256*8-1 ;idt contains 256 entries # 共256项，限长=长度 - 1。
         dd _idt                               
         ret
         

    
setup_gdt:

        lgdt [gdt_descr] ;加载全局描述符表寄存器。
        ret


align 2 ;按4字节方式对齐内存地址边界。
dw    0 ;这里先空出2字节，这样_gdt长字是4字节对齐的。

;加载全局描述符表寄存器gdtr的指令lgdt要求的6字节操作数。前2字节是gdt表的限长，
;后4字节是gdt表的线性基地址。因为每8字节组成一个描述符项，所以表中共可有256项。
;符号_gdt是全局表在本程序中的偏移位置。
gdt_descr:
        dw 256*8-1  
        dd _gdt 
 
;IDT表和GDT表放在程序head的最末尾

;中断描述符表：256个，全部初始化为0。        
_idt:    times 256  dq 0  ;idt is uninitialized # 256项，每项8字节，填0。

 
;全局描述符表。其前4项分别是：空项、代码段、数据段、系统调用段描述符，
;后面还预留了252项的空间，用于放置新创建任务的局部描述符(LDT)和对应的
;任务状态段TSS的描述符。
;(0-nul,1-cs,2-ds,3-syscall,4-TSS0,5-LDT0,6-TSS1,7-LDT1,8-TSS2 etc...)        
_gdt: dq 0x0000000000000000 ;NULL descriptor */
;       dq 0x00c09a0000000fff ;16Mb */ # 0x08，内核代码段最大长度16MB。
;       dq 0x00c0920000000fff ;16Mb */ # 0x10，内核数据段最大长度16MB。
      dq 0x00c09a000000ffff ;16Mb */ # 0x08，内核代码段最大长度16MB。
      dq 0x00cf92000000ffff ;16Mb */ # 0x10，内核数据段最大长度4GB。
      dq 0x0000000000000000 ;TEMPORARY - don't use */
      times 252 dq 0        ;space for LDT's and TSS's etc */ #

print_str:                       ;保护模式下显示字符串, 以'$'为结束标记
        mov  bl ,[ds:esi]
        cmp  bl, '$'
        je   print_over
        mov  byte [ds:edi],bl
        inc  edi
        mov  byte [ds:edi], cl  ;字符红色 
        inc  esi
        inc  edi
        jmp  print_str
print_over:
        ret

get_gdt:
        mov     eax, _gdt
        ret

get_idt:
        mov     eax, _idt
        ret

asm_response_keyboard:
        call    response_keyboard
        iret

asm_response_mouse:
        call    response_mouse
        iret

asm_response_pit:
        call    response_pit
        iret

final:
        lea     eax, [final]
        ret

switch_task:
        ; jmp     far [esp+4]
        jmp     4*8:0
        ret