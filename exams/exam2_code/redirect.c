#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>

//redirect standard input to the specified file
void redirectStdin(const char *filename)
{
        int fd = open(filename, O_RDONLY);
        if(fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
	//TODO
        //fill in the code below
        dup2(fd, 0); // 0 for stdin
        close(fd);
}

//redirect standad output to the specified file
void redirectStdout(const char *filename)
{
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if(fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
	//TODO
	//fill in the code below
        dup2(fd, 1); // 1 for stdin
        close(fd);
}

//TODO: imeplement the following function
// if word is an arithmetic sequence word, return 1 else return 0

int arithmetic(char *word) {
    int length = strlen(word);
    
    // Calculate the common difference from the first two characters
    
    // Iterate through each consecutive pair to check if the difference is constant
    for (int i = 0; i < length; i++) {
        int difference = word[i+1] - word[i];
        if (difference != 2) {
            return 0;  // Not an arithmetic sequence
        }
    }
    
    return 1;  // All consecutive differences matched the initial difference
}