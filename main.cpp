#include "apue.h"

#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

using namespace std;

#define SHM_SIZE 2000 


int main()
{
    int shmid;
    char *shmprt;
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT|0600);
    if(shmid < 0)
    {
        printf("shmget error");
    }

    shmprt = (char*)shmat(shmid, 0, 0);
    if(shmprt == (void*)-1)
    {
        printf("shmat error");
    }

    for(int i = 0; i<SHM_SIZE; i++)
    {
        shmprt[i] = ('a'+ i%26);
    }

    for(int i = 0; i<SHM_SIZE; i++)
    {
        printf("%d:%c \n",i, shmprt[i]);
    }    

    if(shmctl(shmid, IPC_RMID, 0)<0)
    {
        printf("shmctl error");
    }


    return 0;
}


