all: gauss

myint.o: myint.cpp
	g++ myint.cpp -c -o myint.o
gauss.o: gauss.cpp
	g++ gauss.cpp -c -o gauss.o

gauss: gauss.o myint.o
	g++ gauss.o myint.o -o gauss

clean:
	rm gauss *.o
