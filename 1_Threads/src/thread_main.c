#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread_functions.h"
#include "utilities.h"

#define NUM_ARGS    1
#define NUM_THREADS 10

int main(int argc, char ** argv)
{
    int             exit_code      = E_FAILURE;
    thread_list_t * thread_list    = NULL;
    const char *    program_name_p = argv[0];

    if (NUM_ARGS != argc)
    {
        print_error("Invalid number of arguments.\n");
        goto END;
    }

    (void)program_name_p;

    thread_list = thread_list_init(NUM_THREADS);
    if (NULL == thread_list)
    {
        print_error("thread_list_init() failed.");
        goto END;
    }

    pthread_mutex_init(&mutex, NULL);

    exit_code = create_threads(thread_list, routine);
    if (E_SUCCESS != exit_code)
    {
        print_error("create_threads() failed.");
        goto END;
    }

    exit_code = join_threads(thread_list);
    if (E_SUCCESS != exit_code)
    {
        print_error("join_threads() failed.");
        goto END;
    }

    pthread_mutex_destroy(&mutex);

    exit_code = E_SUCCESS;
END:
    thread_list_destroy(&thread_list);
    return exit_code;
}
