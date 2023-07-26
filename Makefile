
all:
	nasm -f bin src/boot.asm -o build/boot
	nasm -f elf64 src/vector.asm -o build/vector.o
	gcc -c src/main.c -o build/main.o -nostdlib -Os -static -no-pie --entry=main -masm=intel 
	gcc -c src/keyboard.c -o build/keyboard.o -nostdlib -Os -static -no-pie --entry=main -masm=intel 
	
	ld -o build/main build/main.o build/vector.o build/keyboard.o --entry=main --script=script.ld


	cat build/boot build/main > build/bootstrap
	sleep 1
	qemu-system-x86_64 -drive format=raw,index=0,if=floppy,file=build/bootstrap -nographic -monitor /dev/null    -display curses
	
	#qemu-system-i386 -drive format=raw,index=0,if=floppy,file=build/bootstrap -nographic -monitor /dev/null -s -S
clean:
	rm *.o

debug:
	gdb -ix "custom.gdb" -ex "b *0x902a"
debug32:
	gdb -ix "custom32.gdb" -ex "b *0x9000"
