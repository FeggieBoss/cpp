all: obj/str.o obj/test_str.o obj/test.o lab_02

obj/str.o: src/str.c include/str.h
	mkdir -p obj
	gcc -c src/str.c -o obj/str.o -I include

obj/test_str.o: src/test_str.c include/test_str.h 
	mkdir -p obj
	gcc -c src/test_str.c -o obj/test_str.o -I include 

obj/test.o: src/test.c
	mkdir -p obj
	gcc -c src/test.c -o obj/test.o -I include

lab_02: obj/str.o obj/test_str.o obj/test.o
	gcc obj/str.o obj/test_str.o obj/test.o -o lab_02 -I include

clean:
	rm obj/*.o lab_02 
	rmdir obj
