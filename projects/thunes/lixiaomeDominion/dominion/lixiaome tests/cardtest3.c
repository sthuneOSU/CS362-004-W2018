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
    int buys = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxCount = 5;
    // arrays of all coppers, silvers, and golds
    int test_hand[MAX_HAND];
    for (i = 0; i < maxCount; i++)
    {
	test_hand[i] = council_room;
    }

    printf ("TESTING council_room():\n");
    for (p = 0; p < numPlayer; p++)
    {
	for(pos = 0; pos < maxCount; pos++){
#if (NOISY_TEST == 1)
                printf("Test player %d with %d card in hand.\n", p, maxCount);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		for(i = 0; i< numPlayer; i++){
			if( i != p){
				G.handCount[i] = maxCount;
				memcpy(G.hand[i],test_hand,sizeof(int) * maxCount);
			}
		}
		G.handCount[p] = maxCount;
		memcpy(G.hand[p],test_hand,sizeof(int) * maxCount);
		G.numBuys = buys;
		run_council_room(p,&G,pos);
#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d, G.numBuys = %d, expected = %d\n", G.handCount[p],maxCount+3,G.numBuys,buys);
		for(i = 0; i< numPlayer; i++){
			if( i != p) printf("The player %d 's handCount = %d, expected = %d\n",i, G.handCount[i],maxCount+1);
		}
#endif
		assert(G.handCount[p] == maxCount+3 && G.numBuys == buys+1);
		for(i = 0; i< numPlayer; i++){
			if( i != p) assert(G.handCount[i]==maxCount+1);
		}
    }
}
    printf("All tests passed!\n");

    return 0;
}
