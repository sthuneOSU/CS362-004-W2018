/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
//This file tests the isgameOver() function (line 390 in dominion.c)
 
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
	int r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    // arrays of all coppers, silvers, and golds
    //int coppers[MAX_HAND];
    //int silvers[MAX_HAND];
    //int golds[MAX_HAND];
	
/*
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
*/
	r = initializeGame(numPlayer, k, seed, &G);
	G.supplyCount[province] = 3;
	//test for game over with positive province cards remaining
	while (G.supplyCount[province] > 0) {
		printf("testing %d province cards remaining ... ", G.supplyCount[province]);
		if (asserttrue(0, isGameOver(&G), 1))
			printf("TEST PASSED\n");
		else 
			printf("TEST FAILED\n");
		G.supplyCount[province] --;
	}
	//test when no more province cards
	printf("testing %d province cards remaining ... ", G.supplyCount[province]);
	if (asserttrue(1, isGameOver(&G), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");
	
	r = initializeGame(numPlayer, k, seed, &G);
	printf("testing 0 empty supply piles ... ", G.supplyCount[province]);
	if (asserttrue(0, isGameOver(&G), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");
	//2 empty supply pile
	r = initializeGame(numPlayer, k, seed, &G);
	G.supplyCount[curse] = 0;
	G.supplyCount[estate] = 0;
	printf("testing 2 empty supply piles ... ", G.supplyCount[province]);
	if (asserttrue(0, isGameOver(&G), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");
	r = initializeGame(numPlayer, k, seed, &G);
	G.supplyCount[curse] = 0;
	G.supplyCount[estate] = 0;
	G.supplyCount[duchy] = 0;
	printf("testing 3 empty supply piles (curse, estate, duchy)... ", G.supplyCount[province]);
	if (asserttrue(1, isGameOver(&G), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");
	r = initializeGame(numPlayer, k, seed, &G);
	G.supplyCount[copper] = 0;
	G.supplyCount[baron] = 0;
	G.supplyCount[salvager] = 0;
	printf("testing 3 empty supply piles (copper, baron, salvager) ... ", G.supplyCount[province]);
	if (asserttrue(1, isGameOver(&G), 1))
		printf("TEST PASSED\n");
	else 
		printf("TEST FAILED\n");
	
	/*
    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
                assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
                assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
                assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
            }
        }
    }
	*/

    return 0;
}
