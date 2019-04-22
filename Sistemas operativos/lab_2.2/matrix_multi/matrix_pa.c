#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<pthread.h>
#include <sys/time.h>
#define NUM_HILOS 8

int** matriz_a;
int** matriz_b;
int** matriz_c;
int l,m,r,t;

int** init(int** matriz,int f,int c){
    matriz= (int **)malloc (f*sizeof(int *));
    for (int i=0;i<f;i++)matriz[i]=(int *) malloc (c*sizeof(int));
    for (int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            matriz[i][j]=rand()%6;
        }
    }
    return matriz;
}
int** init_vacia(int** matriz,int f,int c){
    matriz= (int **)malloc (f*sizeof(int *));
    for (int i=0;i<f;i++)matriz[i]=(int *) malloc (c*sizeof(int));
    return matriz;
}
void print_m(int** matriz,int f,int c){
    for (int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}
void* matrix_multi(void *id){

    long ids=(long)id;


    for(int p=(int)ids;p<t;p=p+NUM_HILOS){
        //printf("%ld : %d ",ids,p);

        int fi=p/r,co=p%r;
        //printf("%d %d \n",fi,co);

        matriz_c[fi][co]=0;
        for(int z=0;z<m;z++){
            matriz_c[fi][co]=matriz_c[fi][co]+matriz_a[fi][z]*matriz_b[z][co];
        }


    }

    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));
    int rc;
    long id;
    pthread_t arreglo_hilos[NUM_HILOS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    int fa,ca,fb,cb;
    printf("filas de a: ");
    scanf("%d",&fa);
    printf("columnas de a: ");
    scanf("%d",&ca);
    printf("filas de b: ");
    scanf("%d",&fb);
    printf("columnas de b: ");
    scanf("%d",&cb);
    if(ca!=fb){
        printf("No se pueden multiplicar las matrices");
        return 0;
    }
    l=fa;
    m=ca;
    r=cb;
    t=(fa)*(cb);
    matriz_a=init(matriz_a,fa,ca);
    matriz_b=init(matriz_b,fb,cb);

    matriz_c=init_vacia(matriz_c,fa,cb);
    struct timeval start;
	struct timeval finish;
	long compTime;
	double Time=0;
	for(int i=0;i<20;i++){

	gettimeofday(&start, 0);


    for (id=0;id<NUM_HILOS;id++){
        rc=pthread_create(&arreglo_hilos[id],&attr,matrix_multi,(void*)id);
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

    gettimeofday(&finish, 0);
    compTime = (finish.tv_sec - start.tv_sec) * 1000000;
	compTime = compTime + (finish.tv_usec - start.tv_usec);
	Time = (double)compTime +Time;
	}
	Time=Time/20;
	printf("Application time: %f Secs\n",(double)Time/1000000.0);
/*
    print_m(matriz_a,fa,ca);
    printf("\n");
    print_m(matriz_b,fb,cb);
    printf("\n");
    print_m(matriz_c,fa,cb);
*/
}
