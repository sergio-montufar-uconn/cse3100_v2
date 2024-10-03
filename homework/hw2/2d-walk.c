#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n)
{

	//Fill in code below
	//When deciding which way to go for the next step, generate a random number as follows.
	//r = rand() % 4;
	//Treat r = 0, 1, 2, 3 as up, right, down and left respectively.

	//The random walk should stop once the x coordinate or y coordinate reaches $-n$ or $n$. 
	//The function should return the fraction of the visited $(x, y)$ coordinates inside (not including) the square.

	int size = 2 * n + 1;

	int **twoD = (int **) malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++) {
		twoD[i] = (int *) malloc(size * sizeof(int));
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			twoD[i][j] = 0;
		}
	}

	int x = n, y = n;
	twoD[x][y] = n;
	int total_visited = 0;

	while (x > 0 && x < 2 * n && y > 0 && y < 2 * n) {
		int r = rand() % 4;
		if (r == 0) y++;
		else if (r == 1) x++;
		else if (r == 2) y--;
		else if (r == 3) x--;

		if (twoD[x][y] == 0) {
			twoD[x][y] = 1;
			total_visited++;
		}
	}

    int total_points = (2 * n - 1) * (2 * n - 1);
    double fraction = (double) total_visited / total_points;

    for (int i = 0; i < size; i++) {
        free(twoD[i]);
    }
    free(twoD);
	
    return fraction;

	
}

//Do not change the code below
int main(int argc, char *argv[])
{
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;
}
