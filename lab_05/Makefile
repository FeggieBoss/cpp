all: obj/clist.o obj/point_list.o obj/main.o lab_05

obj/clist.o: src/clist.c include/clist.h
	mkdir -p obj
	gcc -c -Wall -Wextra -Werror src/clist.c -o obj/clist.o -I include

obj/point_list.o: src/point_list.c include/point_list.h
	mkdir -p obj
	gcc -c -Wall -Wextra -Werror src/point_list.c -o obj/point_list.o -I include

obj/main.o: src/main.c 
	mkdir -p obj
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include

lab_05: obj/main.o obj/clist.o obj/point_list.o
	gcc obj/main.o obj/clist.o obj/point_list.o -o lab_05

clean:
	rm obj/*.o lab_05
	rmdir obj
