CPPFLAGS = -Wall -O3 -std=c++11 -w -lm

main: main.o cusketch.o cmsketch.o cmlsketch.o csketch.o BOBHash.o \
	cmsketch_nonconflict.o cmlsketch_nonconflict.o cusketch_nonconflict.o csketch_nonconflict.o \
	pfsketch_cu.o pfsketch.o cusketch_plus.o cbsketch_origin.o onememcb.o support.o md5.o \
	cusketch_offchip.o cusketch_offchip_update.o
	g++ -o main main.o cusketch.o cmsketch.o cmlsketch.o csketch.o BOBHash.o \
	cmsketch_nonconflict.o cmlsketch_nonconflict.o cusketch_nonconflict.o csketch_nonconflict.o	\
	pfsketch_cu.o pfsketch.o cusketch_plus.o cbsketch_origin.o onememcb.o support.o md5.o \
	cusketch_offchip.o cusketch_offchip_update.o $(CPPFLAGS)


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

pfsketch.o: pfsketch.cpp pfsketch.h BOBHash.h params.h
	g++ -c pfsketch.cpp $(CPPFLAGS)

cusketch_plus.o: cusketch_plus.cpp cusketch_plus.h BOBHash.h params.h
	g++ -c cusketch_plus.cpp $(CPPFLAGS)

cusketch_offchip.o: cusketch_offchip.cpp cusketch_offchip.h BOBHash.h params.h
	g++ -c cusketch_offchip.cpp $(CPPFLAGS)

cusketch_offchip_update.o: cusketch_offchip_update.cpp cusketch_offchip_update.h BOBHash.h params.h
	g++ -c cusketch_offchip_update.cpp $(CPPFLAGS)

cbsketch_origin.o:	cbsketch_origin.cpp cbsketch_origin.h support.h support.o params.h
	g++ -c cbsketch_origin.cpp $(CPPFLAGS)

onememcb.o:	onememcb.cpp onememcb.h support.h support.o params.h
	g++ -c onememcb.cpp $(CPPFLAGS)

support.o: support.cpp support.h md5.h
	g++ -c support.cpp $(CPPFLAGS)

md5.o: md5.cpp md5.h
	g++ -c md5.cpp $(CPPFLAGS)

BOBHash.o: BOBHash.cpp BOBHash.h params.h
	g++ -c BOBHash.cpp $(CPPFLAGS)

clean:
	rm -f *.o main