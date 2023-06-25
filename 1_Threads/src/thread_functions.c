#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread_functions.h"
#include "utilities.h"

#define MAX_THREADS 10

// NOLINTNEXTLINE
int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

static int thread_list_clear(thread_list_t * thread_list);

void * routine(void * arg)
{
    sleep(1);
    pthread_mutex_lock(&mutex);
    int index = *(int *)arg;
    printf("%d ", primes[index]);
    printf("\n");
    free(arg);
    pthread_mutex_unlock(&mutex);
    // NOLINTNEXTLINE
}

int create_threads(thread_list_t * thread_list, JOB_F routine)
{
    int   exit_code     = E_FAILURE;
    int   create_thread = 0;
    int * result        = NULL;

    if (NULL == thread_list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    for (size_t idx = 0; idx < thread_list->size; idx++)
    {
        // Allocate memory due to avoid multi-threading issues
        result  = calloc(1, sizeof(int));
        *result = idx;

        if (NULL == result)
        {
            print_error("CMR failure.");
            goto END;
        }
        create_thread =
            pthread_create(&thread_list->threads[idx], NULL, routine, result);
        if (E_SUCCESS != create_thread)
        {
            print_error("Unable to create thread.");
            goto END;
        }
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

int join_threads(thread_list_t * thread_list)
{
    int exit_code   = E_FAILURE;
    int join_thread = 0;

    if (NULL == thread_list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    for (size_t idx = 0; idx < thread_list->size; idx++)
    {
        join_thread = pthread_join(thread_list->threads[idx], NULL);
        if (E_SUCCESS != join_thread)
        {
            print_error("Unable to join thread.");
            goto END;
        }
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

thread_list_t * thread_list_init(size_t num_threads)
{
    thread_list_t * thread_list = NULL;

    if ((MAX_THREADS < num_threads) || (0 > num_threads))
    {
        print_error("Invalid number of threads");
        goto END;
    }

    thread_list = calloc(1, sizeof(thread_list_t));
    if (NULL == thread_list)
    {
        print_error("CMR failure.");
        goto END;
    }

    thread_list->threads = calloc(num_threads, sizeof(pthread_t));
    if (NULL == thread_list->threads)
    {
        print_error("CMR failure.");
        free(thread_list);
        thread_list = NULL;
        goto END;
    }

    thread_list->size = num_threads;

END:
    return thread_list;
}

void thread_list_destroy(thread_list_t ** thread_list)
{
    int exit_code = E_FAILURE;

    if (NULL == *thread_list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    exit_code = thread_list_clear(*thread_list);
    if (E_SUCCESS != exit_code)
    {
        print_error("Unable to clear thread_list.");
        goto END;
    }

    free(*thread_list);
    *thread_list = NULL;

END:
    return;
}

static int thread_list_clear(thread_list_t * thread_list)
{
    int exit_code = E_FAILURE;

    if (NULL == thread_list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    free(thread_list->threads);
    thread_list->threads = NULL;

    thread_list->size = 0;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}
