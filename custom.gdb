set confirm off
set verbose off
set disassembly-flavor intel
set disassemble-next-line on
set prompt \033[31mCool Gdb> \033[0m
target remote localhost:1234


define print_regs
  printf "RAX: %016x \nRBX: %016x\n", $rax, $rbx
  printf "RCX: %016x \nRDX: %016x\n", $rcx, $rdx
  printf "RSI: %016x \nRDI: %016x\n", $rsi, $rdi
  printf "RSP: %016x \nRBP: %016x\n", $rsp, $rbp

  echo \33[31mRIP:
  printf " %016x\n", $rip
  echo \033[0m

  printf "\n"
  printf "CS : %04x \nDS : %04x\n", $cs, $ds
  printf "ES : %04x \nSS : %04x\n", $es, $ss
  printf "\n"
  printf "EFLAGS:%016x\n", $eflags 
  printf "cr0 : %016x \ncr4 : %016x\n", $cr0, $cr4
  printf "cr3 : %016x \n", $cr3
  printf "\n"
end

define hook-stop
    print_regs
    x/5i $rip
end


br *0x7c00
c
