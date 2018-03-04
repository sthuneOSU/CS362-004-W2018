/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
//tests fullDeckCount() function
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int asserttrue(int a, int b, int logic) {
	
	switch(logic) {
		case 1:
			if (a == b) 
				return 1; 
			break;
		case 2:
			if (a != b) 
				return 1; 
			break;
		case 3:
			if (a < b)  
				return 1; 
			break;
		case 4:
			if (a <= b) 
				return 1; 
			break;
		case 5:
			if (a > b)  
				return 1; 
			break;
		case 6:
			if (a >= b) 
				return 1; 
			break;
	}
	return 0;
}

int main() {

	int r, i;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	r = initializeGame(numPlayer, k, seed, &G);
			
	G.discardCount[0] = 5;
	//fill hand, deck, discard with estates
	for (i = 0; i < 3; i++) {
		G.deck[0][i] = 1;
		G.hand[0][i] = 1;
		G.discard[0][i] = 1;
	}
		
	for (i = 2; i >= 0; i--) {
		printf("Checking hand,deck,discard size %d ... ",i);
		//reduce hand size
		G.handCount[0] = i;
		G.deckCount[0] = i;
		G.discardCount[0] = i;
		
		//test for matching card, fullDeckCount() should return 6,3,0
		printf("matching cards ... ");
		printf("(%d = %d) ",(3*i) ,fullDeckCount(0,1,&G));
		if (asserttrue((3*i), fullDeckCount(0,1,&G), 1))
			printf("TEST PASSED\n");
		else 
			printf("TEST FAILED\n");
		
		//test no matching cards, should return 0,0,0
		printf("\t\t\t       ... no matching cards ... ");
		printf("(%d = %d) ",0 ,fullDeckCount(0,6,&G));
		if (asserttrue(0, fullDeckCount(0,6,&G), 1))
			printf("TEST PASSED\n");
		else 
			printf("TEST FAILED\n");
	}
	return 0;
}
