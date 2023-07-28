
obj_files = src/keyboard.o \
			src/io.o \
			src/idt.o \
			src/main.o \
			src/vector.o 

CFLAGS=  -static -no-pie -masm=intel 
NASMFLAGS= -f elf64

QEMU_OPTS=-drive format=raw,index=0,if=floppy,file=bootstrap -nographic -monitor /dev/null -display curses # -s S
CC=musl-gcc

bootstrap: kernel boot

	cat boot kernel > bootstrap 
	echo "running system"
	sleep 1
	qemu-system-x86_64 $(QEMU_OPTS)
	#qemu-system-i386 $(QEMU_OPTS)
clean:
	rm src/*.o kernel boot bootstrap 

debug:
	gdb -ix "custom.gdb" -ex "b *0x902a"
debug32:
	gdb -ix "custom32.gdb" -ex "b *0x9000"



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<  $(CFLAGS)

%.o: %.asm $(DEPS)
	nasm -o $@ $< $(NASMFLAGS)

kernel: $(obj_files) 
	$(CC) -o kernel $^ --entry=main --static -T script.ld 
	echo "Kernel build done"

boot:
	nasm -f bin src/boot.asm -o boot

