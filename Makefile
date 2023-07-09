
all:
	nasm -f bin boot.asm 
	qemu-system-x86_64 -drive format=raw,index=0,if=floppy,file=boot -nographic -monitor /dev/null -s -S
	#qemu-system-i386 -drive format=raw,index=0,if=floppy,file=boot -nographic -monitor /dev/null -s -S


debug:
	gdb -ix "custom.gdb" -ex "b *0x7c68"
