#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;

	printf("n = ");
	scanf("%d", &n);

	double pi = 0.;
	//TODO
	//add code below 
	for (i = 0; i <= n; i++) {
		double part1 = 4.0 / (8.0 * i + 1.0);
		double part2 = -1.0 * (2.0 / (8.0 * i + 4.0));
		double part3 = -1.0 * (1.0 / (8.0 * i + 5.0));
		double part4 = -1.0 * (1.0 / (8.0 * i + 6.0));
		double allCombined = part1 + part2 + part3 + part4;
		// printf("%d\n", i);
		
		int pow = 1.0;
		int powerFull = 1.0;
		while (pow <= i) {
			powerFull *= 16.0;
			pow++;
		}
		
		pi += allCombined * (1.0 / powerFull);
	}







	printf("PI = %.10f\n", pi);
	return 0;
}