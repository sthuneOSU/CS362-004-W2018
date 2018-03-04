#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"
#define TEST_ITERATIONS 2000;

int main() {

	int i,j,n;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	srand(time(NULL));
    
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	int iters = TEST_ITERATIONS;
	int dSize = 0;
	int failFlag = 0;
	int numRuns, currentPlayer;

	
	for (i=0; i < iters; i++) {
		
		int numPlayers = rand()%3 + 2; //2-4 players;
		int seed = rand();
		initializeGame(numPlayers, k, seed, &G);
		
		G.whoseTurn = currentPlayer;
		//draw cards to all hands
		for (n = 1; n < numPlayers; n++) {
			for (j = 0; j < 5; j++)
				drawCard(n, &G);
		}
		
		numRuns = rand()%4 + 1; //need 6 cards to be drawn, forcing a shuffle
		for (n = 0; n < numRuns; n++) {
			memcpy(&testG, &G, sizeof(struct gameState)); //set testG = G
			dSize = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
			currentPlayer = rand()%numPlayers;
			
			//check hands
			for (j = 0; j < numPlayers; j++) {
				if (j == currentPlayer) {
					if (G.handCount[currentPlayer]+2 != testG.handCount[currentPlayer] ) {
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
					if (G.deckCount[j] - (dSize+2) != testG.deckCount[j]) {
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
					if (G.discardCount[j] + dSize != testG.discardCount[j]) {
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
			memcpy(&G, &testG, sizeof(struct gameState)); //copy G to testG for next run
		}
	}
	if (!failFlag)
		printf("\n ALL TESTS PASSED!\n");
	return 0;
}


