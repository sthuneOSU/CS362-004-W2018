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
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING gainCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (pos = 0; pos < 10; pos++)
        {
            for (toflag = 0; toflag <= 2; toflag++)
            {

#if (NOISY_TEST == 1)
                printf("Test player %d with %d and %d toflag.\n", p, k[pos], toflag);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.supplyCount[k[pos]] = 1;

		re = gainCard(k[pos],&G,toflag,p);

#if (NOISY_TEST == 1)
                printf("G.supplyCount = %d, expected = 0\n", G.supplyCount[k[pos]]);
#endif
		assert(G.supplyCount[k[pos]] == 0 && re == 0);

		G.supplyCount[k[pos]] = 0;
		re = gainCard(k[pos],&G,toflag,p);

#if (NOISY_TEST == 1)
                printf("G.supplyCount = %d, expected = 0\n", G.supplyCount[k[pos]]);
#endif
		assert(re == -1);
          }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
