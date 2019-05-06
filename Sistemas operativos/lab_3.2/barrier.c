#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define NUM_HILOS 4

int cuenta=0;
pthread_t arreglo_hilos[NUM_HILOS];
pthread_barrier_t our_barrier;

void* barrier(void *num){
    long n=(long)num;
    for(int i=0;i<n;i++){
        pthread_barrier_wait(&our_barrier);
    }

}
void* reverse_barrier(void *num){
    long n=(long)num;

}
int main(){
    int rc;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    pthread_barrier_init(&our_barrier,NULL,NUM_HILOS);
    for(long num=10;num<=10000;num=num*10){
        for (int id=0;id<NUM_HILOS;id++){
            rc=pthread_create(&arreglo_hilos[id],&attr,barrier,(void*)num);
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
        /*
        for (int id=0;id<NUM_HILOS;id++){
            rc=pthread_create(&arreglo_hilos[id],&attr,reverse_barrier,(void*)num);
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

    pthread_attr_destroy(&attr);
    printf("Cuenta: %d \n",cuenta);

}
