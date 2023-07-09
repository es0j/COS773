[BITS 16]
[ORG 7c00h]
boot:

    cli
    lgdt [gdtPtr]

    mov ebx,0x1
    mov cr0,ebx
    
    jmp 0x08:protected ; selects the entry number 1, remember the CS must be 1 <<3 due the RPL and IT(?) bits               
    

    
align 4
gdtBase:
    dq  0x0000000000000000 ;Null entry

    dq 0x00cf9a000000ffff ;32 protected cs
    dq 0x00cf92000000ffff ;32 protected ds

    dq 0x00af9a000000ffff    ;64 kernel cs
    dq 0x00af92000000ffff    ;64 kernel ds

gdtPtr:
    dw 0x28 ;5*8=0x28
    dd (gdtBase)


[BITS 32]
protected:
    inc eax
    mov ax, 0x10 ;uses the second gdt entry
    mov ds,ax
    mov ss,ax
    mov es,ax
    mov esp,0xF00000 ; A reasonable Physical address for the stack ~15MB. If the machine contains less RAM its bad.
    push esp
    mov ebp,esp
    mov bl,[testdata] ;sanity check , read 0x55aa, check if protected segmentation is correct


    mov eax,0x20;set PAE for some reason. IDK just following the docs.
    mov cr4,eax

    ; Set LME (long mode enable). Probably allows to use Rax and other stuff
    mov ecx, 0xC0000080
    rdmsr
    or  eax, (1 << 8)
    wrmsr

long_mode:
    ;build the page table on address 0x10000 (i should clean the entries but im lazy)
    mov eax,0x10000
    mov cr3,eax

    mov ebx,0x11003 ;PML4 0x1000->0x11000 RW | Present
    mov [eax],ebx

    ;1GB pages bc im lazy
    mov eax,0x0083
    mov ebx,0x11000 
    mov [ebx],eax ;PDPE 0x11000->0x0000

    mov eax,(1 <<31) | (1)
    mov cr0,eax ;enables pagination

    mov ax,(4 <<3) ;fourth entry on the GDT
    mov ds,ax
    mov es,ax
    mov ss,ax

    mov ax,[testdata]
    nop

    jmp (3 <<3):finished ; Third entry on GDT

[BITS 64]
finished:
    mov rax,0x0068732f6e69622f ; Only possible if in 64 bit mode, copied from shellcode :)
    push rax
    mov rsi, rsp
    call print_string
    
    mov rsi, helostr
    call print_string
    jmp $


;al =arg
print_char:
    mov edx, 0x3f8 ;print using serial port
    out dx, ax
    ret

;esi = arg
print_string:
    mov al,[esi]
    inc esi
    call print_char
    cmp al,0x00
    jnz print_string
    ret


helostr: db "#Hello world from long and paged mode",0x10,0x00 ; Dont know how to print new line

times 510-($-$$) db 0x90

testdata:
db 0x55
db 0xaa
