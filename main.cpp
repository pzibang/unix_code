#include "apue.h"
#include <dirent.h>
#include <iostream>
#include <pthread.h>

#include "error.h"

using namespace std;

void print_pids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
   tid = pthread_self();

   printf("%s pid %lu tid %lu (ox%lx) \n", \
             s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);

}

void *thr_fun(void *arg)
{
    print_pids("new thread: ");
    return ( (void *)0);
}

int main(int argc, char *argv[]){
    int err;
    pthread_t ntid;

    err = pthread_create(&ntid, NULL, thr_fun, NULL);
    if(err != 0)
    {
        err_exit(err, "can't create thread");
    }

    print_pids("main thread: ");
//    sleep(1);

    exit(0);
}
