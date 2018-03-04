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
	int Curses[maxCount];
	int Estates[maxCount];
	int Duchys[maxCount];
	int Provinces[maxCount];
	int Great_halls[maxCount];
	int Gardens[maxCount];

	for(i = 0;i < maxCount;i++){
		Curses[i] = curse;
		Estates[i] = estate;
		Duchys[i] = duchy;		
		Provinces[i] = province;
		Great_halls[i] = great_hall;
		Gardens[i] = gardens;
	}

	printf ("TESTING scoreFor():\n");
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
		memcpy(G.hand[p], Curses, sizeof(int) * maxCount);
		memcpy(G.deck[p], Curses, sizeof(int) * maxCount);
		memcpy(G.discard[p], Curses, sizeof(int) * maxCount);

		re = scoreFor(p,&G);

#if (NOISY_TEST == 1)
		printf("score = %d, expected = %d\n", re, -1 * 3* maxCount);
#endif
		assert(re == -1 * 3 * maxCount);
		
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p], Estates, sizeof(int) * maxCount);
		memcpy(G.deck[p], Estates, sizeof(int) * maxCount);
		memcpy(G.discard[p], Estates, sizeof(int) * maxCount);

		re = scoreFor(p,&G);

#if (NOISY_TEST == 1)
		printf("score = %d, expected = %d\n", re, 3* maxCount);
#endif
		assert(re == 3 * maxCount);
	
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p], Duchys, sizeof(int) * maxCount);
		memcpy(G.deck[p], Duchys, sizeof(int) * maxCount);
		memcpy(G.discard[p], Duchys, sizeof(int) * maxCount);

		re = scoreFor(p,&G);

#if (NOISY_TEST == 1)
		printf("score = %d, expected = %d\n", re, 3 * 3* maxCount);
#endif
		assert(re == 3 * 3 * maxCount);

		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p], Provinces, sizeof(int) * maxCount);
		memcpy(G.deck[p], Provinces, sizeof(int) * maxCount);
		memcpy(G.discard[p], Provinces, sizeof(int) * maxCount);

		re = scoreFor(p,&G);

#if (NOISY_TEST == 1)
		printf("score = %d, expected = %d\n", re, 6 * 3* maxCount);
#endif
		assert(re == 6 * 3 * maxCount);
		
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p], Great_halls, sizeof(int) * maxCount);
		memcpy(G.deck[p], Great_halls, sizeof(int) * maxCount);
		memcpy(G.discard[p], Great_halls, sizeof(int) * maxCount);

		re = scoreFor(p,&G);

#if (NOISY_TEST == 1)
		printf("score = %d, expected = %d\n", re, 1 * 3* maxCount);
#endif
		assert(re == 1 * 3 * maxCount);
		
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p], Gardens, sizeof(int) * maxCount);
		memcpy(G.deck[p], Gardens, sizeof(int) * maxCount);
		memcpy(G.discard[p], Gardens, sizeof(int) * maxCount);

		re = scoreFor(p,&G);

#if (NOISY_TEST == 1)
		printf("score = %d, expected = %d\n", re, 3* maxCount * (3* maxCount/10));
#endif
		assert(re == 3 * maxCount * (3* maxCount/10));
	}
	printf("All tests passed!\n");

	return 0;
}
