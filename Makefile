CPPFLAGS = -Wall -O3 -std=c++11 -w -lm

main: main.o cusketch.o cmsketch.o cmlsketch.o csketch.o BOBHash.o
	g++ -o main main.o cusketch.o cmsketch.o cmlsketch.o csketch.o BOBHash.o $(CPPFLAGS)

main.o: main.cpp cusketch.h cmsketch.h cmlsketch.h csketch.h BOBHash.h
	g++ -c main.cpp $(CPPFLAGS) 

cusketch.o:	cusketch.cpp cusketch.h BOBHash.h
	g++ -c cusketch.cpp $(CPPFLAGS)

cmsketch.o: cmsketch.cpp cmsketch.h BOBHash.h
	g++ -c cmsketch.cpp $(CPPFLAGS)

cmlsketch.o: cmlsketch.cpp cmlsketch.h BOBHash.h
	g++ -c cmlsketch.cpp $(CPPFLAGS)

csketch.o: csketch.cpp csketch.h BOBHash.h
	g++ -c csketch.cpp $(CPPFLAGS)

BOBHash.o: BOBHash.cpp BOBHash.h
	g++ -c BOBHash.cpp $(CPPFLAGS)

clean:
	rm -f *.o