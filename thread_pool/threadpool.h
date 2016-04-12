#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <pthread.h>

typedef struct task
{
    void *(*run)(void *arg);
}task_t;

#endif /* _THREADPOOL_H_ */
