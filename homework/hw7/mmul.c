#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t * arg = (thread_arg_t*) p_arg;
    int m_rows = arg->m->nrows;
    int m_cols = arg->m->ncols;
    int n_cols = arg->n->ncols;

    int startRow = (arg->id == 0) ? 0 : m_rows / 2; 
    int endRow = (arg->id == 0) ? m_rows/2 : m_rows;

    // if arg->id is 0
        // startRow is equal to 0

    // else
        // startRow is equal to m_rows / 2 
    
    // if arg->id is 0
        // endRow is m_rows/2
    // else
        // endRow is equal to m_rows
    
    int sum;
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < n_cols; j++) {
            for (int k = 0; k < m_cols; k++) {
                sum += arg->m->data[i][k] * arg->n->data[k][j];
            }
            arg->t->data[i][j] = sum;
        }
    }

    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
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

    for (int j = 0; j < NUM_THREADS; j++) {
        ret = pthread_join(threads[j], NULL);
        if (ret) {
            perror("Thread joining failed");
            exit(-1);
        }
    }


    return t;
}
