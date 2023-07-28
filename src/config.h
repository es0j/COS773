#ifndef _CONFIG_H 
#define _CONFIG_H

#define PS2_DATA_PORT 0x60

#define PIC1_CTRL 0x20
#define PIC1_DATA 0x21

#define PIC2_CTRL 0xa0
#define PIC2_DATA 0xa1

#define SERIAL_PORT 0x3f8

#define PIC1_END_OF_INTERRUPTION 0x20

#define CLEAR_SCREEN "\x1b[2J\x1B[H\n\r"




void outb( unsigned short port, unsigned char val );
unsigned char inb (unsigned short int port);
int earlyPutch(char inputchar);
int earlyPrintf(char *s);

char getch();
char* getLine();

void enableInterrupt();
void disableInterrupt();
void keyboardISR();

void init_idt();
void picRemap();


void isr_wrapper_keyboard();
void isr_wrapper();




#endif