


RISCVGNU = riscv32-unknown-elf

AOPS = -march=rv32imac
#AOPS = -march=rv32imac -mabi=ilp32
COPS = -march=rv32imac -Wall -O2 -nostdlib -nostartfiles -ffreestanding 
#COPS = -march=rv32imac -mabi=ilp32 -Wall -O2 -nostdlib -nostartfiles -ffreestanding 


all : notmain.bin

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.bin
	rm -f *.list

novectors.o : novectors.s
	$(RISCVGNU)-as $(AOPS) novectors.s -o novectors.o

notmain.o : notmain.c
	$(RISCVGNU)-gcc $(COPS) -c notmain.c -o notmain.o

notmain.bin : memmap novectors.o notmain.o 
	#$(RISCVGNU)-ld  -m elf32lriscv novectors.o notmain.o -T memmap -o notmain.elf
	$(RISCVGNU)-ld novectors.o notmain.o -T memmap -o notmain.elf
	#$(RISCVGNU)-gcc $(COPS) -Xlinker -T -Xlinker memmap novectors.o notmain.o world.o libgcc.a -o notmain.elf
	$(RISCVGNU)-objdump -D notmain.elf > notmain.list
	#$(RISCVGNU)-objcopy notmain.elf -O ihex notmain.hex 
	$(RISCVGNU)-objcopy notmain.elf -O binary notmain.bin 






