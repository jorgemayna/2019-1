#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define NUM_HILOS 5
int a=0,b=0,c=0,d=0,e=0;
pthread_mutex_t lock;
pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;
pthread_mutex_t lock4;
pthread_mutex_t lock5;

void* filosofo(void *id){
    long ids=(long)id;
    int mbool=0;
    int arr=0;
    int palitos=0;
    int a1=0,b1=0,c1=0,d1=0,e1=0;
    while(arr<10){
        a1=0;b1=0;c1=0;d1=0;e1=0;
        if(a==0){
        if(pthread_mutex_trylock(&lock)==0 && palitos<2){
            a++;
            a1++;
            palitos++;
            //printf("usando a hilo: %ld   arr: %d \n",ids,arr);
            pthread_mutex_unlock(&lock);
        }
        }
        if(b==0){
        if(pthread_mutex_trylock(&lock1)==0 && palitos<2){
            b++;
            b1++;
            palitos++;
            //printf("usando b hilo: %ld   arr: %d \n",ids,arr);
            pthread_mutex_unlock(&lock1);
        }
        }
        if(c==0){
        if(pthread_mutex_trylock(&lock2)==0 && palitos<2){
            c++;
            c1++;
            palitos++;
            //printf("usando c hilo: %ld   arr: %d \n",ids,arr);
            pthread_mutex_unlock(&lock2);
        }
        }
        if(d==0){
        if(pthread_mutex_trylock(&lock3)==0 && palitos<2){
            d++;
            d1++;
            palitos++;
            //printf("usando d hilo: %ld   arr: %d \n",ids,arr);
            pthread_mutex_unlock(&lock3);
        }
        }
        if(e==0){
        if(pthread_mutex_trylock(&lock4)==0 && palitos<2){
            e++;
            e1++;
            palitos++;
            //printf("usando e hilo: %ld   arr: %d \n",ids,arr);
            pthread_mutex_unlock(&lock4);
        }
        }
        if(palitos==2){
            printf("Filosofo %ld esta comiendo\n",ids);
            mbool=0;
            arr++;
            sleep(1);
        }else if(mbool=0){
            printf("Filosofo %ld esta hablando\n",ids);
            mbool=1;
        }
        pthread_mutex_trylock(&lock5);
        a=a-a1;
        b=b-b1;
        c=c-c1;
        d=d-d1;
        e=e-e1;
        pthread_mutex_unlock(&lock5);
        palitos=0;
    }


}

int main(){
    int rc;
    long id;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex 0 init has failed\n");
        return EXIT_FAILURE;
    }
    if (pthread_mutex_init(&lock1, NULL) != 0) {
        printf("\n mutex 1 init has failed\n");
        return EXIT_FAILURE;
    }
    if (pthread_mutex_init(&lock2, NULL) != 0) {
        printf("\n mutex 2 init has failed\n");
        return EXIT_FAILURE;
    }
    if (pthread_mutex_init(&lock3, NULL) != 0) {
        printf("\n mutex 3 init has failed\n");
        return EXIT_FAILURE;
    }
    if (pthread_mutex_init(&lock4, NULL) != 0) {
        printf("\n mutex 4 init has failed\n");
        return EXIT_FAILURE;
    }
    if (pthread_mutex_init(&lock5, NULL) != 0) {
        printf("\n mutex 4 init has failed\n");
        return EXIT_FAILURE;
    }

    pthread_t arreglo_hilos[NUM_HILOS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    for (id=0;id<NUM_HILOS;id++){
        rc=pthread_create(&arreglo_hilos[id],&attr,filosofo,(void*)id);
        if (rc){printf("ERROR al crear el hilo %ld codigo %d \n",id,rc);
        exit(-1);}

    }

    pthread_attr_destroy(&attr);

    for (id=0;id<NUM_HILOS;id++)
    {
        rc=pthread_join(arreglo_hilos[id],NULL);
        if (rc){printf("ERROR,codigo %d \n",rc);
            exit(-1);
        }
    }
    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    pthread_mutex_destroy(&lock3);
    pthread_mutex_destroy(&lock4);
    pthread_mutex_destroy(&lock5);

    return 0;
}
