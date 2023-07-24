; filename: vector.s
[BITS 64]
global   isr_wrapper
global   isr_wrapper_keyboard
align   4

extern interrupt_handler
extern keyboardInt


%macro SAVE_REGS 0
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi
%endmacro

%macro RESTORE_REGS 0
    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
%endmacro



isr_wrapper:
    SAVE_REGS
    cld    ; C code following the sysV ABI requires DF to be clear on function entry
    call interrupt_handler
    ;pop rax
    RESTORE_REGS
    iretq

isr_wrapper_keyboard:
    SAVE_REGS
    cld    ; C code following the sysV ABI requires DF to be clear on function entry
    call keyboardInt
    ;pop rax
    RESTORE_REGS
    iretq