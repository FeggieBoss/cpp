all: obj/main.o obj/mergesort.o obj/test.o lab_03 test

obj/main.o: src/main.c 
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o -I include

obj/mergesort.o: src/mergesort.c include/mergesort.h
	mkdir -p obj
	gcc -c src/mergesort.c -o obj/mergesort.o -I include

obj/test.o: src/test.c
	mkdir -p obj
	gcc -c src/test.c -o obj/test.o -I include

test: obj/test.o obj/mergesort.o 
	gcc obj/test.o obj/mergesort.o -o test 

lab_03: obj/main.o obj/mergesort.o
	gcc obj/main.o obj/mergesort.o -o lab_03

clean:
	rm obj/*.o lab_03 test
	rmdir obj
