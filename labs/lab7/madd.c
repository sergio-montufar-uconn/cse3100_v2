#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t * arg = (thread_arg_t *) p_arg;
    int halfRow = arg->m->nrows / 2;
    int col = arg->m->ncols;

    int startRow = (arg->id == 0) ? 0 : halfRow;
    int endRow = (arg->id == 0) ? halfRow : arg->m->nrows;

    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < col; j++) {
            arg->t->data[i][j] = arg->m->data[i][j] + arg->n->data[i][j];
        }
    }
    return NULL;

}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t threads[NUM_THREADS];
    thread_arg_t thread_args[NUM_THREADS];

    int ret;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].id = i;
        thread_args[i].m = m;
        thread_args[i].n = n;
        thread_args[i].t = t;

        ret = pthread_create(&threads[i], NULL, thread_main, &thread_args[i]);
        if (ret) {
            perror("Thread creation failed");
            exit(-1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        ret = pthread_join(threads[i], NULL);
        if (ret) {
            perror("Thread creation failed");
            exit(-1);
        }
    }

    return t;
}



/********  Code of addMatrix for reference  *******/

// TMatrix * addMatrix(TMatrix *m, TMatrix *n)
// {
//     if (    m == NULL || n == NULL
//          || m->nrows != n->nrows || m->ncols != n->ncols )
//         return NULL;

//     TMatrix * t = newMatrix(m->nrows, m->ncols);
//     if (t == NULL)
//         return t;
//     for (unsigned int i = 0; i < m->nrows; i++)
//         for (unsigned int j = 0; j < m->ncols; j++)
//             t->data[i][j] = m->data[i][j] + n->data[i][j];
//     return t;
// }