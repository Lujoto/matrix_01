hello2: hello2.o
	gcc -o hello2 hello2.o -no-pie
hello2.o: hello2.asm
	nasm -f elf64 -g -F dwarf hello2.asm -l hello2.lst
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
	rm input hello hello2 hello2.asm hello2.lst hello2.o input.o hello.o 

