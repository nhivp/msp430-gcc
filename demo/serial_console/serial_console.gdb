target remote localhost:2000
monitor reset
monitor erase
load serial_console.elf
b
disassemble
nexti
disassemble
nexti
info registers
b main
continue