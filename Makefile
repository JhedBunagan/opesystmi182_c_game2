all:
	gcc -Wall -ansi Tiktik.c -Iinclude -o Tiktik -lncurses

clean:
	rm Tiktik
