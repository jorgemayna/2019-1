#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/time.h>
struct timeval start;
struct timeval finish;
pthread_mutex_t lock;
pthread_t t[5];
int unidades_de_makis[5]={20,20,20,20,20}; //El indice identifica al sabio y el array identifica el nro de makis restantes de cada sabio
int estados[5]={0,0,0,0,0}; //El indice identifica al sabio y el array identifica el estado de cada sabio, si es 1 es porque esta comiendo, si es 0 es porque esta hablando
int palillos_obtenido[5]={0,0,0,0,0}; //EL indice identifica al sabio y el array identifica el nro de palillos que tiene cada sabio
int palillo1=0,palillo2=0,palillo3=0,palillo4=0,palillo5=0; //Si es 0 el paillo esta libre, si es 1 el palillo esta siendo usado
double promedio_tiempo=0; //Contador del tiempo de la cena
void *cena(void* id_arg){
  int id=(int)id_arg;
  if(unidades_de_makis[id]==0){
    pthread_exit(NULL);
  }
  if(palillo1!=1 && palillos_obtenido[id]<2){
  if(pthread_mutex_trylock(&lock)==0){
        palillo1+=1;
        palillos_obtenido[id]+=1;
        printf("Palillo 1 lo tiene el sabio %d \n",id+1);

    pthread_mutex_unlock(&lock);
  }
}
if(palillo2!=1 && palillos_obtenido[id]<2){
  if(pthread_mutex_trylock(&lock)==0){
    palillo2+=1;
        palillos_obtenido[id]+=1;
        printf("Palillo 2 lo tiene el sabio %d \n",id+1);
    pthread_mutex_unlock(&lock);
  }
}
if(palillo3!=1 && palillos_obtenido[id]<2){
  if(pthread_mutex_trylock(&lock)==0){
    palillo3+=1;
        palillos_obtenido[id]+=1;
        printf("Palillo 3 lo tiene el sabio %d \n",id+1);
    }
    pthread_mutex_unlock(&lock);
  }
if(palillo4!=1 && palillos_obtenido[id]<2){
  if(pthread_mutex_trylock(&lock)==0){
    palillo4+=1;
        palillos_obtenido[id]+=1;
        printf("Palillo 4 lo tiene el sabio %d \n",id+1);
    pthread_mutex_unlock(&lock);
}
}
if(palillo5!=1 && palillos_obtenido[id]<2){
  if(pthread_mutex_trylock(&lock)==0){
    palillo5+=1;
        palillos_obtenido[id]+=1;
        printf("Palillo 5 lo tiene el sabio %d \n",id+1);
    pthread_mutex_unlock(&lock);
  }
}
  if(palillos_obtenido[id]==2){
    estados[id]=1;
    unidades_de_makis[id]-=1;
  }
  pthread_exit(NULL);
}
int main(){
  gettimeofday(&start, 0);
  if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
  for (int i = 0; i < 20; i++) {
  while(unidades_de_makis[0]!=0 || unidades_de_makis[1]!=0 || unidades_de_makis[2]!=0 || unidades_de_makis[3]!=0 || unidades_de_makis[4]!=0){
    for (int rank = 0; rank < 5; rank++)
       pthread_create(&t[rank], NULL,cena ,(void*)rank);
    for (int rank = 0; rank < 5; rank++)
        pthread_join(t[rank], NULL);
    for(int x = 0; x < 5; x++){
        if(estados[x]==0){
          printf("Sabio %d esta hablando\n", x+1);
        }
        else{
          printf("Sabio %d esta comiendo\n", x+1);
          estados[x]=0;
        }
        palillos_obtenido[x]=0;
    }
    for(int x = 0; x < 5; x++){
        printf("Unidades de makis restantes del sabio %d es: %d\n", x+1 , unidades_de_makis[x]);
    }
    printf("--------------------------------------------------------------------------------\n");
    promedio_tiempo+=4;
    palillo1=0;
    palillo2=0;
    palillo3=0;
    palillo4=0;
    palillo5=0;
  }
  printf("Fin de la cena %d\n", i+1);
  printf("--------------------------------------------------------------------------------\n");
  unidades_de_makis[0]=20;
  unidades_de_makis[1]=20;
  unidades_de_makis[2]=20;
  unidades_de_makis[3]=20;
  unidades_de_makis[4]=20;
}
  gettimeofday(&finish, 0);
  printf("Application time: %f Secs\n",(double)(((finish.tv_sec - start.tv_sec) * 1000000)+(finish.tv_usec - start.tv_usec))/1000000.0);
  printf("Tiempo promedio de la cena es: %f Secs\n", promedio_tiempo/20);
  //pthread_exit(NULL);
  return 0;
}
