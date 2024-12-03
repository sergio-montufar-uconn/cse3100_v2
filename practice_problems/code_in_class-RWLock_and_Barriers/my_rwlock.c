#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_mutex_t mutex;       // Mutex for managing access to the read-write lock
    pthread_cond_t read_cond;    // Condition variable for readers
    pthread_cond_t write_cond;   // Condition variable for writers
    int read_count;              // Number of active readers
    int write_count;             // Number of active writers
    int read_wait;      // TODO
    int write_wait;     // TODO
} rwlock_t;

void rwlock_init(rwlock_t *lock) {
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->read_cond, NULL);
    pthread_cond_init(&lock->write_cond, NULL);
    lock->read_count = 0;
    lock->write_count = 0;
}

void rwlock_rdlock(rwlock_t *lock) {
    // TODO
    pthread_mutex_lock(&lock->mutex);
    lock->read_wait++;
    while ( lock->write_count > 0 )
        pthread_cond_wait(&lock->read_cond, &lock->mutex);
    lock->read_wait--;
    lock->read_count++;
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_wrlock(rwlock_t *lock) {
    // TODO
    pthread_mutex_lock(&lock->mutex);
    while ( lock->write_count > 0 || lock->read_count > 0 )
        pthread_cond_wait(&lock->write_cond, &lock->mutex);
    lock->write_count++;
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_rdunlock(rwlock_t *lock) {
    // TODO
    pthread_mutex_lock(&lock->mutex);

    lock->read_count--;

    if ( lock->read_count == 0 )
        pthread_cond_signal(&lock->write_cond);

    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_wrunlock(rwlock_t *lock) {
    // TODO
    pthread_mutex_lock(&lock->mutex);
    lock->write_count--;

    // writer is done -> two groups may be waiting: readers, and other writers
    pthread_cond_broadcast(&lock->read_cond);
    pthread_cond_signal(&lock->write_cond);

    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_destroy(rwlock_t *lock) {
    pthread_mutex_destroy(&lock->mutex);
    pthread_cond_destroy(&lock->read_cond);
    pthread_cond_destroy(&lock->write_cond);
}
