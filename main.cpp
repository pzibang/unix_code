#include "apue.h"
#include <stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *arg);
void *thread2(void *arg);
void maketimeout(struct timespec *tsp, long second);

int main()
{
    pthread_t thread_1;
    pthread_t thread_2;

    //thread_2 should create before thread_1,
    //because if you send condition before you use pthread_cond_wait,
    //thread_2 will wait util the next condition
    pthread_create(&thread_2, NULL, thread2, NULL);
    pthread_create(&thread_1, NULL, thread1, NULL);

    pthread_join(thread_2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}

void *thread1(void *arg)
{

    pthread_mutex_lock(&mutex);

    printf("send condition\n");
    //send condition
    sleep(2);
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex);

    //exit the thread, three method.
    //return
    pthread_exit((void*)0);

}

void *thread2(void *arg)
{
    struct timespec tsp;
    maketimeout(&tsp, 3);
    pthread_mutex_lock(&mutex);
    printf("thread2: wait condition \n");

    //wait a condition, 3 sec  time out 
    if( 0 != pthread_cond_timedwait(&cond, &mutex, &tsp))
    {
        printf("thread2: get condition time out\n");
    }
    else
    {
        printf("thread2: get condition\n");
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit((void*)0);
}

void maketimeout(struct timespec *tsp, long second)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    tsp->tv_sec = now.tv_sec;
    tsp->tv_nsec = now.tv_usec;

    tsp->tv_sec += second;
    
}