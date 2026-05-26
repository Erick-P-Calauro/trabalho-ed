all:
	make dir
	make compile
	make run
	make clean

dir:
	rm -rf ./bin
	mkdir ./bin

compile:
	gcc -c BTree.c -I ./ -o ./bin/BTree.o
	gcc -c Main.c -I ./ -o ./bin/Main.o

run:
	gcc ./bin/Main.o ./bin/BTree.o -o Main.exe

clean:
	rm -rf ./bin