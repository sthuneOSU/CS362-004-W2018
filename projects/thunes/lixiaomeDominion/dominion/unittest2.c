/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int asserttrue(int a, int b, int logic) {
	
	switch(logic) {
		case 1:
			if (a == b) 
				return 1; 
			break;
		case 2:
			if (a != b) 
				return 1; 
			break;
		case 3:
			if (a < b)  
				return 1; 
			break;
		case 4:
			if (a <= b) 
				return 1; 
			break;
		case 5:
			if (a > b)  
				return 1; 
			break;
		case 6:
			if (a >= b) 
				return 1; 
			break;
	}
	return 0;
}
	


int main() {

	int i;
	int cardCosts[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    printf("TESTING getCost() for valid cards (0 through 27)\n");
	
	for (i = 0; i < 27; i++) {
		printf("Testing card %d has value %d ... ", i, cardCosts[i]);
		if (asserttrue(cardCosts[i], getCost(i), 1))
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}
	
	printf("Testing invalid card (-1) returns -1 ... ");
	if (asserttrue(-1, getCost(-1), 1)) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("Testing invalid card (28) returns -1 ... ");
	if (asserttrue(-1, getCost(28), 1)) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	
	return 0;
}
