#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "smithy"
#define TEST_ITERATIONS 2000;

int main() {

	int i,j,n;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	srand(time(NULL));
    
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	int iters = TEST_ITERATIONS;
	int failFlag = 0;

	
	for (i=0; i < iters; i++) {
		
		int numPlayers = rand()%3 + 2; //2-4 players;
		int seed = rand();
		initializeGame(numPlayers, k, seed, &G);
		int currentPlayer = rand()%numPlayers;
		G.whoseTurn = currentPlayer;
		//draw cards for everyone
		for (n = 1; n < numPlayers; n++) {
			for (j = 0; j < 5; j++)
				drawCard(n, &G);
		}
		//G.hand[currentPlayer][0] = smithy;
		
		memcpy(&testG, &G, sizeof(struct gameState)); //set testG = G
		cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
		
		/*//check current player's hand/deck/discard counts before and after card is played
		printf("currentPlayer is %d of %d ", currentPlayer, numPlayers);
		printf("<%d %d> ",G.handCount[currentPlayer], testG.handCount[currentPlayer]);
		printf("<%d %d> ",G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
		printf("<%d %d>\n",G.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
		*///test me
		
		//check hands
		for (j = 0; j < numPlayers; j++) {
			if (j == currentPlayer) {
				if (G.handCount[currentPlayer] + 2 != testG.handCount[currentPlayer] ) {
					printf("iter%d: currentPlayer hand...FAIL ",i);
					failFlag = 1;
				}	
			}
			else {
				if (G.handCount[j] != testG.handCount[j]) {
					printf("iter%d player%d: hand...FAIL ",i,j);
					failFlag = 1;
				}
			}
		}
		//check decks
		for (j = 0; j < numPlayers; j++) {
			if (j == currentPlayer) {
				if (G.deckCount[j] - 3 != testG.deckCount[j]) {
					printf("iter%d: currentPlayer deck...FAIL ",i);
					failFlag = 1;
				}
			}
			else {
				if (G.deckCount[j] != testG.deckCount[j]) {
					printf("iter%d player%d: deck...FAIL ",i,j);
					failFlag = 1;
				}
			}
		}
		//check discard piles
		for (j = 0; j < numPlayers; j++) {
			if (j == currentPlayer) {
				if (G.discardCount[j] != testG.discardCount[j]) {
					printf("iter%d: currentPlayer discard...FAIL ",i);
					failFlag = 1;
				}
			}
			else {
				if (G.discardCount[j] != testG.discardCount[j]) {
					printf("iter%d player%d: discard...FAIL ",i,j);
					failFlag = 1;
				}
			}
		}
		//check victory cards
		for (j = 0; j < 27; j++) {
			if (G.supplyCount[j] != testG.supplyCount[j]) {
				printf("iter%d pile%d: victory card...FAIL ",i,j);
				failFlag = 1;
			}
		}
	}
	if (!failFlag)
		printf("\n ALL TESTS PASSED!\n");
	return 0;
}


