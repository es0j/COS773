#include "config.h"

#define LINE_SIZE 1024


char kbdus[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '+', '\b',   /* Backspace */
    '\t',           /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',       /* Enter key */
    0,          /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   /* 39 */
    '\'', '`',   0,     /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',         /* 49 */
    'm', ',', '.', '/',   0,                    /* Right shift */
    '*',
    0,  /* Alt */
    ' ',    /* Space bar */
    0,  /* Caps lock */
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
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

char lchar;
char line[LINE_SIZE];
void keyboardISR(){


 
  unsigned char scancode=inb(PS2_DATA_PORT);
  if(!(scancode & 0x80)) {
    // Key pressed
    //earlyPrintf("keyboard pressed: ");
    
    lchar=kbdus[scancode];
    if(lchar=='\n'){
      earlyPutch('\r');
    }
    earlyPutch(lchar);
    //earlyPrintf("\r\n");
  }
  outb(PIC1_CTRL,PIC1_END_OF_INTERRUPTION);

}


char getch(){
  lchar=0;
  while(lchar==0){
    asm("hlt");
  }
  return lchar;
}

char* getLine(){
  char d;
  for(int i=0;i<LINE_SIZE;i++){
    d = getch();
    if(d=='\n'){
      line[i]=0;
      break;
    }
    line[i]=d;
  }
  return line;
}

