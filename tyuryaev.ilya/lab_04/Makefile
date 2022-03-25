all: obj/clist.o obj/main.o lab_04

obj/clist.o: src/clist.c include/clist.h
	mkdir -p obj
	gcc -c src/clist.c -o obj/clist.o -I include

obj/main.o: src/main.c
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o -I include

lab_04: obj/clist.o obj/main.o
	gcc obj/clist.o obj/main.o -o lab_04

clean:
	rm obj/*.o lab_04
	rmdir obj