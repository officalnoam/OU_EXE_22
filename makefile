mainmat: mainmat.exe

mainmat.exe: mainmat/mymat.o mainmat/mainmat.o mainmat/matlist.o mainmat/matrixoperation.o mainmat/string_utils.o
	gcc -ansi -Wall -pedantic -o mainmat.exe mainmat/mymat.o mainmat/mainmat.o mainmat/matlist.o mainmat/matrixoperation.o mainmat/string_utils.o

mainmat/mainmat.o: mainmat/mainmat.c mainmat/mainmat.h mainmat/mymat.h mainmat/boolean.h mainmat/matlist.h mainmat/matrixoperation.h
	gcc -ansi -Wall -pedantic -c mainmat/mainmat.c -o mainmat/mainmat.o

mainmat/mymat.o: mainmat/mymat.c mainmat/mymat.h
	gcc -ansi -Wall -pedantic -c mainmat/mymat.c -o mainmat/mymat.o

mainmat/matlist.o: mainmat/matlist.c mainmat/matlist.h mainmat/mymat.h
	gcc -ansi -Wall -pedantic -c mainmat/matlist.c -o mainmat/matlist.o

mainmat/matrixoperation.o: mainmat/matrixoperation.c mainmat/matrixoperation.h mainmat/string_utils.h
	gcc -ansi -Wall -pedantic -c mainmat/matrixoperation.c -o mainmat/matrixoperation.o

mainmat/string_utils.o: mainmat/string_utils.c mainmat/string_utils.h mainmat/boolean.h
	gcc -ansi -Wall -pedantic -c mainmat/string_utils.c -o mainmat/string_utils.o

cleanup:
	rm mainmat/*.o
