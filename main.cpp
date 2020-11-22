#include "apue.h"
#include <dirent.h>
#include <iostream>
#include <pthread.h>

#include "error.h"

using namespace std;

struct date
{
    int year;
    int month;
    int dat;
};

void *thr_fun1(void *arg)
{
    struct date tmp = {2020, 11, 18};
    printf(" struct address :%lx  \n  ", (unsigned long)&tmp);
    printf(" %d:%d:%d \n ", tmp.year, tmp.month, tmp.dat);
    pthread_exit( (void *)&tmp);
}

int main(int argc, char *argv[]){
    int err;
    pthread_t tid1;
    struct date *pTmp;

    err = pthread_create(&tid1, NULL, thr_fun1, NULL);
    if(err != 0)
    {
        err_exit(err, "can't create thread1");
    }

    err = pthread_join(tid1, (void **)&pTmp);
    if(err != 0)
    {
        err_exit(err, "can't join with thread1");
    }
     sleep(1);
    printf(" struct address :%lx  \n  ",  (unsigned long)pTmp);
    printf(" %d:%d:%d \n ", pTmp->year, pTmp->month, pTmp->dat);


    exit(0);
}
