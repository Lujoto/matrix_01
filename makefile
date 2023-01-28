%: %.o
	gcc -o $@ $< -no-pie
%.o: %.asm
	nasm -f elf64 -g -F stabs $< 
