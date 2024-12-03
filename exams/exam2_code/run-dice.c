#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// write an integer to a pipe
void write_int(int pd, int value) { write(pd, &value, sizeof(int)); }
// read an integer from a pipe
// the function returns the number of bytes read
int read_int(int pd, int *value) { return read(pd, value, sizeof(int)); }

void dice_dist(int n) {
  int pd1[2];
  // pipe creation
  if (pipe(pd1) < 0) {
    perror("Error.");
    exit(-1);
  }

  int pd2[2];
  // pipe creation
  if (pipe(pd2) < 0) {
    perror("Error.");
    exit(-1);
  }
  pid_t pid = fork();
  if (pid == 0) {
    // TODO
    // fill in code below
    // note this is process A
    close(pd1[0]);
    close(pd2[1]);

    srand(3100);

    int v;
    // TODO
    // complete the following line of code
    // pd2[1] or pd2[PFD_WRITEEND] will receive a 1
    while (read_int(pd2[0], &v) != 0) { // for readend
      // TODO
      // fill in code below
      // int random = rand() % 6 + 1;
      if (v == 1) {
        v = rand() % 6 + 1;
        // v = rand();
        // printf("random = %d\n", v);
        write_int(pd1[1], v);
      }
    }
    // TODO
    // fill in code below
    close(pd2[0]);
    // close(pd1[1]);
    exit(0);
  }
  // TODO
  // fill in code below
  close(pd1[1]);

  int pd3[2];
  // pipe creation
  if (pipe(pd3) < 0) {
    perror("Error.");
    exit(-1);
  }

  int pd4[2];
  // pipe creation
  if (pipe(pd4) < 0) {
    perror("Error.");
    exit(-1);
  }
  pid_t pid1 = fork();

  if (pid1 == 0) {
    // fill in code below
    // note this is process B
    close(pd1[0]);
    close(pd2[0]);
    close(pd2[1]);
    close(pd3[0]);
    close(pd4[1]);
    srand(3504);

    int v;
    // TODO
    // complete the following line of code

    // reading from pd4[PFD_READEND]
    // cuz it sends from pd4[PFD_WRITEEND]
    while (read_int(pd4[0], &v) != 0) {
      // TODO
      // fill in code below
      if (v == 1) {
        v = rand() % 6 + 1;
      }
      write_int(pd3[1], v);
    }

    // fill in code below
    close(pd4[0]);
    exit(0);
  }
  // TODO
  // fill in code below
  close(pd3[1]);

  int dist[11] = {0};
  int v1, v2;
  for (int i = 0; i < n; i++) {
    write_int(pd2[1], 1);
    write_int(pd4[1], 1);
    read_int(pd1[0], &v1);
    read_int(pd3[0], &v2);
    // printf("v1 = %d, v2 = %d\n", v1, v2);
    // TODO
    // fill in code below
    int sum = v1 + v2;
    switch (sum)
    {
      case (2): dist[0]++; break;
      case (3): dist[1]++; break;
      case (4): dist[2]++; break;
      case (5): dist[3]++; break;
      case (6): dist[4]++; break;
      case (7): dist[5]++; break;
      case (8): dist[6]++; break;
      case (9): dist[7]++; break;
      case (10): dist[8]++; break;
      case (11): dist[9]++; break;
      case (12): dist[10]++; break;
      
      default:
        break;
    }
  }



  // TODO
  // fill in code below
  close(pd2[0]);
  close(pd2[1]);

  close(pd4[0]);
  close(pd4[1]);

  close(pd1[0]);
  close(pd3[0]);
  // already closed pd1[1] and pd3[1]

  waitpid(pid, NULL, 0);
  waitpid(pid1, NULL, 0);

  for (int i = 2; i <= 12; i++)
    printf("%02d %d\n", i, dist[i - 2]);
}
