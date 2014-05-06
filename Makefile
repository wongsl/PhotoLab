# Makefile: PhotoLab

DEBUG = -g -DDEBUG
CFLAG = -Wall -ansi $(DEBUG) -c
DFLAG = -Wall -ansi -c


all: PhotoLab

clean: 
	rm -f *.o	
	rm -f PhotoLab	

PhotoLab : FileIO.o Advanced.o DIPs.o PhotoLab.o
	gcc -Wall -ansi FileIO.o Advanced.o DIPs.o PhotoLab.o -o PhotoLab

PhotoLab.o: PhotoLab.c Constants.h
	gcc -Wall -ansi -c PhotoLab.c -o PhotoLab.o

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -c FileIO.c -o FileIO.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -Wall -ansi -c Advanced.c -o Advanced.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -c DIPs.c -o DIPs.o	


PhotoLabTest: PhotoLab2

PhotoLab2 : FileIO2.o Advanced2.o DIPs2.o PhotoLab2.o
	gcc -Wall -ansi $(DEBUG) FileIO.o Advanced.o DIPs.o PhotoLab.o -o PhotoLab

PhotoLab2.o: PhotoLab.c Constants.h
	gcc $(CFLAG) PhotoLab.c -o PhotoLab.o

FileIO2.o: FileIO.c FileIO.h Constants.h
	gcc $(CFLAG) FileIO.c -o FileIO.o

Advanced2.o: Advanced.c Advanced.h Constants.h
	gcc $(CFLAG) Advanced.c -o Advanced.o

DIPs2.o: DIPs.c DIPs.h Constants.h
	gcc $(CFLAG) DIPs.c -o DIPs.o	



