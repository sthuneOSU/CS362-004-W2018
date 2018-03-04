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
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf ("TESTING discardCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount+= maxHandCount-1)
        {
            for (pos = 0; pos < handCount; pos++)
            {

#if (NOISY_TEST == 1)
                printf("Test player %d with %d handCount and %dth handpos discard.\n", p, handCount, pos+1);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[p] = handCount;
		memcpy(G.hand[p], k, sizeof(int) * handCount);
		played = G.playedCardCount;
		re = discardCard(pos,p,&G,0);

#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d, G.playedCardCount = %d, expected = %d\n", G.handCount[p], handCount - 1, G.playedCardCount, played + 1);
#endif
		assert(G.handCount[p] == handCount - 1&& G.playedCardCount == played + 1  && re == 0);

		G.handCount[p] = handCount;
		memcpy(G.hand[p], k, sizeof(int) * handCount);
		played = G.playedCardCount;
		re = discardCard(pos,p,&G,1);

#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d, G.playedCardCount = %d, expected = %d\n", G.handCount[p], handCount - 1, G.playedCardCount, played);
#endif
		assert(G.handCount[p] == handCount-1 && G.playedCardCount == played && re == 0);
          }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
