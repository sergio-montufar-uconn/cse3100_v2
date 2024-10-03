#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    // TODO 
    size_t length_s1 = strlen(s1), length_s2 = strlen(s2); // takes the length of string s1
    char * answer = (char * ) malloc( length_s1 + length_s2 + 1 ); // allocates memory using the size of s1 and s2
    if (answer == NULL) my_error(s1); // if malloc fails, call my_error to handle error
    strcpy(answer, s1); // copy s1 into answer
    strcat(answer, s2); // concatinate both strings together
    return answer;
}

int main(int argc, char *argv[])
{
    char *s;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        char * tp = my_strcat(s, argv[i]);
        free(s);
        s = tp;
    }
    
    printf("%s\n", s);
    free(s);
    return 0;
}