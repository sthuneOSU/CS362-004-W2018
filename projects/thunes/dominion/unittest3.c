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

	//int r, i;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int handpos = 0;
	initializeGame(numPlayer, k, seed, &G);
			
	G.phase = 1; //wrong phase
	G.numActions = 0; //not enough actions
	G.hand[0][0] = 40; //invalid card
	int choice1 = 0; //invalid choice, to be used with valid card
	
	printf("invalid phase causes return value -1 ... ");
	if (asserttrue(playCard(handpos,choice1,0,0,&G), -1, 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	
	G.phase = 0; //fix phase
	printf("not enough actions causes return value -1 ... ");
	if (asserttrue(playCard(handpos,choice1,0,0,&G), -1, 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	
	G.numActions = 4; //fix actions
	printf("invalid card ID causes return value -1 ... ");
	if (asserttrue(playCard(handpos,choice1,0,0,&G), -1, 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	
	G.hand[0][0] = ambassador; //fix card, choice1 = handPos returns -1
	printf("invalid choice1 on ambassador causes return value -1 ... ");
	if (asserttrue(playCard(handpos,choice1,0,0,&G), -1, 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	
	choice1 = 1; //fix choice1;
	int numActionsOld = G.numActions;	//used for comparison
	//playCard(handpos,choice1,0,0,&G), -1, 1);
	printf("run function correctly, check return value is 0 ... ");
	if (asserttrue(playCard(handpos,choice1,0,0,&G), 0, 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");
	printf("run function correctly, check that actions is reduced by 1 ...");
	printf(" (%d-1 = %d) ", numActionsOld, G.numActions);
	if (asserttrue(numActionsOld-1, G.numActions, 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");	
	
	
	return 0;
	
}
