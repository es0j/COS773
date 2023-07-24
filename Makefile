
all:
	nasm -f bin boot.asm 

	nasm -f elf64 vector.asm
	gcc -c main.c keyboard.c -nostdlib -Os -static -no-pie --entry=main -masm=intel
	ld -o main main.o vector.o keyboard.o --entry=main --script=script.ld


	cat boot main > bootstrap
	sleep 1
	qemu-system-x86_64 -drive format=raw,index=0,if=floppy,file=bootstrap -nographic -monitor /dev/null -s   
	
	#qemu-system-i386 -drive format=raw,index=0,if=floppy,file=bootstrap -nographic -monitor /dev/null -s -S

debug:
	gdb -ix "custom.gdb" -ex "b *0x902a"
debug32:
	gdb -ix "custom32.gdb" -ex "b *0x9000"
