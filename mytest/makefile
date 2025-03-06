


make : mytest.riscv
	@echo "make done"

mytest.o:mytest.c
	riscv64-unknown-elf-gcc -O2 -fno-common -fno-builtin-printf -specs=htif.specs -c mytest.c
mytest.riscv:mytest.o
	riscv64-unknown-elf-gcc  -O2 -static -specs=htif_nano.specs mytest.o -o mytest.riscv
	rm mytest.o
	riscv64-unknown-elf-objdump -d mytest.riscv > mytest.dump 
