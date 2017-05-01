all: index

index : index.o skiplist.o
	g++ -o index -g index.o skiplist.o

skiplist.o : skiplist.cc skiplist.h
	g++ -Wall -c -g skiplist.cc

index.o : index.cc skiplist.h
	g++ -Wall -c -g index.cc

clean :
	rm *.o
	rm index
