; filename: vector.s
[BITS 64]
global   isr_wrapper
global   isr_wrapper_keyboard

extern interrupt_handler
extern keyboardISR


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
    cld   
    call interrupt_handler
    RESTORE_REGS
    iretq

isr_wrapper_keyboard:
    SAVE_REGS
    cld    
    call keyboardISR

    RESTORE_REGS
    iretq