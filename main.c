
char *helloStr="\r\nHello world from C!\r\n\0";







#define INT_DISABLE 0
#define INT_ENABLE  0x200
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01




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
    while(*s++!='\0'){
        earlyPutch(*s);
    }
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

void init_pics(int pic1, int pic2)
{
   /* send ICW1 */
   outb(PIC1, ICW1);
   outb(PIC2, ICW1);

   /* send ICW2 */
   outb(PIC1 + 1, pic1);   
   outb(PIC2 + 1, pic2);   

   /* send ICW3 */
   outb(PIC1 + 1, 4);   
   outb(PIC2 + 1, 2);

   /* send ICW4 */
   outb(PIC1 + 1, ICW4);
   outb(PIC2 + 1, ICW4);

   /* disable all IRQs */
   outb(PIC1 + 1, 0xFF);
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

void kernel_main() {
  unsigned char c = 0;
  unsigned short port = 0x60;
  int shift = 0;
  int length = 0;
  char* haha = "";
  //init_pics();
  //asm("sti");
  outb(0x61, 0x7F);//Enables the keyboard  
  earlyPrintf("\r\n!");
  do
  {
    c = inb(port);
    if (inb(port) != c) //PORT FROM WHICH WE READ
    {

      earlyPutch(kbd_US[c]);
      earlyPutch('!');
    }
  }while(kbd_US[c] != -2); // 1= ESCAPE
}



int readKeyboard(){

}


int main(){
    asm("mov rsp,0x1000000\n");
    asm("mov rbp,rsp       \n");
    earlyPrintf(helloStr);
    kernel_main();
}




















