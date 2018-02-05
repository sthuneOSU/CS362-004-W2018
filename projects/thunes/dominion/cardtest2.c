/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

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
    //int newCards = 0;
    //int discarded = 1;
    //int xtraCoins = 0;
    //int shuffledCards = 0;

    //int i, j, m;

	int i,j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    //int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("TESTING CARD: ADVENTURER\n");
	
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	//test currentPlayer hand has increased by 2
	printf("player 0 hand size has increased ... ");
	printf(" (%d < %d) ",G.handCount[0], (testG.handCount[0]));
	if (asserttrue(G.handCount[0], (testG.handCount[0]), 3))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	//test currentPlayer deck has decreased
	printf("player 0 deck size has decreased ... ");
	printf(" (%d > %d) ",G.deckCount[0], testG.deckCount[0]);
	if (asserttrue(G.deckCount[0], (testG.deckCount[0]), 5))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");
	//test currentPlayer discard has increased
	printf("player 0 has more cards in discard pile ... ");
	printf(" (%d < %d) ",G.discardCount[0], testG.discardCount[0]);
	if (asserttrue(G.discardCount[0], (testG.discardCount[0]), 3))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	//test p1 has unchanged hand count
	printf("player 1 has unchanged hand count ... ");
	printf(" (%d = %d) ",G.handCount[1], (testG.handCount[1]));
	if (asserttrue(G.handCount[1], (testG.handCount[1]), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");			
	//test p1 has unchanged deck count
	printf("player 1 has unchanged deck count ... ");
	printf(" (%d = %d) ",G.deckCount[1], (testG.deckCount[1]));
	if (asserttrue(G.deckCount[1], (testG.deckCount[1]), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	//test p1 discard unchanged
	printf("player 1 has unchanged discard pile ... ");
	printf(" (%d = %d) ",G.discardCount[1], testG.discardCount[1]);
	if (asserttrue(G.discardCount[1], (testG.discardCount[1]), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");		
	
	j = 0;
	printf("Test that victory card piles are unchanged ... ");
	for (i = 0; i < 27; i++) {
		if (asserttrue(G.supplyCount[i], testG.supplyCount[i], 2)) {//if not equal, failure
			printf("TEST FAILED\n");
			j = 1;
		}
	}
	if (j == 0) 
		printf("TEST PASSED\n");

	return 0;
}


