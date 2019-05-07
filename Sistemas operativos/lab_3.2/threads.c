#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include"atomic_ops.h"
#include"hrtimer_x86.cc"
#define NUM_HILOS 8

int cuenta=0;
pthread_t arreglo_hilos[NUM_HILOS];
int rc;
pthread_attr_t attr;
pthread_mutex_t lock;
volatile unsigned long ptr;
volatile unsigned long tatas;
tatas_lock_t tatas1;
ticket_lock_t tiket;
ticket_lock_t ticket;


void tatas_lock(volatile unsigned long* ptrs){
    do{
        while(*ptrs ==1);
    }while(tas(ptrs)==1);
}
void locks(volatile unsigned long* ptrs){
    while(tas(ptrs)==1);
}
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
        locks(&ptr);
        cuenta++;
        ptr=0;
    }

}
void* sumar_lock_TATAS(void *id){
    for(int i=0;i<50000;i++){
        tatas_lock(&tatas);
        cuenta++;
        tatas=0;
    }

}
void* sumar_lock_TATAS_back(void *id){
    for(int i=0;i<50000;i++){
        tatas_acquire_slowpath(&tatas1);
        cuenta++;
        tatas_release(&tatas1);
    }

}
void* sumar_lock_TIQUET(void *id){
    for(int i=0;i<50000;i++){
        ticket_acquire(&ticket);
        cuenta++;
        ticket_release(&ticket);
    }

}
void threads(void *(*start_routine) (void *),void *arg){
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    for (int id=0;id<NUM_HILOS;id++){
        rc=pthread_create(&arreglo_hilos[id],&attr,start_routine,NULL);
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
    pthread_attr_destroy(&attr);

}
int main(){
    double time1;
    double time2;
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex 0 init has failed\n");
        return EXIT_FAILURE;
    }
    printf("\n\nCon 8 threads:\n\n");
    printf("Sin block \n");
    time1 = gethrtime_x86();
    threads(sumar,NULL);
    time2 = gethrtime_x86();
    printf("Cuenta: %d \n",cuenta);
    printf("Tiempo: %lf \n",time2-time1);
    cuenta=0;

    printf("\nCon mutex \n");
    time1 = gethrtime_x86();
    threads(sumar_lock,NULL);
    time2 = gethrtime_x86();
    printf("Cuenta: %d \n",cuenta);
    printf("Tiempo: %lf \n",time2-time1);
    cuenta=0;
    pthread_mutex_destroy(&lock);

    ptr=0;
    printf("\nCon TAS \n");
    time1 = gethrtime_x86();
    threads(sumar_lock_TAS,NULL);
    time2 = gethrtime_x86();
    printf("Cuenta: %d \n",cuenta);
    printf("Tiempo: %lf \n",time2-time1);
    cuenta=0;

    printf("\nCon TATAS \n");
    time1 = gethrtime_x86();
    threads(sumar_lock_TATAS,NULL);
    time2 = gethrtime_x86();
    printf("Cuenta: %d \n",cuenta);
    printf("Tiempo: %lf \n",time2-time1);
    cuenta=0;

    printf("\nCon TATAS con backlog \n");
    time1 = gethrtime_x86();
    threads(sumar_lock_TATAS_back,NULL);
    time2 = gethrtime_x86();
    printf("Cuenta: %d \n",cuenta);
    printf("Tiempo: %lf \n",time2-time1);
    cuenta=0;

    printf("\nCon Ticket \n");
    time1 = gethrtime_x86();
    threads(sumar_lock_TIQUET,NULL);
    time2 = gethrtime_x86();
    printf("Cuenta: %d \n",cuenta);
    printf("Tiempo: %lf \n",time2-time1);
    cuenta=0;
        //time = gethrtime_x86();
    /*
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
    */




}
