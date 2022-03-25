all: obj/bmp.o obj/main.o obj/stego.o hw_01

obj/bmp.o: src/bmp.c include/bmp.h 
	mkdir -p obj
	gcc -c -Wall -Wextra -Werror src/bmp.c -o obj/bmp.o -I include

obj/main.o: src/main.c
	mkdir -p obj
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include

obj/stego.o: src/stego.c include/stego.h 
	mkdir -p obj
	gcc -c -Wall -Wextra -Werror src/stego.c -o obj/stego.o -I include

hw_01: obj/bmp.o obj/main.o obj/stego.o
	gcc obj/bmp.o obj/main.o obj/stego.o -o hw_01

clean:
	rm obj/*.o hw_01
	rmdir obj