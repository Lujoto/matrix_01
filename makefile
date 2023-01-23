xor: xor.o
	gcc -o xor xor.o -no-pie
xor.o: xor.asm
	nasm -f elf64 -g -F stabs xor.asm -l xor.lst
arg: arg.o
	gcc -o arg arg.o -no-pie
arg.o: arg.asm
	nasm -f elf64 -g -F stabs arg.asm -l arg.lst
mem: mem.o
	gcc -o mem mem.o -no-pie
mem.o: mem.asm
	nasm -f elf64 -g -F stabs mem.asm -l mem.lst
pint: pint.o
	gcc -o pint pint.o -no-pie
pint.o: pint.asm
	nasm -f elf64 -g -F stabs pint.asm -l pint.lst
# Stabs instead of Dwarf lets me break (linenumber), dwarf is defective or something. 
macro: macro.o
	gcc -o macro macro.o -no-pie
macro.o: macro.asm
	nasm -f elf64 -g -F dwarf macro.asm -l macro.lst
test: test.o
	gcc -o test test.o -no-pie
test.o: test.asm
	nasm -f elf64 -g -F dwarf test.asm -l test.lst
string: string.o
	gcc -o string string.o -no-pie
string.o: string.asm
	nasm -f elf64 -g -F dwarf string.asm -l string.lst
digit: digit.o
	gcc -o digit digit.o -no-pie
digit.o: digit.asm
	nasm -f elf64 -g -F dwarf digit.asm -l digit.lst
hello: hello.o
	gcc -o hello hello.o -no-pie
hello.o: hello.asm
	nasm -f elf64 -g -F dwarf hello.asm -l hello.lst
input: input.o
	gcc -o input input.o -no-pie
input.o: input.asm
	nasm -f elf64 -g -F dwarf input.asm -l input.lst
clean: 
	rm input hello hello2 hello2.asm hello2.lst hello2.o input.o hello.o \
		a.exe digit digit.lst digit.o hello.lst macro.lst macro.o string string.lst string.o \
			test.lst test.o test input.lst macro 

