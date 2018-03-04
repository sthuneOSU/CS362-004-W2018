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

	int i,r;
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
	
	printf("TESTING CARD: EMBARGO\n");
	
	cardEffect(embargo, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	//test coins have increased
	printf("2 coins have been added ... ");
	printf(" (%d+2 = %d) ", G.coins, testG.coins);
	if (asserttrue(G.coins+2, testG.coins, 1))
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
	

	
	printf("Test that victory card piles are correctly modified:");
	for (i = 0; i < 27; i++) {
		initializeGame(numPlayers, k, seed, &G);
		choice1 = i;
		r = cardEffect(embargo, choice1, choice2, choice3, &testG, handpos, &bonus);
		//if pile is not in play, check that -1 is returned
		if (testG.supplyCount[i] == -1) {
			printf("Card %d is not in play, test for -1 return value ... ", i);
			if (asserttrue(r, -1, 1))
				printf("TEST PASSED\n");
			else 
				printf("TEST FAILED\n");
		}
		//otherwise, pile is on play, and check that token is placed
		else {
			printf("Card %d is in play, test for embargo token ... ", i);
			if (asserttrue(G.embargoTokens[i]+1, testG.embargoTokens[i], 1))
				printf("TEST PASSED\n");
			else 
				printf("TEST FAILED\n");			
		}
	}
}


