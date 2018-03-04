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
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
	int maxCount = 5;
	int test_hand[maxHandCount];
	for(i = 0;i<maxHandCount;i++) test_hand[i] = smithy;

    printf ("TESTING run_smithy():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (pos = 0; pos < maxHandCount; pos++)
        {

#if (NOISY_TEST == 1)
                printf("Test player %d with %d handCount and smithy is the %dth card in hand .\n", p, maxHandCount, pos+1);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[p] = maxHandCount;
		G.deckCount[p] = maxCount;
		memcpy(G.deck[p],test_hand,sizeof(int) * maxCount);
		memcpy(G.hand[p],test_hand,sizeof(int) * maxHandCount);

		run_smithy(p,&G,pos);

#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d\n", G.handCount[p], maxHandCount+2);
                printf("G.deckCount = %d, expected = %d\n", G.deckCount[p], maxHandCount-3);
#endif
		assert(G.handCount[p] == maxHandCount + 2);
		assert(G.deckCount[p] == maxCount - 3);
        }
    }

    printf("All tests passed!\n");

    return 0;
}
