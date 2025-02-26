


make : bfs.riscv
	@echo "make done"

bfs.o:bfs.c
	riscv64-unknown-elf-gcc -O2 -fno-common -fno-builtin-printf -specs=htif.specs -c bfs.c
bfs.riscv:bfs.o
	riscv64-unknown-elf-gcc  -O2 -static -specs=htif_nano.specs bfs.o -o bfs.riscv
	rm bfs.o
	riscv64-unknown-elf-objdump -d bfs.riscv > bfs.dump 