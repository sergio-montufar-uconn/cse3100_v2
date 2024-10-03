#include <stdio.h>

int main(void) {
   printf("Hello, World!\n");
   int i = 1;
   int sum = 0;
   while(i < 200) {
      if (i % 2 == 0) 
         sum += i; 
      i++;

   }
   printf("%d\n", sum);
   return 0;
}
