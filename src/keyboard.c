
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




void pic_mask()
{
    // Setup Interrupt Mask Register (IMR)
	outb(0x21, 0xFd); // 1111 1101 - Enable IRQ 1 only (keyboard).
	outb(0xa1, 0xFF);
	asm("sti"); // Enable interrupts.
}


void kernel_main() {

  pic_mask();

  //int data = inb(0x61);     
  //outb(0x61, data & 0x7F);//Enables the keyboard  ?
  earlyPrintf("Is keyboard working?!\r\n");
  do
  {
    //c = 1/c;
    asm("hlt");
    
    
  }while(1); // 1= ESCAPE
}
