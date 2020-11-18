#include "apue.h"
#include <dirent.h>
#include <iostream>
#include <pthread.h>

#include "error.h"

using namespace std;


void *thr_fun1(void *arg)
{
    printf(" thread 1 returning \n  ");
    return ( (void *)1);
}

void *thr_fun2(void *arg)
{
    printf("hread 1 exiting \n ");
    pthread_exit ( (void *)2);
}

int main(int argc, char *argv[]){
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fun1, NULL);
    if(err != 0)
    {
        err_exit(err, "can't create thread1");
    }

    err = pthread_create(&tid2, NULL, thr_fun2, NULL);
    if(err != 0)
    {
        err_exit(err, "can't create thread1");
    }

    err = pthread_join(tid1, &tret);
    if(err != 0)
    {
        err_exit(err, "can't join with thread1");
    }
    printf(" thread 1 exit code is :%ld \n ", (long)tret);

    err = pthread_join(tid2, &tret);
    if(err != 0)
    {
        err_exit(err, "can't join with thread1");
    }
    printf(" thread 2 exit code is :%ld \n ", (long)tret);


    exit(0);
}
