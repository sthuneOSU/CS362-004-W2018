#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include "assert.h"
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int toflag;
	int re;
	int pos;
	int i,j;
	int seed = 1000;
	int numPlayer = 2;
	int maxBonus = 10;
	int p, r, handCount;
	int bonus;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxCount = 5;
	// arrays of all coppers, silvers, and golds
	int test_hand[5] = {copper,silver,gold,curse,mine};
	int test_pile[6] = {treasure_map,curse,mine,gold,copper,silver};

	printf ("TESTING run_mine():\n");
	for (p = 0; p < numPlayer; p++)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j <= 2; j++)
			{

#if (NOISY_TEST == 1)
				printf("Test player %d with %d and %d.\n", p, test_hand[i], test_pile[j]);
#endif

				memset(&G, 23, sizeof(struct gameState));   // clear the game state
				r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

				G.handCount[p] = maxCount;
				memcpy(G.hand[p],test_hand,sizeof(int) * maxCount);

				run_mine(&G,p,i,test_pile[j],4);

#if (NOISY_TEST == 1)
				printf("G.handCount = %d, expected = %d\n", G.handCount[p],maxCount-1);

#endif
				assert(G.handCount[p] == maxCount-1);
				
			}        
		}
	}

	printf("All tests passed!\n");

	return 0;
}
