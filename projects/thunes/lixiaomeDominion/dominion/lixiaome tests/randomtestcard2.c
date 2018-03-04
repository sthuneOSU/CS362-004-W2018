#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<string.h>
#include<stdio.h>
#include<math.h>

int checkMine(struct gameState *post,int p,int choice1 ,int choice2 ,int handPos){
	int check = 0;
	int i, n,r;
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	//printf("Testing smithy with Handcount = %d, deckCount = %d, discardCount = %d\n", pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
	//printf("choice1 = %d, choice2 = %d, handPos = %d\n",handPos,choice1,choice2);
	r = run_mine(post,p,choice1,choice2,handPos);

	if(pre.hand[p][choice1] < copper || pre.hand[p][choice1] > gold){
		if(!assert(r==-1)); //check = 1;
	}
	else if(choice2 > treasure_map || choice2 < curse){
		if(!assert(r==-1)); //check = 1;
	}
	else if((getCost(pre.hand[p][choice1]) + 3) > getCost(choice2)){
		if(!assert(r==-1)); //check = 1;
	}
	else if(supplyCount(choice2,post) > 0){
		if(!assert (post->handCount[p] == pre.handCount[p] - 1)){
//			check = 1;
//			printf("post handcount = %d, pre handcount = %d\n", post->handCount[p], pre.handCount[p]);
		}
	}
	else{
		if(!assert (post->handCount[p] == pre.handCount[p] - 2)){
//			check = 1;
//			printf("post handcount = %d, pre handcount = %d\n", post->handCount[p], pre.handCount[p]);
		}
	}
//	if(check == 1){
//		printf("Testing mine with Handcount = %d, deckCount = %d, discardCount = %d\n", pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
//		printf("choice1 = %d, choice2 = %d, handPos = %d\n",choice1,choice2,handPos);
//	}
}

int main(){
	int num_test = 5000;
	int handPos,choice1,choice2;
	int i,n,j,r,p, deckCount, discardCount, handCount;

	int k[14] = {duchy,copper,silver,gold,adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf("Testing run_mine.\n");

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
		choice2 = k[(int)floor(Random() * 14)];

		for(n = 0; n < G.deckCount[p];n++) G.deck[p][n] = k[(int)floor(Random() * 14)];
		for(n = 0; n < G.discardCount[p];n++) G.discard[p][n] = k[(int)floor(Random() * 14)];
		for(n = 0; n < G.handCount[p];n++) G.hand[p][n] = k[(int)floor(Random() * 14)];
		for(n = 0; n < G.playedCardCount;n++) G.playedCards[n] = k[(int)floor(Random() * 14)];

		choice1 = floor(Random() * G.handCount[p]);

		checkMine(&G,p,choice1,choice2,handPos);
	}

	printf("ALL TESTS OK.\n");

	return 0;
}
