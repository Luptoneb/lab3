CC=gcc

CFLAGS= -g -O1

arrayList: main.o arrayList.o

arrayList.o: arrayList.h

main.o: arrayList.o

clean:
	rm -f *.o
