
all:
	nasm -f bin boot.asm 
	#gcc -Wl,--oformat=binary -Wl,-Ttext-segment,0x9000 -o main main.c -s  -nolibc -nostdlib -Os -static -pie --entry=main -masm=intel
	gcc -c main.c -s  -nostdlib -Os -static -no-pie --entry=main -masm=intel
	ld -o main main.o --entry=main --script=script.ld
	cat boot main > bootstrap
	#xxd bootstrap
	sleep 5

	qemu-system-x86_64 -drive format=raw,index=0,if=floppy,file=bootstrap -nographic -monitor /dev/null -s 
	
	#qemu-system-i386 -drive format=raw,index=0,if=floppy,file=bootstrap -nographic -monitor /dev/null -s -S

debug:
	gdb -ix "custom.gdb" -ex "b *0x902a"
debug32:
	gdb -ix "custom32.gdb" -ex "b *0x9000"
