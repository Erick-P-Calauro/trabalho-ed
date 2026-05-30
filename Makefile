all:
	make dir
	make compile
	make run
	make clean

dir:
	rm -rf ./bin
	mkdir ./bin

compile:
	gcc -c b_split_child.c -I ./ -o ./bin/b_split_child.o
	gcc -c b_insert.c -I ./ -o ./bin/b_insert.o
	gcc -c b_insert_nonfull.c -I ./ -o ./bin/b_insert_nonfull.o
	gcc -c BTree.c -I ./ -o ./bin/BTree.o
	gcc -c Main.c -I ./ -o ./bin/Main.o

run:
	gcc ./bin/Main.o ./bin/BTree.o  ./bin/b_insert_nonfull.o ./bin/b_insert.o ./bin/b_split_child.o -o Main.exe

clean:
	rm -rf ./bin