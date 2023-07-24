#include "pic.h"


extern void earlyPrintf(char *);
extern void earlyPutch(char );

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



int capslock = 0;

char kbd_US [128] =
{
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', -1,   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', -4,
  '*',
  0,  /* Alt */
  ' ',  /* Space bar */
  -3,  /* Caps lock */
  0,  /* 59 - F1 key ... > */
  0,   0,   0,   0,   0,   0,   0,   0,
  0,  /* < ... F10 */
  0,  /* 69 - Num lock*/
  0,  /* Scroll Lock */
  0,  /* Home key */
  0,  /* Up Arrow */
  0,  /* Page Up */
  '-',
  0,  /* Left Arrow */
  0,
  0,  /* Right Arrow */
  '+',
  -2,  /* 79 - End key*/
  0,  /* Down Arrow */
  0,  /* Page Down */
  0,  /* Insert Key */
  0,  /* Delete Key */
  0,   0,   0,
  0,  /* F11 Key */
  0,  /* F12 Key */
  0,  /* All other keys are undefined */
};

char capital_kbd_US [128] =
{
  0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', -5,   
  '\t', /* <-- Tab */
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
  0, /* <-- control key */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',  0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', -8,
  '*',
  0,  /* Alt */
  ' ',  /* Space bar */
  -7,  /* Caps lock */
  0,  /* 59 - F1 key ... > */
  0,   0,   0,   0,   0,   0,   0,   0,
  0,  /* < ... F10 */
  0,  /* 69 - Num lock*/
  0,  /* Scroll Lock */
  0,  /* Home key */
  0,  /* Up Arrow */
  0,  /* Page Up */
  '-',
  0,  /* Left Arrow */
  0,
  0,  /* Right Arrow */
  '+',
  -6,  /* 79 - End key*/
  0,  /* Down Arrow */
  0,  /* Page Down */
  0,  /* Insert Key */
  0,  /* Delete Key */
  0,   0,   0,
  0,  /* F11 Key */
  0,  /* F12 Key */
  0,  /* All other keys are undefined */
};



void pic_remap(int offset1, int offset2)
{

        /* ICW1 */
    outb( 0x20,0x11 ); /* Master port A */
    outb( 0xA0,0x11 ); /* Slave port A */

    /* ICW2 */
    outb( 0x21,0x20 ); /* Master offset of 0x20 in the IDT */
    outb( 0xA1,0x28 ); /* Master offset of 0x28 in the IDT */

    /* ICW3 */
    outb( 0x21,0x04 ); /* Slaves attached to IR line 2 */
    outb( 0xa1,0x02 ); /* This slave in IR line 2 of master */

    /* ICW4 */
    outb( 0x21,0x05 ); /* Set as master */
    outb( 0xA1,0x01 ); /* Set as slave */


	/*outb(PIC_1_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);	// starts the initialization sequence (in cascade mode)
	outb(PIC_2_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	outb(PIC_1_DATA, offset1);				// ICW2: Master PIC vector offset
	outb(PIC_2_DATA, offset2);				// ICW2: Slave PIC vector offset
	outb(PIC_1_DATA, 4);					// ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC_2_DATA, 2);					// ICW3: tell Slave PIC its cascade identity (0000 0010)

	outb(PIC_1_DATA, PIC_ICW4_8086);
	outb(PIC_2_DATA, PIC_ICW4_8086);*/

        // Setup Interrupt Mask Register (IMR)
	outb(PIC_1_DATA, 0xFd); // 1111 1101 - Enable IRQ 1 only (keyboard).
	outb(PIC_2_DATA, 0xFF);

	asm("sti"); // Enable interrupts.
}


void kernel_main() {
  unsigned char c = 0;
  unsigned short port = 0x60;
  int shift = 0;
  int length = 0;
  char* haha = "";
  pic_remap(0,8);

  int data = inb(0x61);     
  outb(0x61, data & 0x7F);//Enables the keyboard  
  earlyPrintf("\r\n!");
  do
  {
    //c = 1/c;
    //asm("int 0");
    
    
  }while(1); // 1= ESCAPE
}
