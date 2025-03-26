mainmat: mainmat.exe

mainmat.exe: mainmat/mymat.o mainmat/mainmat.o mainmat/matlist.o
	gcc -ansi -Wall -pedantic -o mainmat.exe mainmat/mymat.o mainmat/mainmat.o mainmat/matlist.o

mainmat/mainmat.o: mainmat/mainmat.c mainmat/mainmat.h mainmat/mymat.h mainmat/boolean.h mainmat/matlist.h
	gcc -ansi -Wall -pedantic -c mainmat/mainmat.c -o mainmat/mainmat.o

mainmat/mymat.o: mainmat/mymat.c mainmat/mymat.h
	gcc -ansi -Wall -pedantic -c mainmat/mymat.c -o mainmat/mymat.o

mainmat/matlist.o: mainmat/matlist.c mainmat/matlist.h mainmat/mymat.h
	gcc -ansi -Wall -pedantic -c mainmat/matlist.c -o mainmat/matlist.o

cleanup:
	rm mainmat/*.o
