#include <stdint.h>

char *helloStr="#Hello world from C!\r\n";
#define IDT_ENTRIES 256


extern void isr_wrapper();
extern void isr_wrapper_keyboard();
extern void kernel_main();


int earlyPutch(char inputchar){
    asm(
        "mov al, %0         \n"
        "mov edx, 0x3f8     \n"
        "out dx, ax         \n"
        :
        :"r"(inputchar)
        : "rdx","rax"
        //DONT FORGET
        );
}

int earlyPrintf(char *s){
    while(*s!='\0'){
        earlyPutch(*s++);
    }
}

struct idtdesc64 {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t zero;            // reserved
}__attribute__ ((packed));

struct idtr64 {
    uint16_t limite;
    uint64_t base;
} __attribute__ ((packed));

void init_idt_desc(uint16_t select, uint64_t offset, uint8_t type,uint8_t ist, struct idtdesc64 *desc)
{
    desc->offset_1 = offset&0xffff;
    desc->selector = select;
    desc->ist = ist;
    desc->type_attributes = type;
    desc->offset_2 = offset&0xffff0000;
    desc->offset_3 = offset&0xffffffff00000000;
    desc->zero = 0;
    return;
}

struct idtr64 kidtr;
struct idtdesc64 kidt[IDT_ENTRIES];

//default
void interrupt_handler(){

  earlyPrintf("default interruption\r\n");
    outb(0x20,0x20);
  //outb(0xA0,0x20);
}

void keyboardInt(){
  char data;
  data=inb(0x60);
  earlyPrintf("keyboard pressed: ");
  earlyPutch('A'+data);
  earlyPrintf("\r\n");
  outb(0x20,0x20);
  //outb(0xA0,0x20);

}

void init_idt()
{
    /* Init irq */
    for (int i = 0; i < IDT_ENTRIES; i++)
      //64-bit Interrupt Gate: 0x8E (p=1, dpl=0b00, type=0b1110 => type_attributes=0b1000_1110=0x8E)
      init_idt_desc(0x18, (uint64_t)isr_wrapper, 0x8E,0, &kidt[i]); //

    //for (int i = 10; i < 14; i++)
    init_idt_desc(0x18, (uint64_t)isr_wrapper_keyboard, 0x8E,0, &kidt[9]); //keyboard

    kidtr.limite = IDT_ENTRIES * 16;
    kidtr.base = (uint64_t)&kidt;

    /* Load the IDTR registry */
    asm(
        "lidt (kidtr) \n"
        );

}

int main(){
    asm("mov rsp,0x1000000\n");
    asm("mov rbp,rsp       \n");
    init_idt();
    //clear screen magic
    earlyPrintf("\x1b[2J\x1B[H\n\r");
    earlyPrintf(helloStr);

    //outb(0x21,0xfd);
    //outb(0xa1,0xff);
    //asm("sti");
    //outb(0x64, 0xF4);
    //outb(0x60, 0xF4);

    /*while (1)
    {
      //asm("INT 50");
      /* code */
      //asm("sti");
    //}
    
    kernel_main();
}




















