mainmat: mainmat.exe

mainmat.exe: mainmat/mymat.o
	gcc -ansi -Wall -pedantic -o mainmat.exe mainmat/mymat.o

mymat.o: mainmat/mymat.h mainmat/mymat.c
	gcc -ansi -Wall -pedantic -c mainmat/mymat.c -o mainmat/mymat.o

cleanup:
	rm mainmat/*.o
