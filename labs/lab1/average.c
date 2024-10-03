// Only this line of comment is provided 
#include <stdio.h>

int main (void) {

     double x, total, average;
     int count = 1;
     while (scanf("%lf", &x) == 1) {
          total += x;
          average = total / count++;
          printf("Total=%f Average=%f\n", total, average);
     }

    return 0; 
}