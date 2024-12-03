#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "run-dice.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s n\n", argv[0]);
		return 0;
	}
	int n = atoi(argv[1]);
	assert(n>=1 && n <=100000);
	dice_dist(n);
	return 0;
}
