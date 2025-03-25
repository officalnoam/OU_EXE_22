mainmat: mainmat.exe

mainmat.exe: mainmat/mymat.o mainmat/mainmat.o
	gcc -ansi -Wall -pedantic -o mainmat.exe mainmat/mymat.o mainmat/mainmat.o

mainmat.o: mainmat/mainmat.c mainmat/mainmat.h mainmat/mymat.h mainmat/boolean.h
	gcc -ansi -Wall -pedantic -c mainmat/mainmat.c -o mainmat/mainmat.o

mymat.o: mainmat/mymat.c mainmat/mymat.h
	gcc -ansi -Wall -pedantic -c mainmat/mymat.c -o mainmat/mymat.o

cleanup:
	rm mainmat/*.o
