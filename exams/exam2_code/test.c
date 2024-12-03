#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main() {
    char * word = "am";

    for (int i = 0; i < strlen(word)-1; i++) {
        int difference = word[i+1] - word[i];
        if (difference != 2)
            printf("this not it\n");
            return 0;
    }

    printf("this it\n");

    // printf("%d\n", word[0]);
    // printf("%d\n", word[1]);
    // printf("%d\n", word[2]);
    return 1;
}