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
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
	int temphand[MAX_HAND];
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxCount = 5;
	int test_hand[maxCount];
	int Tresures[maxCount];
	int non_tre[maxCount];
	int one_tre[maxCount];
	for(i = 0;i<maxCount;i++){
		test_hand[maxCount] = adventurer;
		Tresures[i] = copper;
		non_tre[i] = estate;
		one_tre[i] = estate;
	}
		one_tre[0] = copper;
    printf ("TESTING run_adventurer():\n");
    for (p = 0; p < numPlayer; p++)
    {

#if (NOISY_TEST == 1)
                printf("Test player %d with full deck and discard pile of tresures.\n", p);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p],test_hand,sizeof(int) * maxCount);
		memcpy(G.deck[p],Tresures,sizeof(int) * maxCount);
		memcpy(G.discard[p],Tresures,sizeof(int) * maxCount);

		run_adventurer(0,&G,p,0,temphand);

#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d\n", G.handCount[p], maxCount+1);
                //printf("G.deckCount = %d, expected = %d\n", G.deckCount[p], maxCount - strlen(temphand));
#endif
		assert(G.handCount[p] == maxCount+1);
		//assert(G.deckCount[p] == );
#if (NOISY_TEST == 1)
                printf("Test player %d with only one tresure in deck and discard pile.\n", p);
#endif
    
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p],test_hand,sizeof(int) * maxCount);
		memcpy(G.deck[p],one_tre,sizeof(int) * maxCount);
		memcpy(G.discard[p],non_tre,sizeof(int) * maxCount);

		run_adventurer(0,&G,p,0,temphand);

#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d\n", G.handCount[p], maxCount);
                //printf("G.deckCount = %d, expected = %d\n", G.deckCount[p], maxCount - strlen(temphand));
#endif
		assert(G.handCount[p] == maxCount);

#if (NOISY_TEST == 1)
                printf("Test player %d with no tresure in deck and discard pile.\n", p);
#endif
		G.handCount[p] = maxCount;
		G.deckCount[p] = maxCount;
		G.discardCount[p] = maxCount;
		memcpy(G.hand[p],test_hand,sizeof(int) * maxCount);
		memcpy(G.deck[p],non_tre,sizeof(int) * maxCount);
		memcpy(G.discard[p],non_tre,sizeof(int) * maxCount);

		run_adventurer(0,&G,p,0,temphand);

#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d\n", G.handCount[p], maxCount-1);
                //printf("G.deckCount = %d, expected = %d\n", G.deckCount[p], maxCount - strlen(temphand));
#endif
		assert(G.handCount[p] == maxCount);
}

    printf("All tests passed!\n");

    return 0;
}
