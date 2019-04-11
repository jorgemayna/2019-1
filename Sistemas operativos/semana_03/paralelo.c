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
	pthread_t hilo0,hilo1,hilo2,hilo3;
	printf("Bienvenidos a hola \n");
	t=0;
	rc=pthread_create(&hilo0,NULL,printHola,(void*)t);
	if(rc){
		printf("erroe");
		exit(-1);
	}
	t=1;
	rc=pthread_create(&hilo1,NULL,printHola,(void*)t);
	if(rc){
		printf("erroe");
		exit(-1);
	}

	t=2;
	rc=pthread_create(&hilo2,NULL,printHola,(void*)t);
	if(rc){
		printf("erroe");
		exit(-1);
	}
	t=3;
	rc=pthread_create(&hilo3,NULL,printHola,(void*)t);
	if(rc){
		printf("erroe");
		exit(-1);
	}
	pthread_exit(NULL);
	return 0;
}
