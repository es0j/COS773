#include "config.h"


void enableInterrupt(){
    asm("sti");
}

void disableInterrupt(){
    asm("cli");
}

void outb( unsigned short port, unsigned char val )
{
   asm volatile("out  %1, %0" : : "a"(val), "Nd"(port) );
}

unsigned char inb (unsigned short int port)
{
  unsigned char _v;

  __asm__ __volatile__ ("in %0, %w1":"=a" (_v):"Nd" (port));
  return _v;
}

void printNum(int num){
    char chars[10]={0};
    for(int i=0;i<10;i++){
        chars[i] = '0'+num%10;
        num=num/10;
    }

    for(int i=0;i<10;i++){
        earlyPutch(chars[9-i]);
    }
    earlyPutch('\n');
    earlyPutch('\r');

    
}

int earlyPutch(char inputchar){
    asm(
        "mov al, %0           \n"
        "mov edx, %1 \n"
        "out dx, ax           \n"
        :
        :"r"(inputchar),"i"(SERIAL_PORT)
        : "rdx","rax"
        //DONT FORGET
        );
}

int earlyPrintf(char *s){
    while(*s!='\0'){
        earlyPutch(*s++);
    }
    earlyPutch('\n');
    earlyPutch('\r');
}



void picRemap()
{
  outb( PIC1_CTRL,0x11 ); 
  outb( PIC2_CTRL,0x11 ); 

  /* ICW2 */
  outb( PIC1_DATA,0x20 ); /* Master offset of 0x20 in the IDT */
  outb( PIC2_DATA,0x28 ); /* Master offset of 0x28 in the IDT */

  /* ICW3 */
  outb( PIC1_DATA,0x04 ); /* Slaves attached to IR line 2 */
  outb( PIC2_DATA,0x02 ); /* This slave in IR line 2 of master */

  /* ICW4 */
  outb( PIC1_DATA,0x05 ); /* Set as master */
  outb( PIC2_DATA,0x01 ); /* Set as slave */

  // Setup Interrupt Mask Register (IMR)
  outb(PIC1_DATA, 0xFd); // 1111 1101 - Enable IRQ 1 only (keyboard).
  outb(PIC2_DATA, 0xFF);
  enableInterrupt();
}