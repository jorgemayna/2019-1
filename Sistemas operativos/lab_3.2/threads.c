#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include"atomic_ops.h"
#include"hrtimer_x86.h"
#define NUM_HILOS 4

int cuenta=0;
pthread_t arreglo_hilos[NUM_HILOS];
pthread_mutex_t lock;
ticket_lock_t tiket;

void* sumar(void *id){
    for(int i=0;i<50000;i++){
        cuenta++;
    }

}
void* sumar_lock(void *id){
    for(int i=0;i<50000;i++){
        pthread_mutex_lock(&lock);
        cuenta++;
        pthread_mutex_unlock(&lock);
    }

}
void* sumar_lock_TAS(void *id){
    for(int i=0;i<50000;i++){
        pthread_mutex_lock(&lock);
        cuenta++;
        pthread_mutex_unlock(&lock);
    }

}
void* sumar_lock_TIQUET(void *id){
    for(int i=0;i<50000;i++){
        ticket_acquire(&tiket);
        cuenta++;
        ticket_release(&tiket);
    }

}
int main(){
    int rc;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex 0 init has failed\n");
        return EXIT_FAILURE;
    }

    for (int id=0;id<NUM_HILOS;id++){
        rc=pthread_create(&arreglo_hilos[id],&attr,sumar_lock,NULL);
        if (rc){printf("ERROR al crear el hilo %d codigo %d \n",id,rc);
        exit(-1);}

    }

    for (int id=0;id<NUM_HILOS;id++)
    {
        rc=pthread_join(arreglo_hilos[id],NULL);
        if (rc){printf("ERROR,codigo %d \n",rc);
            exit(-1);
        }
    }
    pthread_mutex_destroy(&lock);
    pthread_attr_destroy(&attr);
    printf("Cuenta: %d \n",cuenta);

}
