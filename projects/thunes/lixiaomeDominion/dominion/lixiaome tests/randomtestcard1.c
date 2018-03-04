#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<string.h>
#include<stdio.h>
#include<math.h>

int checkSmithy(int p,struct gameState *post,int handPos){
	int check = 0;
	int i, n;
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	//printf("Testing smithy with handPos = %d, Handcount = %d, deckCount = %d, discardCount = %d\n",handPos, pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
	run_smithy(p,post,handPos);

	if(pre.deckCount[p] >= 3){
		if(!assert (post->deckCount[p] == pre.deckCount[p] - 3)){
	//		check = 1;
	//		printf("post->deckCount = %d, pre.deckCount = %d\n", post->deckCount[p],pre.deckCount[p]);
		}
		if(!assert (post->handCount[p] == pre.handCount[p] + 2)){
	//		check = 1;
	//		printf("post handcount = %d, pre handcount = %d\n", post->handCount[p], pre.handCount[p]);
		}
	}
	else{
		if(!assert (post->deckCount[p] == pre.discardCount[p] + pre.deckCount[p] - 3)){
	//		check = 1;
	//		printf("post->deckCount = %d, pre.deckCount = %d\n", post->deckCount[p],pre.discardCount[p] + pre.deckCount[p] - 3);
		}
		if(!assert (post->handCount[p] == pre.handCount[p] + 2)){
	//		check = 1;
	//		printf("post handcount = %d, pre handcount = %d\n", post->handCount[p], pre.handCount[p]);
		}
	}
	//if(check == 1){
	//	printf("Testing smithy with handPos = %d, Handcount = %d, deckCount = %d, discardCount = %d\n",handPos, pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
	//}
}

int main(){
	int num_test = 5000;
	int handPos;
	int i,n,j,r,p, deckCount, discardCount, handCOunt;

	int k[13] = {copper,silver,gold,adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf("Testing run_smithy.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for(i = 0; i < num_test;i++){
		for(j = 0; j < sizeof(struct gameState); j++){
			((char*)&G)[j] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.playedCardCount = floor(Random() * MAX_HAND);
		handPos = floor(Random() * G.handCount[p]);

		for(n = 0; n < G.deckCount[p];n++) G.deck[p][n] = k[(int)floor(Random() * 13)];
		for(n = 0; n < G.discardCount[p];n++) G.discard[p][n] = k[(int)floor(Random() * 13)];
		for(n = 0; n < G.handCount[p];n++) G.hand[p][n] = k[(int)floor(Random() * 13)];
		for(n = 0; n < G.playedCardCount;n++) G.playedCards[n] = k[(int)floor(Random() * 13)];

		checkSmithy(p,&G,handPos);
	}

	printf("ALL TESTS OK.\n");

	return 0;
}
