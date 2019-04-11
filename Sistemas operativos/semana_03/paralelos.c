#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *printHola(void *num_hilo){
	long t;
	t=(long)num_hilo;
	printf("Hola Mundo desde el hilo %ld \n",t);
	pthread_exit(NULL);
}
int main(){
int i,j,k,rc;
long t;
static int n_hilos=1000;
pthread_t hilos[n_hilos];
printf("Bienvenidos a hola \n");
for (int i = 0; i < n_hilos; i++) {
  t=i;
  rc=pthread_create(&hilos[i],NULL,printHola,(void*)t);
  if(rc){
  printf("erroe");
  exit(-1);
  }
}
pthread_exit(NULL);
return 0;
}
