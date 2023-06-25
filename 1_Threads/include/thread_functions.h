#ifndef _THREAD_FUNCTIONS_H
#define _THREAD_FUNCTIONS_H

pthread_mutex_t mutex;

typedef void * (*JOB_F)(void * arg);

typedef struct thread_list
{
    pthread_t * threads;
    size_t      size;
} thread_list_t;

/**
 * @brief A routine for a thread
 *
 * @return void*
 */
void * routine(void * arg);

int             create_threads(thread_list_t * thread_list, JOB_F routine);
int             join_threads(thread_list_t * thread_list);
thread_list_t * thread_list_init(size_t num_threads);
void            thread_list_destroy(thread_list_t ** thread_list);

#endif
