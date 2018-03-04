#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<string.h>
#include<stdio.h>
#include<math.h>

int checkAdventurer(int drawntreasure,struct gameState *post,int p,int cardDrawn,int *temphand){
	int check = 0;
	int i, n;
	int num_trea = 0;
	int pre_trea_hand = 0;
	int post_trea_hand = 0;
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));


	for(i = 0;i < pre.deckCount[p];i++) {
		if(pre.deck[p][i] == copper||pre.deck[p][i] == silver||pre.deck[p][i] == gold) num_trea++;
	}
	for(i = 0;i < pre.discardCount[p];i++) {
		if(pre.discard[p][i] == copper||pre.discard[p][i] == silver||pre.discard[p][i] == gold) num_trea++;
	}
	for(i = 0;i < pre.handCount[p];i++) {
		if(pre.hand[p][i] == copper||pre.hand[p][i] == silver||pre.hand[p][i] == gold) pre_trea_hand++;
	}
	run_adventurer(drawntreasure,post,p,cardDrawn,temphand);

	for(i = 0;i < post->handCount[p];i++) {
		if(post->hand[p][i] == copper||post->hand[p][i] == silver||post->hand[p][i] == gold) post_trea_hand++;
	}

	if(num_trea >= 2){
		if(!assert (post_trea_hand == pre_trea_hand + 2)){
//			check = 1;
//			printf("post_trea_hand = %d, pre_trea_hand = %d\n", post_trea_hand,pre_trea_hand);
		}
		if(!assert (post->handCount[p] == pre.handCount[p] + 2)){
//			check = 1;
//			printf("post handcount = %d, pre handcount = %d\n", post->handCount[p], pre.handCount[p]);
		}
	}
	else if(num_trea == 1){
		if(!assert (post_trea_hand == pre_trea_hand + 1)){
//			check = 1;
//			printf("post_trea_hand = %d, pre_trea_hand = %d\n", post_trea_hand,pre_trea_hand);
		}
		if(!assert (post->handCount[p] == pre.handCount[p] + 1)){
//			check = 1;
//			printf("post handcount = %d, pre handcount = %d\n", post->handCount[p], pre.handCount[p]);
		}
	}
//	if(check == 1){
//		printf("Testing adventurer with %d treasure cards in hand, %d treasure cards in the discard&deck\n",pre_trea_hand,num_trea);
//		printf("Handcount = %d, deckCount = %d, discardCount = %d\n",pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
//	}
}

int main(){
	int num_test = 40000;
	int drawntreasure = 0;
	int cardDrawn = 0;
	int temphand[MAX_HAND];
	int i,n,j,r,p, deckCount, discardCount, handCOunt;

	int k[13] = {copper,silver,gold,adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf("Testing run_adventurer.\n");

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

		for(n = 0; n < G.deckCount[p];n++) G.deck[p][n] = k[(int)floor(Random() * 13)];
		for(n = 0; n < G.discardCount[p];n++) G.discard[p][n] = k[(int)floor(Random() * 13)];
		for(n = 0; n < G.handCount[p];n++) G.hand[p][n] = k[(int)floor(Random() * 13)];

		checkAdventurer(drawntreasure,&G,p,cardDrawn,temphand);
	}

	printf("ALL TESTS OK.\n");

	return 0;
}
