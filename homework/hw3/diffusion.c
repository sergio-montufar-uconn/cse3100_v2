#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{
	int length = (2 * n) + 1;
	int x = 0, y = 0, z = 0;

	for (int i = 0; i < n; i++) {
		int random = rand() % 6;
		if (random == 0) x--;
		else if (random == 1) x++;
		else if (random == 2) y++;
		else if (random == 3) y--;
		else if (random == 4) z++;
		else if (random == 5) z--;
	}

	int first = (x + n) * (length * length);
	int second = (y + n) * length;
	int third = z + n;
	
	grid[first + second + third] += 1;


}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{
	int sum = 0;
	int count = 0;
	int length = (2 * n) + 1;

	for (int x = -n; x < n; x++){
		for (int y = -n; y < n; y++) {
			for (int z = -n; z < n; z++) {
				int first = (x + n) * (length * length);
				int second = (y + n) * length;
				int third = z + n;
				
				sum += grid[first + second + third];

				if ((x * x) +  (y * y) + (z * z) <= (r * r * n * n)) {
					count += grid[first + second + third];
				}
		
			}
		}
	}


	return (double) count / sum;
    
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below
	int length = (2 * n + 1);
	int * grid = (int *) calloc(length * length * length, sizeof(int)); // length is there 3 times due to it being 3-dimensional
	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);
	//fill in some code below

	free(grid);
}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}