#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include "assert.h"
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int flag,played;
	int re;
	int pos;
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int maxBonus = 10;
	int p, r, handCount,deckCount,discardCount;
	int bonus;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxCount = 10;
	// arrays of all coppers, silvers, and golds
	int coppers[maxCount];
	for (i = 0; i < maxCount; i++) coppers[i] = copper;

	printf ("TESTING fullDeckCount():\n");
	for (p = 0; p < numPlayer; p++)
	{
#if (NOISY_TEST == 1)
		printf("Test player %d with %d handCount and %d deckCount and %d discardCount.\n", p, maxCount, maxCount, maxCount);
#endif

		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p], coppers, sizeof(int) * maxCount);
		memcpy(G.deck[p], coppers, sizeof(int) * maxCount);
		memcpy(G.discard[p], coppers, sizeof(int) * maxCount);

		re = fullDeckCount(p,copper,&G);

#if (NOISY_TEST == 1)
		printf("count = %d, expected = %d\n", re, 3* maxCount);
#endif
		assert(re == 3 * maxCount);

#if (NOISY_TEST == 1)
		printf("Test player %d with %d handCount and %d deckCount and %d discardCount.\n", p, 0, 0, 0);
#endif
		G.handCount[p] = 0;
		G.deckCount[p] = 0;
		G.discardCount[p] = 0;
		memcpy(G.hand[p], coppers, sizeof(int) * 0);
		memcpy(G.deck[p], coppers, sizeof(int) * 0);
		memcpy(G.discard[p], coppers, sizeof(int) * 0);

		re = fullDeckCount(p,copper,&G);

#if (NOISY_TEST == 1)
		printf("count = %d, expected = %d\n", re, 0);
#endif
		assert(re == 0);

	}
	printf("All tests passed!\n");

	return 0;
}
