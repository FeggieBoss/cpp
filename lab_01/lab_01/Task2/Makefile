all: bin/util.o bin/algorithm.o bin/io.o bin/main.o main
bin/util.o: src/util.c include/util.h
	gcc -c src/util.c -o bin/util.o
bin/algorithm.o: src/algorithm.c include/algo.h
	gcc -c src/algorithm.c -o bin/algorithm.o
bin/io.o: src/io.c include/io.h
	gcc -c src/io.c -o bin/io.o
bin/main.o: src/main.c
	gcc -c src/main.c -o bin/main.o
main: bin/util.o bin/algorithm.o bin/io.o bin/main.o
	gcc bin/util.o bin/algorithm.o bin/io.o bin/main.o -o lab1
clean: 
	rm bin/*.o lab1