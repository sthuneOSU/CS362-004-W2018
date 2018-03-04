CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

unitest1: unitest1.c dominion.o rngs.o
	gcc -o unitest1 -g  unitest1.c dominion.o rngs.o $(CFLAGS)

unitest2: unitest2.c dominion.o rngs.o
	gcc -o unitest2 -g  unitest2.c dominion.o rngs.o $(CFLAGS)

unitest3: unitest3.c dominion.o rngs.o
	gcc -o unitest3 -g  unitest3.c dominion.o rngs.o $(CFLAGS)

unitest4: unitest4.c dominion.o rngs.o
	gcc -o unitest4 -g  unitest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

rununi: unitest1 unitest2 unitest3 unitest4 cardtest1 cardtest2 cardtest3 cardtest4

testAdventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o testAdventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
testSmithy: randomtestcard1.c dominion.o rngs.o
	gcc -o testSmithy -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
testMine: randomtestcard2.c dominion.o rngs.o
	gcc -o testMine -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

testrand1: testAdventurer
	./testAdventurer &> randomtestadventurer.out
	gcov randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

testrand2: testSmithy
	./testSmithy &> randomtestcard1.out
	gcov randomtestcard1.c >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

testrand3: testMine
	./testMine &> randomtestcard2.out
	gcov randomtestcard2.c >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

all: playdom player testDrawCard testBuyCard badTestDrawCard testUpdateCoins

clean: cleanrand cleanuni cleancard
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testUpdateCoins testUpdateCoins.exe

cleanrand: 
	rm -f testAdventurer testAdventurer.exe testSmithy testSmithy.exe testMine testMine.exe

cleanuni: 
	rm -f unitest1 unitest1.exe unitest2 unitest2.exe unitest3 unitest3.exe unitest4 unitest4.exe

cleancard:
	rm -f cardtest1 cardtest2.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe
