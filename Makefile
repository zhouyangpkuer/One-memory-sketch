CPPFLAGS = -Wall -O2 -std=c++11 -w -lm

main: main.o cusketch.o cmsketch.o cmlsketch.o csketch.o BOBHash.o \
	cmsketch_nonconflict.o cmlsketch_nonconflict.o cusketch_nonconflict.o csketch_nonconflict.o \
	pfsketch_cu.o
	g++ -o main main.o cusketch.o cmsketch.o cmlsketch.o csketch.o BOBHash.o \
	cmsketch_nonconflict.o cmlsketch_nonconflict.o cusketch_nonconflict.o csketch_nonconflict.o	\
	pfsketch_cu.o $(CPPFLAGS)

main.o: main.cpp cusketch.h cmsketch.h cmlsketch.h csketch.h BOBHash.h params.h
	g++ -c main.cpp $(CPPFLAGS) 

cusketch.o:	cusketch.cpp cusketch.h BOBHash.h params.h
	g++ -c cusketch.cpp $(CPPFLAGS)

cmsketch.o: cmsketch.cpp cmsketch.h BOBHash.h params.h
	g++ -c cmsketch.cpp $(CPPFLAGS)

cmlsketch.o: cmlsketch.cpp cmlsketch.h BOBHash.h params.h
	g++ -c cmlsketch.cpp $(CPPFLAGS)

csketch.o: csketch.cpp csketch.h BOBHash.h params.h
	g++ -c csketch.cpp $(CPPFLAGS)

cusketch_nonconflict.o:	cusketch_nonconflict.cpp cusketch_nonconflict.h BOBHash.h params.h
	g++ -c cusketch_nonconflict.cpp $(CPPFLAGS)

cmsketch_nonconflict.o: cmsketch_nonconflict.cpp cmsketch_nonconflict.h BOBHash.h params.h
	g++ -c cmsketch_nonconflict.cpp $(CPPFLAGS)

cmlsketch_nonconflict.o: cmlsketch_nonconflict.cpp cmlsketch_nonconflict.h BOBHash.h params.h
	g++ -c cmlsketch_nonconflict.cpp $(CPPFLAGS)

csketch_nonconflict.o: csketch_nonconflict.cpp csketch_nonconflict.h BOBHash.h params.h
	g++ -c csketch_nonconflict.cpp $(CPPFLAGS)

pfsketch_cu.o: pfsketch_cu.cpp pfsketch_cu.h BOBHash.h params.h
	g++ -c pfsketch_cu.cpp $(CPPFLAGS)
	
BOBHash.o: BOBHash.cpp BOBHash.h params.h
	g++ -c BOBHash.cpp $(CPPFLAGS)

clean:
	rm -f *.o main